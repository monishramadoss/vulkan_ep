#ifndef ADD_H
#define ADD_H //Add

//INPUTS:                   A_input, B_input
//OPTIONAL_INPUTS:          
//OUTPUS:                   C_output
//OPTIONAL_OUTPUTS:         
//PARAMETERS:               
//PARAMETER_TYPES:          
//OPTIONAL_PARAMETERS:      
//OPTIONAL_PARAMETERS_TYPE: 



namespace backend {
    class Add : public Layer {
        
        vuh::Device* _get_device();

        struct Params{
            
			
            //input
            Shape_t A_input; Shape_t B_input;
            
            //output
            Shape_t C_output;
            
        };

        vuh::Program<Specs, Params>* program;

    public:
        Add(std::string n, std::vector<std::string> i, std::vector<std::string> o, std::map<std::string, std::vector<std::string>> a);
        void forward(){ program->run(); }
        
        
		
        //input
        std::string A_input; std::string B_input;
        
        //output
        std::string C_output;
        
        //std::vector<uint32_t> output_shape();
   
        ~Add(){}
    };
}


namespace backend {    
    Add::Add(std::string n, std::vector<std::string> i, std::vector<std::string> o, std::map<std::string, std::vector<std::string>> a) : Layer(n, i, o, a) {            
            program = new vuh::Program<Specs, Params>(*_get_device(), (file_path + std::string("\shaders/bin/add.spv")).c_str());
            program->grid(1024/PROCESSKERNEL_SIZE, 1024/PROCESSKERNEL_SIZE, 64/PROCESSKERNEL_SIZE);
			program->spec(64,64,64);
            program->bind({tensor_dict[A_input]->shape(), tensor_dict[B_input]->shape(), tensor_dict[C_output]->shape()}, 
                            tensor_dict[A_input], tensor_dict[B_input],
                            tensor_dict[C_output] );
    }

    vuh::Device* Add::_get_device() {
            for(auto t_name: inputs) {
                if(tensor_dict.end() != tensor_dict.find(t_name)) return tensor_dict[t_name]->dev;
            }
            return device;
    }
};

#endif
