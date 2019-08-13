#ifndef CONVTRANSPOSE_H
#define CONVTRANSPOSE_H //ConvTranspose

#include "../layer.h"

//INPUTS:                   X_input, W_input
//OPTIONAL_INPUTS:          B_input_o
//OUTPUS:                   Y_output
//OPTIONAL_OUTPUTS:         
//PARAMETERS:               
//PARAMETER_TYPES:          
//OPTIONAL_PARAMETERS:      auto_pad, dilations, group, kernel_shape, output_padding, output_shape, pads, strides
//OPTIONAL_PARAMETERS_TYPE: int, Shape_t, int, Shape_t, Shape_t, Shape_t, Shape_t, Shape_t



namespace backend {
    class ConvTranspose : public Layer {
        
        vuh::Device* _get_device();

        struct Params{
            int auto_pad; Shape_t dilations; int group; Shape_t kernel_shape; Shape_t output_padding; Shape_t output_shape; Shape_t pads; Shape_t strides;
			
            //input
            Shape_t X_input; Shape_t W_input;
            Shape_t B_input_o;
            //output
            Shape_t Y_output;
            
        };

        vuh::Program<Specs, Params>* program;

    public:
        ConvTranspose(std::string n, std::vector<std::string> i, std::vector<std::string> o, std::map<std::string, std::vector<std::string>> a);
        void forward() { program->run(); }
        
        int auto_pad; Shape_t dilations; int group; Shape_t kernel_shape; Shape_t output_padding; Shape_t output_shape; Shape_t pads; Shape_t strides;
		
        //input
        std::string X_input; std::string W_input;
        std::string B_input_o;
        //output
        std::string Y_output;
        
        //std::vector<uint32_t> output_shape();
   
        ~ConvTranspose() {}
    };
}


namespace backend {    
    ConvTranspose::ConvTranspose(std::string n, std::vector<std::string> i, std::vector<std::string> o, std::map<std::string, std::vector<std::string>> a) : Layer(n, i, o, a) {            
        program = new vuh::Program<Specs, Params>(*_get_device(), std::string(file_path + "/shaders/bin/convtranspose.spv").c_str());
        program->grid(1024/PROCESSKERNEL_SIZE, 1024/PROCESSKERNEL_SIZE, 64/PROCESSKERNEL_SIZE);
        program->spec(64,64,64);
        program->bind({auto_pad, dilations, group, kernel_shape, output_padding, output_shape, pads, strides, tensor_dict[X_input]->shape(), tensor_dict[W_input]->shape(), tensor_dict[B_input_o]->shape(), tensor_dict[Y_output]->shape()} 
                        
                        , tensor_dict[X_input], tensor_dict[W_input], tensor_dict[B_input_o], tensor_dict[Y_output] );
    }

    vuh::Device* ConvTranspose::_get_device() {
        for(auto t_name: inputs) {
            if(tensor_dict.end() != tensor_dict.find(t_name)) return tensor_dict[t_name]->dev;
        }
        return device;
    }
};

#endif
