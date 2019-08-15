#ifndef LOG_H
#define LOG_H 
#include <pybind11/pybind11.h>
#include "../layer.h"
/*

Calculates the natural log of the given input tensor, element-wise.

input: Input tensor
output: The natural log of the input tensor computed element-wise

*/
//Log
//INPUTS:                   input_input
//OPTIONAL_INPUTS:          
//OUTPUS:                   output_output
//OPTIONAL_OUTPUTS:         
//PARAMETERS:               
//PARAMETER_TYPES:          
//OPTIONAL_PARAMETERS:      
//OPTIONAL_PARAMETERS_TYPE: 

namespace py = pybind11;

//class stuff
namespace backend {   

    class Log : public Layer {
        typedef struct {    
            
        } parameter_descriptor;  

        typedef struct {
            Tensor* input_input;
            
        } input_desriptor;

        typedef struct {
            Tensor* output_output;
            
        } output_descriptor;

        typedef struct {
            
		
            Shape_t input_input;
            
            Shape_t output_output;
            
        } binding_descriptor;

        parameter_descriptor parameters;
        input_desriptor      input;
        output_descriptor    output;
        binding_descriptor   binding;

        vuh::Device* _get_device();
        vuh::Program<Specs, binding_descriptor>* program;        

    public:
        Log(std::string, parameter_descriptor _parameter_descriptor);
    
        void forward() { program->run(); }
        
        void call(); 
        void init(); 

        ~Log() {}

    };
    
}


//cpp stuff
namespace backend {    
   
    Log::Log(std::string n, parameter_descriptor _parameter_descriptor) : Layer(n) {
        parameters = _parameter_descriptor;
        program = new vuh::Program<Specs, binding_descriptor>(*_get_device(), std::string(file_path + std::string("/shaders/bin/log.spv")).c_str());
        program->grid(1024/PROCESSKERNEL_SIZE, 1024/PROCESSKERNEL_SIZE, 64/PROCESSKERNEL_SIZE);
        program->spec(64,64,64);
      
    }  

    vuh::Device* Log::_get_device() {
        for(auto t_name: inputs) {
            if(tensor_dict.end() != tensor_dict.find(t_name)) return tensor_dict[t_name]->dev;
        }
        return device;
    }
    
    void Log::init() {
		binding.input_input = input.input_input->shape();
 
		binding.output_output = output.output_output->shape();
 

        program->bind(binding, *input.input_input->data(), *output.output_output->data());
    }
    
    void Log::call(){
       
    }


}



//python stuff
/*namespace backend {
    PYBIND11_MODULE(_backend, m) {
        py::class_<Log, Layer>(m, "Log")
            .def("forward", &Log::forward);    
    }
}*/

#endif
