#include "lppool.h"
//cpp stuff
namespace layers {    
   
    LpPool::LpPool(std::string name) : backend::Layer(name) {    
        file.append(backend::file_path);
        file.append("shaders/bin/lppool.spv");       
        dev = backend::g_device;
    }
       
        
    void LpPool::init( std::vector<int> _kernel_shape,  std::string _auto_pad,  int _p,  std::vector<int> _pads,  std::vector<int> _strides) {      
		 m_kernel_shape = _kernel_shape; 
 		 m_auto_pad = _auto_pad; 
 		 m_p = _p; 
 		 m_pads = _pads; 
 		 m_strides = _strides; 
  

    }
    
    void LpPool::bind(std::string _X_i, std::string _Y_o){    
        m_X_i = _X_i; m_Y_o = _Y_o;        
		SHAPES.push_back(backend::tensor_dict[m_X_i]->shape());
 
		SHAPES.push_back(backend::tensor_dict[m_Y_o]->shape());
 
        _SHAPES = new vuh::Array<backend::Shape_t>(*dev, SHAPES);


    }

    void LpPool::build(){     
        program = new vuh::Program<Specs, binding_descriptor>(*dev, file.c_str());
        program->grid(  vuh::div_up(SHAPES[0].w, PROCESSKERNEL_SIZE),
                        vuh::div_up(SHAPES[0].h, PROCESSKERNEL_SIZE), 
                        vuh::div_up(SHAPES[0].d, PROCESSKERNEL_SIZE));
        program->spec(SHAPES[0].w, SHAPES[0].h, SHAPES[0].d);
        program->bind({128}, *_SHAPES, *backend::tensor_dict[m_X_i]->data, *backend::tensor_dict[m_Y_o]->data);
    }

    void LpPool::forward(){ 
        program->run();
    }

}

