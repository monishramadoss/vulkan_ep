#include "Concat.h"

//cpp stuff
namespace backend {    
   
    Concat::Concat(std::string n) : Layer(n) { }
       
    vuh::Device* Concat::_get_device() {
        for(auto t_name: inputs) {
            if(tensor_dict.end() != tensor_dict.find(t_name)) return tensor_dict[t_name]->dev;
        }
        return device;
    }
    
    void Concat::init( int _axis) {      
		 axis = _axis; 
  
    }
    
    void Concat::bind(std::string _concat_result_output){
        concat_result_output = _concat_result_output;

		binding.concat_result_output = tensor_dict[concat_result_output]->shape();
 
		binding.axis = axis;
 

        program = new vuh::Program<Specs, binding_descriptor>(*_get_device(), std::string(file_path + std::string("/shaders/bin/concat.spv")).c_str());
        program->grid(1024 / PROCESSKERNEL_SIZE, 1024 / PROCESSKERNEL_SIZE, 64 / PROCESSKERNEL_SIZE);
        program->spec(64, 64, 64);
        //program->bind(binding, *tensor_dict[concat_result_output]->data());
    }
    
}

    //backend::nn;

//python stuff

