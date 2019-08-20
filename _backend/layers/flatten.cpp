#include "Flatten.h"
//cpp stuff
namespace backend {    
   
    Flatten::Flatten(const std::string& name) : Layer(name) { }
       
    vuh::Device* Flatten::_get_device() {
        
        return device;
    }
    
    void Flatten::init( int _axis) {      
		 axis = _axis; 
  
    }
    
    void Flatten::bind(std::string _input_i, std::string _output_o){
        input_i = _input_i; output_o = _output_o;
		binding.input_i = tensor_dict[input_i]->shape();
 
		binding.output_o = tensor_dict[output_o]->shape();
 
		binding.axis = axis;
 

        program = new vuh::Program<Specs, binding_descriptor>(*_get_device(), std::string(file_path + std::string("/shaders/bin/flatten.spv")).c_str());
        program->grid(1024 / PROCESSKERNEL_SIZE, 1024 / PROCESSKERNEL_SIZE, 64 / PROCESSKERNEL_SIZE);
        program->spec(64, 64, 64);
        //program->bind(binding, *tensor_dict[input_i]->data(), *tensor_dict[output_o]->data());
    }

}

