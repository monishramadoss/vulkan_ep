#ifndef LSTM_H
#define LSTM_H

#include <vector>
#include "../layer.h"
#include "../kernel/vuh.h"

namespace backend {
    class LSTM : public Layer {
        struct Params{
            
			Shape_t X;
			Shape_t W;
			Shape_t R;
			Shape_t B;
			Shape_t sequence_lens;
			Shape_t initial_h;
			Shape_t initial_c;
			Shape_t P;
			Shape_t Y;
			Shape_t Y_h;
			Shape_t Y_c;
			float* activation_alpha;
			float* activation_beta;
			std::vector<std::string> activations;
			float clip;
			int direction;
			int hidden_size;
			int input_forget;
        };

        vuh::Program<Specs, Params>* program;

        vuh::Device* _get_device() {
            for(auto t_name: inputs) {
                if(tensor_dict.end() != tensor_dict.find(t_name)) {
                    return tensor_dict[t_name]->dev;
                }
            }
            return device;
        }

        //inputs
		std::string X;
		std::string W;
		std::string R;
		std::string B;
		std::string sequence_lens;
		std::string initial_h;
		std::string initial_c;
		std::string P;

        //outputs
		std::string Y;
		std::string Y_h;
		std::string Y_c;


    public:
        LSTM(std::string n, std::vector<std::string> i, std::vector<std::string> o, std::map<std::string, std::vector<std::string>> a): Layer(n, i, o, a) {
        //inputs
			 X = i[0];
			 W = i[1];
			 R = i[2];
			 B = i[3];
			 sequence_lens = i[4];
			 initial_h = i[5];
			 initial_c = i[6];
			 P = i[7];
        //outputs
			 Y = o[0];
			 Y_h = o[1];
			 Y_c = o[2];

            program = new vuh::Program<Specs, Params>(*_get_device(), (file_path + std::string("\shaders/bin/lstm.spv")).c_str());
            program->grid(1024/PROCESSKERNEL_SIZE, 1024/PROCESSKERNEL_SIZE, 64/PROCESSKERNEL_SIZE);
			program->spec(64,64,64);
            program->bind({}, tensor_dict[Y],tensor_dict[Y_h],tensor_dict[Y_c], tensor_dict[X],tensor_dict[W],tensor_dict[R],tensor_dict[B],tensor_dict[sequence_lens],tensor_dict[initial_h],tensor_dict[initial_c],tensor_dict[P]);

        }
        
        //vuh::Array<float>& operator()(const vuh::Array<float>& t) {            
        //}

        void forward(){
            
        }

       /* std::vector<uint32_t> output_shape(){
            for(auto t_name : inputs){
                if(tensor_dict.end() == tensor_dict.find(t_name) && layer_dict.end() != layer_dict.find(t_name)){
                    //need to do math
                    return layer_dict[t_name]->output_shape();
                }
                else if (tensor_dict.end() != tensor_dict.find(t_name) && layer_dict.end() == layer_dict.find(t_name)){
                    //need to do math
                    return tensor_dict[t_name]->dims;
                }

            }
            for(auto t_name : outputs){
                if(tensor_dict.end() != tensor_dict.find(t_name) && layer_dict.end() == layer_dict.find(t_name)){
                    return tensor_dict[t_name]->dims;
                }
            }
        }*/

        void build_pipeline(){
           // std::vector<Tensor> x;
           // for(auto t_name : inputs)
           //     x.push_back(*tensor_dict[t_name]);
            //program->bind({}, );
		    
        }

        ~LSTM(){}

    };
}

#endif
