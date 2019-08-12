#ifndef PAD_H
#define PAD_H //Pad

//INPUTS:                   data_input
//OPTIONAL_INPUTS:          
//OUTPUS:                   output_output
//OPTIONAL_OUTPUTS:         
//PARAMETERS:               pads
//PARAMETER_TYPES:          Shape_t
//OPTIONAL_PARAMETERS:      mode, value
//OPTIONAL_PARAMETERS_TYPE: int, float



namespace backend {
    class Pad : public Layer {
        
        vuh::Device* _get_device();

        struct Params{
            Shape_t pads; int mode; float value;
			
            //input
            Shape_t data_input;
            
            //output
            Shape_t output_output;
            
        };

        vuh::Program<Specs, Params>* program;

    public:
        Pad(std::string n, std::vector<std::string> i, std::vector<std::string> o, std::map<std::string, std::vector<std::string>> a);
        void forward(){ program->run(); }
        
        Shape_t pads; int mode; float value;
		
        //input
        std::string data_input;
        
        //output
        std::string output_output;
        
        //std::vector<uint32_t> output_shape();
   
        ~Pad(){}
    };
}


namespace backend {    
    Pad::Pad(std::string n, std::vector<std::string> i, std::vector<std::string> o, std::map<std::string, std::vector<std::string>> a) : Layer(n, i, o, a) {            
            program = new vuh::Program<Specs, Params>(*_get_device(), (file_path + std::string("\shaders/bin/pad.spv")).c_str());
            program->grid(1024/PROCESSKERNEL_SIZE, 1024/PROCESSKERNEL_SIZE, 64/PROCESSKERNEL_SIZE);
			program->spec(64,64,64);
            program->bind({pads, mode, value, tensor_dict[data_input]->shape(), tensor_dict[output_output]->shape()}, 
                            tensor_dict[data_input],
                            tensor_dict[output_output] );
    }

    vuh::Device* Pad::_get_device() {
            for(auto t_name: inputs) {
                if(tensor_dict.end() != tensor_dict.find(t_name)) return tensor_dict[t_name]->dev;
            }
            return device;
    }
};

#endif
