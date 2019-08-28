#include "cos.h"
//cpp stuff
namespace layers {    
   
    Cos::Cos(std::string name) : backend::Layer(name) {    
        file.append(backend::file_path);
        file.append("shaders/bin/cos.spv");       
        dev = backend::device;
    }
       
        
    void Cos::init() {      
  

    }
    
    void Cos::bind(std::string _input_i, std::string _output_o){    
        input_i = _input_i; output_o = _output_o;        
		SHAPES.push_back(backend::tensor_dict[input_i]->shape());
 
		SHAPES.push_back(backend::tensor_dict[output_o]->shape());
 
        _SHAPES = new vuh::Array<backend::Shape_t>(*dev, SHAPES);


    }

    void Cos::build(){     
        program = new vuh::Program<Specs, binding_descriptor>(*dev, file.c_str());
        program->grid(1024 / PROCESSKERNEL_SIZE, 1024 / PROCESSKERNEL_SIZE, 64 / PROCESSKERNEL_SIZE);
        program->spec(PROCESSKERNEL_SIZE, PROCESSKERNEL_SIZE, PROCESSKERNEL_SIZE);
        program->bind({128, 0.1f}, *_SHAPES, *backend::tensor_dict[input_i]->data, *backend::tensor_dict[output_o]->data);
    }

    void Cos::forward(){ 
        program->run();
    }

}

