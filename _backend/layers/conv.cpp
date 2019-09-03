#include "conv.h"
//cpp stuff
namespace layers {    
   
    Conv::Conv(std::string name) : backend::Layer(name) {    
        file.append(backend::file_path);
        file.append("shaders/bin/conv.spv");       
        dev = backend::g_device;
    }
       
        
    void Conv::init( std::string _auto_pad,  std::vector<int> _dilations,  int _group,  std::vector<int> _kernel_shape,  std::vector<int> _pads,  std::vector<int> _strides) {      
		 m_auto_pad = _auto_pad; 
 		 m_dilations = _dilations; 
 		 m_group = _group; 
 		 m_kernel_shape = _kernel_shape; 
 		 m_pads = _pads; 
 		 m_strides = _strides; 
  

    }
    
    void Conv::bind(std::string _X_i, std::string _W_i, std::string _B_i, std::string _Y_o){    
        m_X_i = _X_i; m_W_i = _W_i; m_B_i = _B_i; m_Y_o = _Y_o;        
		SHAPES.push_back(backend::tensor_dict[m_X_i]->shape());
  		SHAPES.push_back(backend::tensor_dict[m_W_i]->shape());
  		SHAPES.push_back(backend::tensor_dict[m_B_i]->shape());
 
		SHAPES.push_back(backend::tensor_dict[m_Y_o]->shape());
 
        _SHAPES = new vuh::Array<backend::Shape_t>(*dev, SHAPES);


    }

    void Conv::build(){     
        program = new vuh::Program<Specs, binding_descriptor>(*dev, file.c_str());
        program->grid(vuh::div_up(SHAPES[0].w, PROCESSKERNEL_SIZE_x), vuh::div_up(SHAPES[0].h, PROCESSKERNEL_SIZE_y), vuh::div_up(SHAPES[0].d, PROCESSKERNEL_SIZE_z));
        program->spec(PROCESSKERNEL_SIZE_x, PROCESSKERNEL_SIZE_y, PROCESSKERNEL_SIZE_z);
        program->bind({2, 1}, *_SHAPES, *backend::tensor_dict[m_X_i]->data, *backend::tensor_dict[m_W_i]->data, *backend::tensor_dict[m_B_i]->data, *backend::tensor_dict[m_Y_o]->data);
    }

    void Conv::forward(){ 
        program->run();
    }

}

