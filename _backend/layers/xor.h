#ifndef XOR_H
#define XOR_H 
#include <pybind11/pybind11.h>
#include "../layer.h"
/*

Returns the tensor resulted from performing the `xor` logical operation
elementwise on the input tensors `A` and `B` (with Numpy-style broadcasting support).

This operator supports **multidirectional (i.e., Numpy-style) broadcasting**; for more details please check [the doc](Broadcasting.md).

input: First input operand for the logical operator.
input: Second input operand for the logical operator.
output: Result tensor.

*/
//Xor
//INPUTS:                   A_input, B_input
//OPTIONAL_INPUTS:          
//OUTPUS:                   C_output
//OPTIONAL_OUTPUTS:         
//PARAMETERS:               
//PARAMETER_TYPES:          
//OPTIONAL_PARAMETERS:      
//OPTIONAL_PARAMETERS_TYPE: 

namespace py = pybind11;

//class stuff
namespace backend {   

    class Xor : public Layer {
        typedef struct {    
            
        } parameter_descriptor;  

        typedef struct {
            Tensor* A_input; Tensor* B_input;
            
        } input_desriptor;

        typedef struct {
            Tensor* C_output;
            
        } output_descriptor;

        typedef struct {
            
		
            Shape_t A_input; Shape_t B_input;
            
            Shape_t C_output;
            
        } binding_descriptor;

        parameter_descriptor parameters;
        input_desriptor      input;
        output_descriptor    output;
        binding_descriptor   binding;

        vuh::Device* _get_device();
        vuh::Program<Specs, binding_descriptor>* program;        

    public:
        Xor(std::string, parameter_descriptor _parameter_descriptor);
    
        void forward() { program->run(); }
        
        void call(); 
        void init(); 

        ~Xor() {}

    };
    
}


//cpp stuff
namespace backend {    
   
    Xor::Xor(std::string n, parameter_descriptor _parameter_descriptor) : Layer(n) {
        parameters = _parameter_descriptor;
        program = new vuh::Program<Specs, binding_descriptor>(*_get_device(), std::string(file_path + std::string("/shaders/bin/xor.spv")).c_str());
        program->grid(1024/PROCESSKERNEL_SIZE, 1024/PROCESSKERNEL_SIZE, 64/PROCESSKERNEL_SIZE);
        program->spec(64,64,64);
      
    }  

    vuh::Device* Xor::_get_device() {
        for(auto t_name: inputs) {
            if(tensor_dict.end() != tensor_dict.find(t_name)) return tensor_dict[t_name]->dev;
        }
        return device;
    }
    
    void Xor::init() {
		binding.A_input = input.A_input->shape();
  		binding.B_input = input.B_input->shape();
 
		binding.C_output = output.C_output->shape();
 

        program->bind(binding, *input.A_input->data(), *input.B_input->data(), *output.C_output->data());
    }
    
    void Xor::call(){
       
    }


}



//python stuff
/*namespace backend {
    PYBIND11_MODULE(_backend, m) {
        py::class_<Xor, Layer>(m, "Xor")
            .def("forward", &Xor::forward);    
    }
}*/

#endif
