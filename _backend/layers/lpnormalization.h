#ifndef LPNORMALIZATION_H
#define LPNORMALIZATION_H 

#include "../layer.h"

/*

Given a matrix, apply Lp-normalization along the provided axis.

input: Input matrix
output: Matrix after normalization
*/

//LpNormalization
//INPUTS:                   input_i
//OPTIONAL_INPUTS:          
//OUTPUS:                   output_o
//OPTIONAL_OUTPUTS:         
//PARAMETERS:               
//PARAMETER_TYPES:          
//OPTIONAL_PARAMETERS:      axis, p
//OPTIONAL_PARAMETERS_TYPE: int, int


//class stuff
namespace layers {   

    class LpNormalization : public backend::Layer {
        typedef struct {          
            backend::Shape_t input_i;
            
            backend::Shape_t output_o;
            
        } binding_descriptor;
        
        vuh::Program<Specs, binding_descriptor>* program;
        int axis; int p;
        std::string input_i;
        
        std::string output_o;
        

        binding_descriptor   binding;
        vuh::Device* _get_device();

        /*using Specs = vuh::typelist<uint32_t, uint32_t, uint32_t>;     // shader specialization constants interface
	    struct Params { uint32_t size; float a; };    // shader push-constants interface
	    vuh::Program<Specs, Params>* program;*/


    public:
        LpNormalization(std::string name);
    
        void forward() { program->run(); }
        
        virtual void init( int _axis,  int _p); 
        virtual void bind(std::string _input_i, std::string _output_o); 
        virtual void build();

        ~LpNormalization() {}
    };
   
}
#endif

