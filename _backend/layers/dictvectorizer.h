#ifndef DICTVECTORIZER_H
#define DICTVECTORIZER_H //DictVectorizer

#include "../layer.h"

//INPUTS:                   X_input
//OPTIONAL_INPUTS:          
//OUTPUS:                   Y_output
//OPTIONAL_OUTPUTS:         
//PARAMETERS:               
//PARAMETER_TYPES:          
//OPTIONAL_PARAMETERS:      int64_vocabulary, string_vocabulary
//OPTIONAL_PARAMETERS_TYPE: Shape_t, Tensor*



namespace backend {
    class DictVectorizer : public Layer {
        
        vuh::Device* _get_device();

        struct Params{
            Shape_t int64_vocabulary;
			Shape_t string_vocabulary;
            //input
            Shape_t X_input;
            
            //output
            Shape_t Y_output;
            
        };

        vuh::Program<Specs, Params>* program;

    public:
        DictVectorizer(std::string n, std::vector<std::string> i, std::vector<std::string> o, std::map<std::string, std::vector<std::string>> a);
        void forward() { program->run(); }
        
        Shape_t int64_vocabulary; Tensor* string_vocabulary;
		Shape_t string_vocabulary_s;
        //input
        std::string X_input;
        
        //output
        std::string Y_output;
        
        //std::vector<uint32_t> output_shape();
   
        ~DictVectorizer() {}
    };
}


namespace backend {    
    DictVectorizer::DictVectorizer(std::string n, std::vector<std::string> i, std::vector<std::string> o, std::map<std::string, std::vector<std::string>> a) : Layer(n, i, o, a) {            
        program = new vuh::Program<Specs, Params>(*_get_device(), std::string(file_path + "/shaders/bin/dictvectorizer.spv").c_str());
        program->grid(1024/PROCESSKERNEL_SIZE, 1024/PROCESSKERNEL_SIZE, 64/PROCESSKERNEL_SIZE);
        program->spec(64,64,64);
        program->bind({int64_vocabulary, string_vocabulary_s, tensor_dict[X_input]->shape(), tensor_dict[Y_output]->shape()} 
                        , *string_vocabulary
                        , tensor_dict[X_input], tensor_dict[Y_output] );
    }

    vuh::Device* DictVectorizer::_get_device() {
        for(auto t_name: inputs) {
            if(tensor_dict.end() != tensor_dict.find(t_name)) return tensor_dict[t_name]->dev;
        }
        return device;
    }
};

#endif
