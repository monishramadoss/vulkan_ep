import onnx
from onnx import checker, GraphProto, TensorProto, AttributeProto, ModelProto
import onnx.numpy_helper
import onnx.defs
import onnx.optimizer
import onnx.shape_inference
import onnx.utils
from onnx.backend.base import Backend, Device, DeviceType, namedtupledict, BackendRep
from onnx.tools.net_drawer import GetPydotGraph, GetOpNodeProducer
from onnx.helper import make_tensor_value_info, make_graph, make_model
import onnx.checker
import numpy as np
import os
import time

import layers
import _backend

class OnnxAttributes(dict):
    @staticmethod
    def from_onnx(args):
        d = OnnxAttributes()
        for arg in args:
            d[arg.name] = convertAttributeProto(arg)
        return d

def convertAttributeProto(onnx_arg):   
    if   onnx_arg.HasField('f'):
        return onnx_arg.f
    elif onnx_arg.HasField('i'):
        return onnx_arg.i
    elif onnx_arg.HasField('s'):
        return onnx_arg.s
    elif onnx_arg.HasField('t'):
        return onnx_arg.t  # this is a proto!
    elif onnx_arg.HasField('g'):
        return [] #this is graph
    elif len(onnx_arg.floats):
        return list(onnx_arg.floats)
    elif len(onnx_arg.ints):
        return list(onnx_arg.ints)
    elif len(onnx_arg.strings):
        return list(onnx_arg.strings)
    elif len(onnx_arg.graphs):
        retval = []
        return retval
    else:
        raise ValueError("Unsupported ONNX attribute: {}".format(onnx_arg))

class OnnxNode(object):
    def __init__(self, node):
        self.name = str(node.name)
        self.op_type = str(node.op_type)
        self.attrs = OnnxAttributes.from_onnx(node.attribute)
        self.inputs = list(node.input)
        self.outputs = list(node.output)
    def bind():
        return (self.inputs, self.outputs, self.attrs)

class OnnxGraph:
    def __init__(self, filename):       
        _backend.test()  
        self.filename = filename
        start = time.perf_counter_ns() / 1000000
        model = onnx.load(filename)
        #model = onnx.shape_inference.infer_shapes(model)
        graph = model.graph

        self.nodes = list()
        self.layer = list()

        self.inputs = list()
        self.outputs = list()

        layers.tensors[''] = np.zeros(10)

        #for val in model.graph.value_info:
        ##    data = np.zeros([i.dim_value for i in val.type.tensor_type.shape.dim])
        #    layers.tensors[val.name] = data

        for init_val in graph.initializer:
            name, data = self._create_tensor_filling_op(init_val)            
            layers.tensors[name] = data
            
        for val in graph.input:
            if(val.name not in layers.tensors.keys()):            
                data = np.zeros([i.dim_value for i in val.type.tensor_type.shape.dim])
                self.inputs.append(val.name)
                layers.tensors[val.name] = data     
                
        for val in graph.output:
            for _val in graph.input:
                if(val.name not in layers.tensors.keys()):
                    data = np.zeros([i.dim_value for i in _val.type.tensor_type.shape.dim])
                    self.outputs.append(val.name)
                    layers.tensors[val.name] = data 
                
        for n in graph.node:
            self.nodes.append(OnnxNode(n))
        
        end = time.perf_counter_ns() / 1000000
        print(self.filename, "::: DONE MODEL PARSE :::", end-start)        
        x_start = time.perf_counter_ns() / 1000000

        start = time.perf_counter_ns() / 1000000
        for nodes in self.nodes:
            l = layers.layer_map[nodes.op_type](nodes.name, **nodes.attrs)(*nodes.inputs)
            l.output(*nodes.outputs)
            self.layer.append(l)     
        end = time.perf_counter_ns() / 1000000
        print("::: DONE NODE INIT :::", end-start, "avg", (end-start)/len(self.nodes))

        start = time.perf_counter_ns() / 1000000
        for name, data in layers.tensors.items():
            _backend.create_tensor(name, data)
        end = time.perf_counter_ns() / 1000000
        print("::: DONE Tensor BUILD :::", end-start, "avg", (end-start)/len(layers.tensors.items()))

        start = time.perf_counter_ns() / 1000000
        for l in self.layer:
             l.build()
        end = time.perf_counter_ns() / 1000000
        print("::: DONE LAYER BUILD :::", end-start, 'avg', (end-start)/len(self.layer))
        
        x_end = time.perf_counter_ns() / 1000000

        print("::: DONE BUILDING PIPE :::", x_end-x_start)
        pydot_graph = GetPydotGraph(model.graph, name=model.graph.name, rankdir="LR", node_producer=GetOpNodeProducer("docstring"))
        pydot_graph.write_dot(filename+".dot")
    
   
    def __call__(self, *args):
        tmp = None
        for i, x in enumerate(self.inputs):
            _backend.input(x, args[i])
            tmp = _backend.output(x)
        start = time.perf_counter_ns() / 1000000
            
        for layer in self.layer:
            layer.run()
            tmp = _backend.output(layer.name)
        end = time.perf_counter_ns() / 1000000
        print(self.filename, "::: DONE RUNNING PIPE :::", end-start, "avg", (end-start)/len(self.layer))
        output = list()
        for y in self.outputs:
            output.append(_backend.output(y))
        return output

    def _create_tensor_filling_op(self, onnx_tensor, name=None):
      
        assert name or onnx_tensor.name
        name = name or onnx_tensor.name

        def tensor2list(onnx_tensor):
            # Use the onnx.numpy_helper because the data may be raw
            return onnx.numpy_helper.to_array(onnx_tensor).flatten()

        if onnx_tensor.data_type == TensorProto.FLOAT:
            pass
        elif onnx_tensor.data_type == TensorProto.DOUBLE:
            pass
        elif onnx_tensor.data_type == TensorProto.INT64:
            pass
        elif onnx_tensor.data_type == TensorProto.UINT32:
            pass
        elif onnx_tensor.data_type == TensorProto.UINT8:
            pass
        elif onnx_tensor.data_type == TensorProto.INT8:
            pass
        elif onnx_tensor.data_type == TensorProto.UINT16:
            pass
        elif onnx_tensor.data_type == TensorProto.INT16:
            pass
        elif onnx_tensor.data_type == TensorProto.INT32:
            pass
        elif onnx_tensor.data_type == TensorProto.BOOL:
            pass
        elif onnx_tensor.data_type == TensorProto.STRING:
            pass
        else:
            raise RuntimeError("unrecognized tensor type {}".format(onnx_tensor.data_type))
    
        if(onnx_tensor.dims == []):
            return (name, tensor2list(onnx_tensor))
        data = tensor2list(onnx_tensor).reshape(*onnx_tensor.dims)
            
        return (name, data)
  