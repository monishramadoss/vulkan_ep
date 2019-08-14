#ifndef RANDOMUNIFORMLIKE_H
#define RANDOMUNIFORMLIKE_H //RandomUniformLike
#include <pybind11/pybind11.h>
#include "../layer.h"

//INPUTS:                   input_input
//OPTIONAL_INPUTS:          
//OUTPUS:                   output_output
//OPTIONAL_OUTPUTS:         
//PARAMETERS:               
//PARAMETER_TYPES:          
//OPTIONAL_PARAMETERS:      dtype, high, low, seed
//OPTIONAL_PARAMETERS_TYPE: int, float, float, float

namespace py = pybind11;

//descriptor stuff;
namespace backend {

    struct RandomUniformLike_parameter_descriptor{    
        int dtype; float high; float low; float seed;
    };   

    struct RandomUniformLike_input_desriptor{
        Tensor* input_input;
        
    };

    struct RandomUniformLike_output_descriptor{
        Tensor* output_output;
        
    };

    struct RandomUniformLike_binding_descriptor{
        int dtype; float high; float low; float seed;
		
        Shape_t input_input;
        
        Shape_t output_output;
        
    };
}


namespace backend {

    class RandomUniformLike : public Layer {
        RandomUniformLike_parameter_descriptor parameters;
        RandomUniformLike_input_desriptor      input;
        RandomUniformLike_output_descriptor    output;
        RandomUniformLike_binding_descriptor   binding;

        vuh::Device* _get_device();
        vuh::Program<Specs, RandomUniformLike_binding_descriptor>* program;
        
    public:
        RandomUniformLike(std::string, RandomUniformLike_parameter_descriptor _parameter_descriptor);
    
        void forward() { program->run(); }
        void call() { program->bind(parameters); }
        ~RandomUniformLike() {}

    };
}

//cpp stuff
namespace backend {    
   
    RandomUniformLike::RandomUniformLike(std::string n, RandomUniformLike_parameter_descriptor _parameter_descriptor) : Layer(n) {
        parameters = _parameter_descriptor;
        program = new vuh::Program<Specs, RandomUniformLike_binding_descriptor>(*_get_device(), std::string(file_path + std::string("/shaders/bin/randomuniformlike.spv")).c_str());
        program->grid(1024/PROCESSKERNEL_SIZE, 1024/PROCESSKERNEL_SIZE, 64/PROCESSKERNEL_SIZE);
        program->spec(64,64,64);
      
    }

  

    vuh::Device* RandomUniformLike::_get_device() {
        for(auto t_name: inputs) {
            if(tensor_dict.end() != tensor_dict.find(t_name)) return tensor_dict[t_name]->dev;
        }
        return device;
    }
    
};


//python stuff
namespace backend{
    /*PYBIND11_MODULE(_backend, m) {
        py::class_<RandomUniformLike, Layer>(m, "RandomUniformLike")
            .def("forward", &RandomUniformLike::forward);    
    }*/
}

#endif
