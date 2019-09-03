#include "shrink.h"
//cpp stuff
namespace layers {    
   
    Shrink::Shrink(std::string name) : backend::Layer(name) {    
        file.append(backend::file_path);
        file.append("shaders/bin/shrink.spv");       
        dev = backend::g_device;
    }
       
        
    void Shrink::init( float _bias,  float _lambd) {      
		 m_bias = _bias; 
 		 m_lambd = _lambd; 
  

    }
    
    void Shrink::bind(std::string _input_i, std::string _output_o){    
        m_input_i = _input_i; m_output_o = _output_o;        
		SHAPES.push_back(backend::tensor_dict[m_input_i]->shape());
 
		SHAPES.push_back(backend::tensor_dict[m_output_o]->shape());
 
        _SHAPES = new vuh::Array<backend::Shape_t>(*dev, SHAPES);


    }

    void Shrink::build(){     
        program = new vuh::Program<Specs, binding_descriptor>(*dev, file.c_str());
        program->grid(vuh::div_up(SHAPES[0].w, PROCESSKERNEL_SIZE_x), vuh::div_up(SHAPES[0].h, PROCESSKERNEL_SIZE_y), vuh::div_up(SHAPES[0].d, PROCESSKERNEL_SIZE_z));
        program->spec(PROCESSKERNEL_SIZE_x, PROCESSKERNEL_SIZE_y, PROCESSKERNEL_SIZE_z);
        program->bind({2, 1}, *_SHAPES, *backend::tensor_dict[m_input_i]->data, *backend::tensor_dict[m_output_o]->data);
    }

    void Shrink::forward(){ 
        program->run();
    }

}

