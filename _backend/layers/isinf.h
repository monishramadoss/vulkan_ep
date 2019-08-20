#ifndef ISINF_H
#define ISINF_H 

#include "../layer.h"

#include <pybind11/pybind11.h>
namespace py = pybind11;

/*
Map infinity to true and other values to false.
input: input
output: output
*/

//IsInf
//INPUTS:                   X_i
//OPTIONAL_INPUTS:          
//OUTPUS:                   Y_o
//OPTIONAL_OUTPUTS:         
//PARAMETERS:               
//PARAMETER_TYPES:          
//OPTIONAL_PARAMETERS:      detect_negative, detect_positive
//OPTIONAL_PARAMETERS_TYPE: int, int

//class stuff
namespace backend {   

    class IsInf : public Layer {
        typedef struct {
            int detect_negative; int detect_positive;
			
            Shape_t X_i;
            
            Shape_t Y_o;
            
        } binding_descriptor;

        int detect_negative; int detect_positive;
        std::string X_i;
        
        std::string Y_o;
        

        binding_descriptor   binding;

        vuh::Device* _get_device();
        vuh::Program<Specs, binding_descriptor>* program;        

    public:
        IsInf(const std::string& name);
    
        void forward() { program->run(); }
        
        void init( int _detect_negative,  int _detect_positive); 
        void bind(std::string _X_i, std::string _Y_o); 

        ~IsInf() {}
    };

}

#endif

