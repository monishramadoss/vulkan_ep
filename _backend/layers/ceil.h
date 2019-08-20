#ifndef CEIL_H
#define CEIL_H 

#include "../layer.h"

#include <pybind11/pybind11.h>
namespace py = pybind11;

/*

Ceil takes one input data (Tensor<T>) and produces one output data
(Tensor<T>) where the ceil is, y = ceil(x), is applied to
the tensor elementwise.

input: Input tensor
output: Output tensor
*/

//Ceil
//INPUTS:                   X_i
//OPTIONAL_INPUTS:          
//OUTPUS:                   Y_o
//OPTIONAL_OUTPUTS:         
//PARAMETERS:               
//PARAMETER_TYPES:          
//OPTIONAL_PARAMETERS:      
//OPTIONAL_PARAMETERS_TYPE: 

//class stuff
namespace backend {   

    class Ceil : public Layer {
        typedef struct {
            
			
            Shape_t X_i;
            
            Shape_t Y_o;
            
        } binding_descriptor;

        
        std::string X_i;
        
        std::string Y_o;
        

        binding_descriptor   binding;

        vuh::Device* _get_device();
        vuh::Program<Specs, binding_descriptor>* program;        

    public:
        Ceil(const std::string& name);
    
        void forward() { program->run(); }
        
        void init(); 
        void bind(std::string _X_i, std::string _Y_o); 

        ~Ceil() {}
    };

}

#endif

