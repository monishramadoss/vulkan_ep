#include "GlobalLpPool.h"
//cpp stuff
namespace backend {    
   
    GlobalLpPool::GlobalLpPool(const std::string& name) : Layer(name) { }
       
    vuh::Device* GlobalLpPool::_get_device() {
        
        return device;
    }
    
    void GlobalLpPool::init( int _p) {      
		 p = _p; 
  
    }
    
    void GlobalLpPool::bind(std::string _X_i, std::string _Y_o){
        X_i = _X_i; Y_o = _Y_o;
		binding.X_i = tensor_dict[X_i]->shape();
 
		binding.Y_o = tensor_dict[Y_o]->shape();
 
		binding.p = p;
 

        program = new vuh::Program<Specs, binding_descriptor>(*_get_device(), std::string(file_path + std::string("/shaders/bin/globallppool.spv")).c_str());
        program->grid(1024 / PROCESSKERNEL_SIZE, 1024 / PROCESSKERNEL_SIZE, 64 / PROCESSKERNEL_SIZE);
        program->spec(64, 64, 64);
        //program->bind(binding, *tensor_dict[X_i]->data(), *tensor_dict[Y_o]->data());
    }

}

