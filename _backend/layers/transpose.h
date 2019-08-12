#ifndef TRANSPOSE_H
#define TRANSPOSE_H //Transpose

//INPUTS:                   data_input
//OPTIONAL_INPUTS:          
//OUTPUS:                   transposed_output
//OPTIONAL_OUTPUTS:         
//PARAMETERS:               
//PARAMETER_TYPES:          
//OPTIONAL_PARAMETERS:      perm
//OPTIONAL_PARAMETERS_TYPE: Shape_t



namespace backend {
    class Transpose : public Layer {
        
        vuh::Device* _get_device();

        struct Params{
            Shape_t perm;
			
            //input
            Shape_t data_input;
            
            //output
            Shape_t transposed_output;
            
        };

        vuh::Program<Specs, Params>* program;

    public:
        Transpose(std::string n, std::vector<std::string> i, std::vector<std::string> o, std::map<std::string, std::vector<std::string>> a);
        void forward(){ program->run(); }
        
        Shape_t perm;
		
        //input
        std::string data_input;
        
        //output
        std::string transposed_output;
        
        //std::vector<uint32_t> output_shape();
   
        ~Transpose(){}
    };
}


namespace backend {    
    Transpose::Transpose(std::string n, std::vector<std::string> i, std::vector<std::string> o, std::map<std::string, std::vector<std::string>> a) : Layer(n, i, o, a) {            
            program = new vuh::Program<Specs, Params>(*_get_device(), (file_path + std::string("\shaders/bin/transpose.spv")).c_str());
            program->grid(1024/PROCESSKERNEL_SIZE, 1024/PROCESSKERNEL_SIZE, 64/PROCESSKERNEL_SIZE);
			program->spec(64,64,64);
            program->bind({perm, tensor_dict[data_input]->shape(), tensor_dict[transposed_output]->shape()}, 
                            tensor_dict[data_input],
                            tensor_dict[transposed_output] );
    }

    vuh::Device* Transpose::_get_device() {
            for(auto t_name: inputs) {
                if(tensor_dict.end() != tensor_dict.find(t_name)) return tensor_dict[t_name]->dev;
            }
            return device;
    }
};

#endif
