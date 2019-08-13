#ifndef FEATUREVECTORIZER_H
#define FEATUREVECTORIZER_H //FeatureVectorizer

#include "../layer.h"

//INPUTS:                   
//OPTIONAL_INPUTS:          
//OUTPUS:                   Y_output
//OPTIONAL_OUTPUTS:         
//PARAMETERS:               
//PARAMETER_TYPES:          
//OPTIONAL_PARAMETERS:      inputdimensions
//OPTIONAL_PARAMETERS_TYPE: Shape_t



namespace backend {
    class FeatureVectorizer : public Layer {
        
        vuh::Device* _get_device();

        struct Params{
            Shape_t inputdimensions;
			
            //input
            
            
            //output
            Shape_t Y_output;
            
        };

        vuh::Program<Specs, Params>* program;

    public:
        FeatureVectorizer(std::string n, std::vector<std::string> i, std::vector<std::string> o, std::map<std::string, std::vector<std::string>> a);
        void forward() { program->run(); }
        
        Shape_t inputdimensions;
		
        //input
        
        
        //output
        std::string Y_output;
        
        //std::vector<uint32_t> output_shape();
   
        ~FeatureVectorizer() {}
    };
}


namespace backend {    
    FeatureVectorizer::FeatureVectorizer(std::string n, std::vector<std::string> i, std::vector<std::string> o, std::map<std::string, std::vector<std::string>> a) : Layer(n, i, o, a) {            
        program = new vuh::Program<Specs, Params>(*_get_device(), std::string(file_path + "/shaders/bin/featurevectorizer.spv").c_str());
        program->grid(1024/PROCESSKERNEL_SIZE, 1024/PROCESSKERNEL_SIZE, 64/PROCESSKERNEL_SIZE);
        program->spec(64,64,64);
        program->bind({inputdimensions, tensor_dict[Y_output]->shape()} 
                        
                        , tensor_dict[Y_output] );
    }

    vuh::Device* FeatureVectorizer::_get_device() {
        for(auto t_name: inputs) {
            if(tensor_dict.end() != tensor_dict.find(t_name)) return tensor_dict[t_name]->dev;
        }
        return device;
    }
};

#endif
