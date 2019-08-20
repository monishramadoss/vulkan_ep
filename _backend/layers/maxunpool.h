#ifndef MAXUNPOOL_H
#define MAXUNPOOL_H 

#include "../layer.h"

#include <pybind11/pybind11.h>
namespace py = pybind11;

/*

MaxUnpool essentially computes the partial inverse of the MaxPool op.
 The input information to this op is typically the the output information from a MaxPool op. The first
 input tensor X is the tensor that needs to be unpooled, which is typically the pooled tensor (first output)
 from MaxPool. The second input tensor, I, contains the indices to the (locally maximal) elements corrsponding
 to the elements in the first input tensor X. Input tensor I is typically the second output of the MaxPool op.
 The third (optional) input is a tensor that specifies the output size of the unpooling operation.

MaxUnpool is intended to do 'partial' inverse of the MaxPool op. 'Partial' because all the non-maximal
 values from the original input to MaxPool are set to zero in the output of the MaxUnpool op. Pooling
 the result of an unpooling operation should give back the original input to the unpooling op.

MaxUnpool can produce the same output size for several input sizes, which makes unpooling op ambiguous.
 The third input argument, output_size, is meant to disambiguate the op and produce output tensor of
 known/predictable size.

In addition to the inputs, MaxUnpool takes three attributes, namely kernel_shape, strides, and pads,
 which define the exact unpooling op. The attributes typically have the same values as the corrsponding
 pooling op that the unpooling op is trying to invert.

input: Input data tensor that has to be unpooled. This tensor is typically the first output of the MaxPool op.Dimensions for image case are (N x C x H x W), where N is the batch size, C is the number of channels, and H and W are the height and the width of the data. For non-image case, the dimensions are in the form of (N x C x D1 x D2 ... Dn), where N is the batch size. Optionally, if dimension denotation is in effect, the operation expects the input data tensor to arrive with the dimension denotation of [DATA_BATCH, DATA_CHANNEL, DATA_FEATURE, DATA_FEATURE ...].
input: Input data tensor containing the indices corresponding to elements in the first input tensor X.This tensor is typically the second output of the MaxPool op.Dimensions must be the same as input tensor X. The indices are linear, i.e. computed considering the tensor as flattened 1-D tensor, assuming row-major storage. Also, the linear indices should not consider padding. So the values in indices are in the range [0, N x C x D1 x ... x Dn).
input: The shape of the output can be explicitly set which will cause pads values to be auto generated. If 'output_shape' is specified, 'pads' values are ignored.
output: Output data tensor that contains the result of the unpooling.
*/

//MaxUnpool
//INPUTS:                   X_i, I_i
//OPTIONAL_INPUTS:          output_shape_i
//OUTPUS:                   output_o
//OPTIONAL_OUTPUTS:         
//PARAMETERS:               kernel_shape
//PARAMETER_TYPES:          Shape_t
//OPTIONAL_PARAMETERS:      pads, strides
//OPTIONAL_PARAMETERS_TYPE: Shape_t, Shape_t

//class stuff
namespace backend {   

    class MaxUnpool : public Layer {
        typedef struct {
            Shape_t kernel_shape; Shape_t pads; Shape_t strides;
			
            Shape_t X_i; Shape_t I_i;
            Shape_t output_shape_i;
            Shape_t output_o;
            
        } binding_descriptor;

        Shape_t kernel_shape; Shape_t pads; Shape_t strides;
        std::string X_i; std::string I_i;
        std::string output_shape_i;
        std::string output_o;
        

        binding_descriptor   binding;

        vuh::Device* _get_device();
        vuh::Program<Specs, binding_descriptor>* program;        

    public:
        MaxUnpool(const std::string& name);
    
        void forward() { program->run(); }
        
        void init( Shape_t _kernel_shape,  Shape_t _pads,  Shape_t _strides); 
        void bind(std::string _X_i, std::string _I_i, std::string _output_shape_i, std::string _output_o); 

        ~MaxUnpool() {}
    };

}

#endif

