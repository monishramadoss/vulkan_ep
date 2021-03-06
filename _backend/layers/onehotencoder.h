#pragma once
#ifndef ONEHOTENCODER_H
#define ONEHOTENCODER_H 

#include "../layer.h"

/*

    Replace each input element with an array of ones and zeros, where a single
    one is placed at the index of the category that was passed in. The total category count 
    will determine the size of the extra dimension of the output array Y.<br>
    For example, if we pass a tensor with a single value of 4, and a category count of 8, 
    the output will be a tensor with ``[0,0,0,0,1,0,0,0]``.<br>
    This operator assumes every input feature is from the same set of categories.<br>
    If the input is a tensor of float, int32, or double, the data will be cast
    to integers and the cats_int64s category list will be used for the lookups.

input: Data to be encoded.
output: Encoded output data, having one more dimension than X.
*/

//OneHotEncoder
//INPUTS:                   X_i
//OPTIONAL_INPUTS:          
//OUTPUS:                   Y_o
//OPTIONAL_OUTPUTS:         
//PARAMETERS:               
//PARAMETER_TYPES:          
//OPTIONAL_PARAMETERS:      cats_int64s, cats_strings, zeros
//OPTIONAL_PARAMETERS_TYPE: std::vector<int>, std::vector<std::string>, int


//class stuff
namespace layers {   

    class OneHotEncoder : public backend::Layer {
        typedef struct {
            uint32_t input_mask;
            uint32_t output_mask;
        } binding_descriptor;
        
        vuh::Program<Specs, binding_descriptor>* program;
        std::string file;        
		vuh::Device* dev;
        std::vector<backend::Shape_t> SHAPES;
        vuh::Array<backend::Shape_t>* _SHAPES;

        std::vector<int> m_cats_int64s; std::vector<std::string> m_cats_strings; int m_zeros;
        std::string m_X_i;
        
        std::string m_Y_o;
        

        binding_descriptor   binding;
       

    public:
        OneHotEncoder(std::string name);
        
        virtual void forward();        
        virtual void init( std::vector<int> _cats_int64s,  std::vector<std::string> _cats_strings,  int _zeros); 
        virtual void bind(std::string _X_i, std::string _Y_o); 
        virtual void build();

        ~OneHotEncoder() {}
    };
   
}
#endif

