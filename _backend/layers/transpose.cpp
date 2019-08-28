#include "transpose.h"
//cpp stuff
namespace layers {    
   
    Transpose::Transpose(std::string name) : backend::Layer(name) {    
        file.append(backend::file_path);
        file.append("shaders/bin/transpose.spv");       
        dev = backend::device;
    }
       
        
    void Transpose::init( std::vector<int> _perm) {      
		 perm = _perm; 
  

    }
    
    void Transpose::bind(std::string _data_i, std::string _transposed_o){    
        data_i = _data_i; transposed_o = _transposed_o;        
		SHAPES.push_back(backend::tensor_dict[data_i]->shape());
 
		SHAPES.push_back(backend::tensor_dict[transposed_o]->shape());
 
        _SHAPES = new vuh::Array<backend::Shape_t>(*dev, SHAPES);


    }

    void Transpose::build(){     
        program = new vuh::Program<Specs, binding_descriptor>(*dev, file.c_str());
        program->grid(1024 / PROCESSKERNEL_SIZE, 1024 / PROCESSKERNEL_SIZE, 64 / PROCESSKERNEL_SIZE);
        program->spec(PROCESSKERNEL_SIZE, PROCESSKERNEL_SIZE, PROCESSKERNEL_SIZE);
        program->bind({128, 0.1f}, *_SHAPES, *backend::tensor_dict[data_i]->data, *backend::tensor_dict[transposed_o]->data);
    }

    void Transpose::forward(){ 
        program->run();
    }

}

