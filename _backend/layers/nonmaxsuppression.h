#ifndef NONMAXSUPPRESSION_H
#define NONMAXSUPPRESSION_H //NonMaxSuppression

//INPUTS:                   boxes, scores
//OPTIONAL_INPUTS:          max_output_boxes_per_class, iou_threshold, score_threshold
//OUTPUS:                   selected_indices
//OPTIONAL_OUTPUTS:         
//PARAMETERS:               
//PARAMETER_TYPES:          
//OPTIONAL_PARAMETERS:      center_point_box
//OPTIONAL_PARAMETERS_TYPE: INT

#include <vector>
#include "../layer.h"
#include "../kernel/vuh.h"

namespace backend {
    class NonMaxSuppression : public Layer {
        
        vuh::Device* _get_device();

        struct Params{ };
        vuh::Program<Specs, Params>* program;

    public:
        NonMaxSuppression(std::string n, std::vector<std::string> i, std::vector<std::string> o, std::map<std::string, std::vector<std::string>> a);
        void forward(){ program->run(); }
         
         //std::vector<uint32_t> output_shape();
   
        ~NonMaxSuppression(){}
    };
}


namespace backend {    
    NonMaxSuppression::NonMaxSuppression(std::string n, std::vector<std::string> i, std::vector<std::string> o, std::map<std::string, std::vector<std::string>> a) : Layer(n, i, o, a) {            
            program = new vuh::Program<Specs, Params>(*_get_device(), (file_path + std::string("\shaders/bin/nonmaxsuppression.spv")).c_str());
            program->grid(1024/PROCESSKERNEL_SIZE, 1024/PROCESSKERNEL_SIZE, 64/PROCESSKERNEL_SIZE);
			program->spec(64,64,64);
            //program->bind({}, );
    }

    vuh::Device* NonMaxSuppression::_get_device() {
            for(auto t_name: inputs) {
                if(tensor_dict.end() != tensor_dict.find(t_name)) return tensor_dict[t_name]->dev;
            }
            return device;
    }


};

#endif
