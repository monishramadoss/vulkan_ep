#ifndef ABS_H
#define ABS_H //Abs
#include <pybind11/pybind11.h>
#include "../layer.h"

//INPUTS:                   X_input
//OPTIONAL_INPUTS:          
//OUTPUS:                   Y_output
//OPTIONAL_OUTPUTS:         
//PARAMETERS:               
//PARAMETER_TYPES:          
//OPTIONAL_PARAMETERS:      
//OPTIONAL_PARAMETERS_TYPE: 

namespace py = pybind11;

//descriptor stuff;
namespace backend {

    struct Abs_parameter_descriptor{    
        
    };   

    struct Abs_input_desriptor{
        Tensor* X_input;
        
    };

    struct Abs_output_descriptor{
        Tensor* Y_output;
        
    };

    struct Abs_binding_descriptor{
        
		
        Shape_t X_input;
        
        Shape_t Y_output;
        
    };
}


namespace backend {

    class Abs : public Layer {
        Abs_parameter_descriptor parameters;
        Abs_input_desriptor      input;
        Abs_output_descriptor    output;
        Abs_binding_descriptor   binding;

        vuh::Device* _get_device();
        vuh::Program<Specs, Abs_binding_descriptor>* program;
        
    public:
        Abs(std::string, Abs_parameter_descriptor _parameter_descriptor);
    
        void forward() { program->run(); }
        void call() { program->bind(parameters); }
        ~Abs() {}

    };
}

//cpp stuff
namespace backend {    
   
    Abs::Abs(std::string n, Abs_parameter_descriptor _parameter_descriptor) : Layer(n) {
        parameters = _parameter_descriptor;
        program = new vuh::Program<Specs, Abs_binding_descriptor>(*_get_device(), std::string(file_path + std::string("/shaders/bin/abs.spv")).c_str());
        program->grid(1024/PROCESSKERNEL_SIZE, 1024/PROCESSKERNEL_SIZE, 64/PROCESSKERNEL_SIZE);
        program->spec(64,64,64);
      
    }

  

    vuh::Device* Abs::_get_device() {
        for(auto t_name: inputs) {
            if(tensor_dict.end() != tensor_dict.find(t_name)) return tensor_dict[t_name]->dev;
        }
        return device;
    }
    
};


//python stuff
namespace backend{
    /*PYBIND11_MODULE(_backend, m) {
        py::class_<Abs, Layer>(m, "Abs")
            .def("forward", &Abs::forward);    
    }*/
}

#endif
