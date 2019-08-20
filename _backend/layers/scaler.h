#ifndef SCALER_H
#define SCALER_H 

#include "../layer.h"

#include <pybind11/pybind11.h>
namespace py = pybind11;

/*

    Rescale input data, for example to standardize features by removing the mean and scaling to unit variance.

input: Data to be scaled.
output: Scaled output data.
*/

//Scaler
//INPUTS:                   X_i
//OPTIONAL_INPUTS:          
//OUTPUS:                   Y_o
//OPTIONAL_OUTPUTS:         
//PARAMETERS:               
//PARAMETER_TYPES:          
//OPTIONAL_PARAMETERS:      offset, scale
//OPTIONAL_PARAMETERS_TYPE: Tensor*, Tensor*

//class stuff
namespace backend {   

    class Scaler : public Layer {
        typedef struct {
            
			Shape_t offset; Shape_t scale;
            Shape_t X_i;
            
            Shape_t Y_o;
            
        } binding_descriptor;

        std::string offset; std::string scale;
        std::string X_i;
        
        std::string Y_o;
        

        binding_descriptor   binding;

        vuh::Device* _get_device();
        vuh::Program<Specs, binding_descriptor>* program;        

    public:
        Scaler(const std::string& name);
    
        void forward() { program->run(); }
        
        void init(); 
        void bind(std::string _offset, std::string _scale, std::string _X_i, std::string _Y_o); 

        ~Scaler() {}
    };

}

#endif

