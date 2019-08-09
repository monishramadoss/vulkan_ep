#ifndef EXPAND_H
#define EXPAND_H //Expand

//INPUTS:                   input_input, shape_input
//OPTIONAL_INPUTS:          
//OUTPUS:                   output_input_o
//OPTIONAL_OUTPUTS:         
//PARAMETERS:               
//PARAMETER_TYPES:          
//OPTIONAL_PARAMETERS:      
//OPTIONAL_PARAMETERS_TYPE: 



namespace backend {
    class Expand : public Layer {
        
        vuh::Device* _get_device();

        struct Params{
            
			
            //input
            Shape_t input_input; Shape_t shape_input;
            
            //output
            Shape_t output_input_o;
            
        };

        vuh::Program<Specs, Params>* program;

    public:
        Expand(std::string n, std::vector<std::string> i, std::vector<std::string> o, std::map<std::string, std::vector<std::string>> a);
        void forward(){ program->run(); }
        
        
		
        //input
        std::string input_input; std::string shape_input;
        
        //output
        std::string output_input_o;
        
        //std::vector<uint32_t> output_shape();
   
        ~Expand(){}
    };
}


namespace backend {    
    Expand::Expand(std::string n, std::vector<std::string> i, std::vector<std::string> o, std::map<std::string, std::vector<std::string>> a) : Layer(n, i, o, a) {            
            program = new vuh::Program<Specs, Params>(*_get_device(), (file_path + std::string("\shaders/bin/expand.spv")).c_str());
            program->grid(1024/PROCESSKERNEL_SIZE, 1024/PROCESSKERNEL_SIZE, 64/PROCESSKERNEL_SIZE);
			program->spec(64,64,64);
            program->bind({}, 
                            tensor_dict[input_input], tensor_dict[shape_input],
                            tensor_dict[output_input_o] );
    }

    vuh::Device* Expand::_get_device() {
            for(auto t_name: inputs) {
                if(tensor_dict.end() != tensor_dict.find(t_name)) return tensor_dict[t_name]->dev;
            }
            return device;
    }
};

#endif
