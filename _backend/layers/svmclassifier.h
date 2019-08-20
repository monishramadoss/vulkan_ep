#ifndef SVMCLASSIFIER_H
#define SVMCLASSIFIER_H 

#include "../layer.h"

#include <pybind11/pybind11.h>
namespace py = pybind11;

/*

    Support Vector Machine classifier

input: Data to be classified.
output: Classification outputs (one class per example).
output: Class scores (one per class per example), if prob_a and prob_b are provided they are probabilities for each class, otherwise they are raw scores.
*/

//SVMClassifier
//INPUTS:                   X_i
//OPTIONAL_INPUTS:          
//OUTPUS:                   Y_o, Z_o
//OPTIONAL_OUTPUTS:         
//PARAMETERS:               
//PARAMETER_TYPES:          
//OPTIONAL_PARAMETERS:      classlabels_ints, classlabels_strings, coefficients, kernel_params, kernel_type, post_transform, prob_a, prob_b, rho, support_vectors, vectors_per_class
//OPTIONAL_PARAMETERS_TYPE: Shape_t, Tensor*, Tensor*, Tensor*, int, int, Tensor*, Tensor*, Tensor*, Tensor*, Shape_t

//class stuff
namespace backend {   

    class SVMClassifier : public Layer {
        typedef struct {
            Shape_t classlabels_ints; int kernel_type; int post_transform; Shape_t vectors_per_class;
			Shape_t classlabels_strings; Shape_t coefficients; Shape_t kernel_params; Shape_t prob_a; Shape_t prob_b; Shape_t rho; Shape_t support_vectors;
            Shape_t X_i;
            
            Shape_t Y_o; Shape_t Z_o;
            
        } binding_descriptor;

        Shape_t classlabels_ints; int kernel_type; int post_transform; Shape_t vectors_per_class; std::string classlabels_strings; std::string coefficients; std::string kernel_params; std::string prob_a; std::string prob_b; std::string rho; std::string support_vectors;
        std::string X_i;
        
        std::string Y_o; std::string Z_o;
        

        binding_descriptor   binding;

        vuh::Device* _get_device();
        vuh::Program<Specs, binding_descriptor>* program;        

    public:
        SVMClassifier(const std::string& name);
    
        void forward() { program->run(); }
        
        void init( Shape_t _classlabels_ints,  int _kernel_type,  int _post_transform,  Shape_t _vectors_per_class); 
        void bind(std::string _classlabels_strings, std::string _coefficients, std::string _kernel_params, std::string _prob_a, std::string _prob_b, std::string _rho, std::string _support_vectors, std::string _X_i, std::string _Y_o, std::string _Z_o); 

        ~SVMClassifier() {}
    };

}

#endif

