#ifndef QLINEARMATMUL_H
#define QLINEARMATMUL_H 

#include "../layer.h"

/*

Matrix product that behaves like numpy.matmul: https://docs.scipy.org/doc/numpy-1.13.0/reference/generated/numpy.matmul.html.
It consumes two quantized input tensors, their scales and zero points, scale and zero point of output, and computes the quantized output.
The quantization formula is y = saturate((x / y_scale) + y_zero_point). For (x / y_scale), it is rounding to nearest ties to even.
Refer to https://en.wikipedia.org/wiki/Rounding for details. Scale and zero point must have same shape.
They must be either scalar (per tensor) or 1-D tensor (per row for 'a' and per column for 'b'). If scale and zero point are 1-D tensor,
the number of elements of scale and zero point tensor of input 'a' and output 'y' should be equal to the number of rows of input 'a',
and the number of elements of scale and zero point tensor of input 'b' should be equal to the number of columns of input 'b'.
Production must never overflow, and accumulation may overflow if and only if in 32 bits.

input: N-dimensional quantized matrix a
input: scale of quantized input a
input: zero point of quantized input a
input: N-dimensional quantized matrix b
input: scale of quantized input b
input: zero point of quantized input b
input: scale of quantized output y
input: zero point of quantized output y
output: Quantized matrix multiply results from a * b
*/

//QLinearMatMul
//INPUTS:                   a_i, a_scale_i, a_zero_point_i, b_i, b_scale_i, b_zero_point_i, y_scale_i, y_zero_point_i
//OPTIONAL_INPUTS:          
//OUTPUS:                   y_o
//OPTIONAL_OUTPUTS:         
//PARAMETERS:               
//PARAMETER_TYPES:          
//OPTIONAL_PARAMETERS:      
//OPTIONAL_PARAMETERS_TYPE: 


//class stuff
namespace layers {   

    class QLinearMatMul : public backend::Layer {
        typedef struct {          
            backend::Shape_t a_i; backend::Shape_t a_scale_i; backend::Shape_t a_zero_point_i; backend::Shape_t b_i; backend::Shape_t b_scale_i; backend::Shape_t b_zero_point_i; backend::Shape_t y_scale_i; backend::Shape_t y_zero_point_i;
            
            backend::Shape_t y_o;
            
        } binding_descriptor;
        
        vuh::Program<Specs, binding_descriptor>* program;
        
        std::string a_i; std::string a_scale_i; std::string a_zero_point_i; std::string b_i; std::string b_scale_i; std::string b_zero_point_i; std::string y_scale_i; std::string y_zero_point_i;
        
        std::string y_o;
        

        binding_descriptor   binding;
        vuh::Device* _get_device();

        /*using Specs = vuh::typelist<uint32_t, uint32_t, uint32_t>;     // shader specialization constants interface
	    struct Params { uint32_t size; float a; };    // shader push-constants interface
	    vuh::Program<Specs, Params>* program;*/


    public:
        QLinearMatMul(std::string name);
    
        void forward() { program->run(); }
        
        virtual void init(); 
        virtual void bind(std::string _a_i, std::string _a_scale_i, std::string _a_zero_point_i, std::string _b_i, std::string _b_scale_i, std::string _b_zero_point_i, std::string _y_scale_i, std::string _y_zero_point_i, std::string _y_o); 
        virtual void build();

        ~QLinearMatMul() {}
    };
   
}
#endif

