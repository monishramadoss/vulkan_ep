#ifndef ONEHOTENCODER_H
#define ONEHOTENCODER_H //OneHotEncoder

//INPUTS:                   X
//OPTIONAL_INPUTS:          
//OUTPUS:                   Y
//OPTIONAL_OUTPUTS:         
//PARAMETERS:               
//PARAMETER_TYPES:          
//OPTIONAL_PARAMETERS:      cats_int64s, cats_strings, zeros
//OPTIONAL_PARAMETERS_TYPE: INTS, STRINGS, INT

#include <vector>
#include "../layer.h"
#include "../kernel/vuh.h"

namespace backend {
    class OneHotEncoder : public Layer {
        
        vuh::Device* _get_device();

        struct Params{ };
        vuh::Program<Specs, Params>* program;

    public:
        OneHotEncoder(std::string n, std::vector<std::string> i, std::vector<std::string> o, std::map<std::string, std::vector<std::string>> a);
        void forward(){ program->run(); }
         
         //std::vector<uint32_t> output_shape();
   
        ~OneHotEncoder(){}
    };
}


namespace backend {    
    OneHotEncoder::OneHotEncoder(std::string n, std::vector<std::string> i, std::vector<std::string> o, std::map<std::string, std::vector<std::string>> a) : Layer(n, i, o, a) {            
            program = new vuh::Program<Specs, Params>(*_get_device(), (file_path + std::string("\shaders/bin/onehotencoder.spv")).c_str());
            program->grid(1024/PROCESSKERNEL_SIZE, 1024/PROCESSKERNEL_SIZE, 64/PROCESSKERNEL_SIZE);
			program->spec(64,64,64);
            //program->bind({}, );
    }

    vuh::Device* OneHotEncoder::_get_device() {
            for(auto t_name: inputs) {
                if(tensor_dict.end() != tensor_dict.find(t_name)) return tensor_dict[t_name]->dev;
            }
            return device;
    }


};

#endif
