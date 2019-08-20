#ifndef RESHAPE_H
#define RESHAPE_H 

#include "../layer.h"

#include <pybind11/pybind11.h>
namespace py = pybind11;

/*

Reshape the input tensor similar to numpy.reshape.
First input is the data tensor, second input is a shape tensor which specifies the output shape. It outputs the reshaped tensor.
At most one dimension of the new shape can be -1. In this case, the value is
inferred from the size of the tensor and the remaining dimensions. A dimension
could also be 0, in which case the actual dimension value is unchanged (i.e. taken
from the input tensor).
input: An input tensor.
input: Specified shape for output.
output: Reshaped data.
*/

//Reshape
//INPUTS:                   data_i, shape_i
//OPTIONAL_INPUTS:          
//OUTPUS:                   reshaped_o
//OPTIONAL_OUTPUTS:         
//PARAMETERS:               
//PARAMETER_TYPES:          
//OPTIONAL_PARAMETERS:      
//OPTIONAL_PARAMETERS_TYPE: 

//class stuff
namespace backend {   

    class Reshape : public Layer {
        typedef struct {
            
			
            Shape_t data_i; Shape_t shape_i;
            
            Shape_t reshaped_o;
            
        } binding_descriptor;

        
        std::string data_i; std::string shape_i;
        
        std::string reshaped_o;
        

        binding_descriptor   binding;

        vuh::Device* _get_device();
        vuh::Program<Specs, binding_descriptor>* program;        

    public:
        Reshape(const std::string& name);
    
        void forward() { program->run(); }
        
        void init(); 
        void bind(std::string _data_i, std::string _shape_i, std::string _reshaped_o); 

        ~Reshape() {}
    };

}

#endif

