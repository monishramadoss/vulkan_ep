#ifndef SCATTER_H
#define SCATTER_H 

#include "../layer.h"

/*

Given `data`, `updates` and `indices` input tensors of rank r >= 1, write the values provided by `updates` 
into the first input, `data`, along `axis` dimension of `data` (by default outer-most one as axis=0) at corresponding `indices`. 
For each entry in `updates`, the target index in `data` is specified by corresponding entry in `indices`
for dimension = axis, and index in source for dimension != axis. For instance, in a 2-D tensor case,
data[indices[i][j]][j] = updates[i][j] if axis = 0, or data[i][indices[i][j]] = updates[i][j] if axis = 1,
where i and j are loop counters from 0 up to the respective size in `updates` - 1.

Example 1:
  data = [
      [0.0, 0.0, 0.0],
      [0.0, 0.0, 0.0],
      [0.0, 0.0, 0.0],
  ]
  indices = [
      [1, 0, 2],
      [0, 2, 1],
  ]
  updates = [
      [1.0, 1.1, 1.2],
      [2.0, 2.1, 2.2],
  ]
  output = [
      [2.0, 1.1, 0.0]
      [1.0, 0.0, 2.2]
      [0.0, 2.1, 1.2]
  ]

Example 2:
  data = [[1.0, 2.0, 3.0, 4.0, 5.0]]
  indices = [[1, 3]]
  updates = [[1.1, 2.1]]
  axis = 1
  output = [[1.0, 1.1, 3.0, 2.1, 5.0]]

input: Tensor of rank r >= 1.
input: Tensor of int32/int64 indices, of r >= 1 (same rank as input).
input: Tensor of rank r >=1 (same rank and shape as indices)
output: Tensor of rank r >= 1 (same rank as input).
*/

//Scatter
//INPUTS:                   data_i, indices_i, updates_i
//OPTIONAL_INPUTS:          
//OUTPUS:                   output_o
//OPTIONAL_OUTPUTS:         
//PARAMETERS:               
//PARAMETER_TYPES:          
//OPTIONAL_PARAMETERS:      axis
//OPTIONAL_PARAMETERS_TYPE: int


//class stuff
namespace layers {   

    class Scatter : public backend::Layer {
        typedef struct {          
            backend::Shape_t data_i; backend::Shape_t indices_i; backend::Shape_t updates_i;
            
            backend::Shape_t output_o;
            
        } binding_descriptor;
        
        vuh::Program<Specs, binding_descriptor>* program;
        int axis;
        std::string data_i; std::string indices_i; std::string updates_i;
        
        std::string output_o;
        

        binding_descriptor   binding;
        vuh::Device* _get_device();

        /*using Specs = vuh::typelist<uint32_t, uint32_t, uint32_t>;     // shader specialization constants interface
	    struct Params { uint32_t size; float a; };    // shader push-constants interface
	    vuh::Program<Specs, Params>* program;*/


    public:
        Scatter(std::string name);
    
        void forward() { program->run(); }
        
        virtual void init( int _axis); 
        virtual void bind(std::string _data_i, std::string _indices_i, std::string _updates_i, std::string _output_o); 
        virtual void build();

        ~Scatter() {}
    };
   
}
#endif

