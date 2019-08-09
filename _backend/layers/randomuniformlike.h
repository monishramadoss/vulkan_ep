#ifndef RANDOMUNIFORMLIKE_H
#define RANDOMUNIFORMLIKE_H //RandomUniformLike

//INPUTS:                   input_input
//OPTIONAL_INPUTS:          
//OUTPUS:                   output_input_o
//OPTIONAL_OUTPUTS:         
//PARAMETERS:               
//PARAMETER_TYPES:          
//OPTIONAL_PARAMETERS:      dtype, high, low, seed
//OPTIONAL_PARAMETERS_TYPE: int, float, float, float



namespace backend {
    class RandomUniformLike : public Layer {
        
        vuh::Device* _get_device();

        struct Params{
            int dtype; float high; float low; float seed;
			
            //input
            Shape_t input_input;
            
            //output
            Shape_t output_input_o;
            
        };

        vuh::Program<Specs, Params>* program;

    public:
        RandomUniformLike(std::string n, std::vector<std::string> i, std::vector<std::string> o, std::map<std::string, std::vector<std::string>> a);
        void forward(){ program->run(); }
        
        int dtype; float high; float low; float seed;
		
        //input
        std::string input_input;
        
        //output
        std::string output_input_o;
        
        //std::vector<uint32_t> output_shape();
   
        ~RandomUniformLike(){}
    };
}


namespace backend {    
    RandomUniformLike::RandomUniformLike(std::string n, std::vector<std::string> i, std::vector<std::string> o, std::map<std::string, std::vector<std::string>> a) : Layer(n, i, o, a) {            
            program = new vuh::Program<Specs, Params>(*_get_device(), (file_path + std::string("\shaders/bin/randomuniformlike.spv")).c_str());
            program->grid(1024/PROCESSKERNEL_SIZE, 1024/PROCESSKERNEL_SIZE, 64/PROCESSKERNEL_SIZE);
			program->spec(64,64,64);
            program->bind({dtype, high, low, seed}, 
                            tensor_dict[input_input],
                            tensor_dict[output_input_o] );
    }

    vuh::Device* RandomUniformLike::_get_device() {
            for(auto t_name: inputs) {
                if(tensor_dict.end() != tensor_dict.find(t_name)) return tensor_dict[t_name]->dev;
            }
            return device;
    }
};

#endif
