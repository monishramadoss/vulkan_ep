#include "AveragePool.h"
//cpp stuff
namespace backend {    
   
    AveragePool::AveragePool(const std::string& name) : Layer(name) { }
       
    vuh::Device* AveragePool::_get_device() {
        
        return device;
    }
    
    void AveragePool::init( Shape_t _kernel_shape,  int _auto_pad,  int _ceil_mode,  int _count_include_pad,  Shape_t _pads,  Shape_t _strides) {      
		 kernel_shape = _kernel_shape; 
 		 auto_pad = _auto_pad; 
 		 ceil_mode = _ceil_mode; 
 		 count_include_pad = _count_include_pad; 
 		 pads = _pads; 
 		 strides = _strides; 
  
    }
    
    void AveragePool::bind(std::string _X_i, std::string _Y_o){
        X_i = _X_i; Y_o = _Y_o;
		binding.X_i = tensor_dict[X_i]->shape();
 
		binding.Y_o = tensor_dict[Y_o]->shape();
 
		binding.kernel_shape = kernel_shape;
  		binding.auto_pad = auto_pad;
  		binding.ceil_mode = ceil_mode;
  		binding.count_include_pad = count_include_pad;
  		binding.pads = pads;
  		binding.strides = strides;
 

        program = new vuh::Program<Specs, binding_descriptor>(*_get_device(), std::string(file_path + std::string("/shaders/bin/averagepool.spv")).c_str());
        program->grid(1024 / PROCESSKERNEL_SIZE, 1024 / PROCESSKERNEL_SIZE, 64 / PROCESSKERNEL_SIZE);
        program->spec(64, 64, 64);
        //program->bind(binding, *tensor_dict[X_i]->data(), *tensor_dict[Y_o]->data());
    }

}

