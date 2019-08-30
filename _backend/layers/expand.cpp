#include "expand.h"
//cpp stuff
namespace layers {    
   
    Expand::Expand(std::string name) : backend::Layer(name) {    
        file.append(backend::file_path);
        file.append("shaders/bin/expand.spv");       
        dev = backend::g_device;
    }
       
        
    void Expand::init() {      
  

    }
    
    void Expand::bind(std::string _input_i, std::string _shape_i, std::string _output_o){    
        m_input_i = _input_i; m_shape_i = _shape_i; m_output_o = _output_o;        
		SHAPES.push_back(backend::tensor_dict[m_input_i]->shape());
  		SHAPES.push_back(backend::tensor_dict[m_shape_i]->shape());
 
		SHAPES.push_back(backend::tensor_dict[m_output_o]->shape());
 
        _SHAPES = new vuh::Array<backend::Shape_t>(*dev, SHAPES);


    }

    void Expand::build(){     
        program = new vuh::Program<Specs, binding_descriptor>(*dev, file.c_str());
        program->grid(  vuh::div_up(SHAPES[0].w, PROCESSKERNEL_SIZE),
                        vuh::div_up(SHAPES[0].h, PROCESSKERNEL_SIZE), 
                        vuh::div_up(SHAPES[0].d, PROCESSKERNEL_SIZE));
        program->spec(SHAPES[0].w, SHAPES[0].h, SHAPES[0].d);
        program->bind({128}, *_SHAPES, *backend::tensor_dict[m_input_i]->data, *backend::tensor_dict[m_shape_i]->data, *backend::tensor_dict[m_output_o]->data);
    }

    void Expand::forward(){ 
        program->run();
    }

}

