#include "meanvariancenormalization.h"
//cpp stuff
namespace layers {    
   
    MeanVarianceNormalization::MeanVarianceNormalization(std::string name) : backend::Layer(name) {    
        file.append(backend::file_path);
        file.append("shaders/bin/meanvariancenormalization.spv");       
        dev = backend::g_device;
    }
       
        
    void MeanVarianceNormalization::init( std::vector<int> _axes) {      
		 m_axes = _axes; 
  

    }
    
    void MeanVarianceNormalization::bind(std::string _X_i, std::string _Y_o){    
        m_X_i = _X_i; m_Y_o = _Y_o;        
		SHAPES.push_back(backend::tensor_dict[m_X_i]->shape());
 
		SHAPES.push_back(backend::tensor_dict[m_Y_o]->shape());
 
        _SHAPES = new vuh::Array<backend::Shape_t>(*dev, SHAPES);


    }

    void MeanVarianceNormalization::build(){     
        program = new vuh::Program<Specs, binding_descriptor>(*dev, file.c_str());
        program->grid(  vuh::div_up(SHAPES[0].w, PROCESSKERNEL_SIZE),
                        vuh::div_up(SHAPES[0].h, PROCESSKERNEL_SIZE), 
                        vuh::div_up(SHAPES[0].d, PROCESSKERNEL_SIZE));
        program->spec(SHAPES[0].w, SHAPES[0].h, SHAPES[0].d);
        program->bind({128}, *_SHAPES, *backend::tensor_dict[m_X_i]->data, *backend::tensor_dict[m_Y_o]->data);
    }

    void MeanVarianceNormalization::forward(){ 
        program->run();
    }

}

