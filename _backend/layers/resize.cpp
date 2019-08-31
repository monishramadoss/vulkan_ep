#include "resize.h"
//cpp stuff
namespace layers {    
   
    Resize::Resize(std::string name) : backend::Layer(name) {    
        file.append(backend::file_path);
        file.append("shaders/bin/resize.spv");       
        dev = backend::g_device;
    }
       
        
    void Resize::init( std::string _mode) {      
		 m_mode = _mode; 
  

    }
    
    void Resize::bind(std::string _X_i, std::string _scales_i, std::string _Y_o){    
        m_X_i = _X_i; m_scales_i = _scales_i; m_Y_o = _Y_o;        
		SHAPES.push_back(backend::tensor_dict[m_X_i]->shape());
  		SHAPES.push_back(backend::tensor_dict[m_scales_i]->shape());
 
		SHAPES.push_back(backend::tensor_dict[m_Y_o]->shape());
 
        _SHAPES = new vuh::Array<backend::Shape_t>(*dev, SHAPES);


    }

    void Resize::build(){     
        program = new vuh::Program<Specs, binding_descriptor>(*dev, file.c_str());
        program->grid(  vuh::div_up(SHAPES[0].w, PROCESSKERNEL_SIZE),
                        vuh::div_up(SHAPES[0].h, PROCESSKERNEL_SIZE), 
                        vuh::div_up(SHAPES[0].d, PROCESSKERNEL_SIZE));
        program->spec(PROCESSKERNEL_SIZE, PROCESSKERNEL_SIZE, 1);
        program->bind({0}, *_SHAPES, *backend::tensor_dict[m_X_i]->data, *backend::tensor_dict[m_scales_i]->data, *backend::tensor_dict[m_Y_o]->data);
    }

    void Resize::forward(){ 
        program->run();
    }

}

