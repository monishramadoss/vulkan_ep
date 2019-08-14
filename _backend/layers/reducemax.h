#ifndef REDUCEMAX_H
#define REDUCEMAX_H //ReduceMax
#include <pybind11/pybind11.h>
#include "../layer.h"

//INPUTS:                   data_input
//OPTIONAL_INPUTS:          
//OUTPUS:                   reduced_output
//OPTIONAL_OUTPUTS:         
//PARAMETERS:               
//PARAMETER_TYPES:          
//OPTIONAL_PARAMETERS:      axes, keepdims
//OPTIONAL_PARAMETERS_TYPE: Shape_t, int

namespace py = pybind11;

//descriptor stuff;
namespace backend {

    struct ReduceMax_parameter_descriptor{    
        Shape_t axes; int keepdims;
    };   

    struct ReduceMax_input_desriptor{
        Tensor* data_input;
        
    };

    struct ReduceMax_output_descriptor{
        Tensor* reduced_output;
        
    };

    struct ReduceMax_binding_descriptor{
        Shape_t axes; int keepdims;
		
        Shape_t data_input;
        
        Shape_t reduced_output;
        
    };
}


namespace backend {

    class ReduceMax : public Layer {
        ReduceMax_parameter_descriptor parameters;
        ReduceMax_input_desriptor      input;
        ReduceMax_output_descriptor    output;
        ReduceMax_binding_descriptor   binding;

        vuh::Device* _get_device();
        vuh::Program<Specs, ReduceMax_binding_descriptor>* program;
        
    public:
        ReduceMax(std::string, ReduceMax_parameter_descriptor _parameter_descriptor);
    
        void forward() { program->run(); }
        void call() { program->bind(parameters); }
        ~ReduceMax() {}

    };
}

//cpp stuff
namespace backend {    
   
    ReduceMax::ReduceMax(std::string n, ReduceMax_parameter_descriptor _parameter_descriptor) : Layer(n) {
        parameters = _parameter_descriptor;
        program = new vuh::Program<Specs, ReduceMax_binding_descriptor>(*_get_device(), std::string(file_path + std::string("/shaders/bin/reducemax.spv")).c_str());
        program->grid(1024/PROCESSKERNEL_SIZE, 1024/PROCESSKERNEL_SIZE, 64/PROCESSKERNEL_SIZE);
        program->spec(64,64,64);
      
    }

  

    vuh::Device* ReduceMax::_get_device() {
        for(auto t_name: inputs) {
            if(tensor_dict.end() != tensor_dict.find(t_name)) return tensor_dict[t_name]->dev;
        }
        return device;
    }
    
};


//python stuff
namespace backend{
    /*PYBIND11_MODULE(_backend, m) {
        py::class_<ReduceMax, Layer>(m, "ReduceMax")
            .def("forward", &ReduceMax::forward);    
    }*/
}

#endif
