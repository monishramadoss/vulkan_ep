#ifndef SOFTMAX_H
#define SOFTMAX_H //Softmax
#include <pybind11/pybind11.h>
#include "../layer.h"

//INPUTS:                   input_input
//OPTIONAL_INPUTS:          
//OUTPUS:                   output_output
//OPTIONAL_OUTPUTS:         
//PARAMETERS:               
//PARAMETER_TYPES:          
//OPTIONAL_PARAMETERS:      axis
//OPTIONAL_PARAMETERS_TYPE: int

namespace py = pybind11;

//descriptor stuff;
namespace backend {

    struct Softmax_parameter_descriptor{    
        int axis;
    };   

    struct Softmax_input_desriptor{
        Tensor* input_input;
        
    };

    struct Softmax_output_descriptor{
        Tensor* output_output;
        
    };

    struct Softmax_binding_descriptor{
        int axis;
		
        Shape_t input_input;
        
        Shape_t output_output;
        
    };
}


namespace backend {

    class Softmax : public Layer {
        Softmax_parameter_descriptor parameters;
        Softmax_input_desriptor      input;
        Softmax_output_descriptor    output;
        Softmax_binding_descriptor   binding;

        vuh::Device* _get_device();
        vuh::Program<Specs, Softmax_binding_descriptor>* program;
        
    public:
        Softmax(std::string, Softmax_parameter_descriptor _parameter_descriptor);
    
        void forward() { program->run(); }
        void call() { program->bind(parameters); }
        ~Softmax() {}

    };
}

//cpp stuff
namespace backend {    
   
    Softmax::Softmax(std::string n, Softmax_parameter_descriptor _parameter_descriptor) : Layer(n) {
        parameters = _parameter_descriptor;
        program = new vuh::Program<Specs, Softmax_binding_descriptor>(*_get_device(), std::string(file_path + std::string("/shaders/bin/softmax.spv")).c_str());
        program->grid(1024/PROCESSKERNEL_SIZE, 1024/PROCESSKERNEL_SIZE, 64/PROCESSKERNEL_SIZE);
        program->spec(64,64,64);
      
    }

  

    vuh::Device* Softmax::_get_device() {
        for(auto t_name: inputs) {
            if(tensor_dict.end() != tensor_dict.find(t_name)) return tensor_dict[t_name]->dev;
        }
        return device;
    }
    
};


//python stuff
namespace backend{
    /*PYBIND11_MODULE(_backend, m) {
        py::class_<Softmax, Layer>(m, "Softmax")
            .def("forward", &Softmax::forward);    
    }*/
}

#endif
