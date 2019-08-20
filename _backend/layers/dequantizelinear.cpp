#include "DequantizeLinear.h"
//cpp stuff
namespace backend {    
   
    DequantizeLinear::DequantizeLinear(const std::string& name) : Layer(name) { }
       
    vuh::Device* DequantizeLinear::_get_device() {
        
        return device;
    }
    
    void DequantizeLinear::init() {      
  
    }
    
    void DequantizeLinear::bind(std::string _x_i, std::string _x_scale_i, std::string _x_zero_point_i, std::string _y_o){
        x_i = _x_i; x_scale_i = _x_scale_i; x_zero_point_i = _x_zero_point_i; y_o = _y_o;
		binding.x_i = tensor_dict[x_i]->shape();
  		binding.x_scale_i = tensor_dict[x_scale_i]->shape();
  		binding.x_zero_point_i = tensor_dict[x_zero_point_i]->shape();
 
		binding.y_o = tensor_dict[y_o]->shape();
 


        program = new vuh::Program<Specs, binding_descriptor>(*_get_device(), std::string(file_path + std::string("/shaders/bin/dequantizelinear.spv")).c_str());
        program->grid(1024 / PROCESSKERNEL_SIZE, 1024 / PROCESSKERNEL_SIZE, 64 / PROCESSKERNEL_SIZE);
        program->spec(64, 64, 64);
        //program->bind(binding, *tensor_dict[x_i]->data(), *tensor_dict[x_scale_i]->data(), *tensor_dict[x_zero_point_i]->data(), *tensor_dict[y_o]->data());
    }

}

