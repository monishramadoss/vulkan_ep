#ifndef TREEENSEMBLECLASSIFIER_H
#define TREEENSEMBLECLASSIFIER_H //TreeEnsembleClassifier

//INPUTS:                   X_input
//OPTIONAL_INPUTS:          
//OUTPUS:                   Y_input_o, Z_input_o
//OPTIONAL_OUTPUTS:         
//PARAMETERS:               
//PARAMETER_TYPES:          
//OPTIONAL_PARAMETERS:      base_values, class_ids, class_nodeids, class_treeids, class_weights, classlabels_int64s, classlabels_strings, nodes_falsenodeids, nodes_featureids, nodes_hitrates, nodes_missing_value_tracks_true, nodes_modes, nodes_nodeids, nodes_treeids, nodes_truenodeids, nodes_values, post_transform
//OPTIONAL_PARAMETERS_TYPE: Tensor*, Shape_t, Shape_t, Shape_t, Tensor*, Shape_t, Tensor*, Shape_t, Shape_t, Tensor*, Shape_t, Tensor*, Shape_t, Shape_t, Shape_t, Tensor*, int



namespace backend {
    class TreeEnsembleClassifier : public Layer {
        
        vuh::Device* _get_device();

        struct Params{
            Shape_t class_ids; Shape_t class_nodeids; Shape_t class_treeids; Shape_t classlabels_int64s; Shape_t nodes_falsenodeids; Shape_t nodes_featureids; Shape_t nodes_missing_value_tracks_true; Shape_t nodes_nodeids; Shape_t nodes_treeids; Shape_t nodes_truenodeids; int post_transform;
			Shape_t base_values; Shape_t class_weights; Shape_t classlabels_strings; Shape_t nodes_hitrates; Shape_t nodes_modes; Shape_t nodes_values;
            //input
            Shape_t X_input;
            
            //output
            Shape_t Y_input_o; Shape_t Z_input_o;
            
        };

        vuh::Program<Specs, Params>* program;

    public:
        TreeEnsembleClassifier(std::string n, std::vector<std::string> i, std::vector<std::string> o, std::map<std::string, std::vector<std::string>> a);
        void forward(){ program->run(); }
        
        Tensor* base_values; Shape_t class_ids; Shape_t class_nodeids; Shape_t class_treeids; Tensor* class_weights; Shape_t classlabels_int64s; Tensor* classlabels_strings; Shape_t nodes_falsenodeids; Shape_t nodes_featureids; Tensor* nodes_hitrates; Shape_t nodes_missing_value_tracks_true; Tensor* nodes_modes; Shape_t nodes_nodeids; Shape_t nodes_treeids; Shape_t nodes_truenodeids; Tensor* nodes_values; int post_transform;
		Shape_t base_values_t; Shape_t class_weights_t; Shape_t classlabels_strings_t; Shape_t nodes_hitrates_t; Shape_t nodes_modes_t; Shape_t nodes_values_t;
        //input
        std::string X_input;
        
        //output
        std::string Y_input_o; std::string Z_input_o;
        
        //std::vector<uint32_t> output_shape();
   
        ~TreeEnsembleClassifier(){}
    };
}


namespace backend {    
    TreeEnsembleClassifier::TreeEnsembleClassifier(std::string n, std::vector<std::string> i, std::vector<std::string> o, std::map<std::string, std::vector<std::string>> a) : Layer(n, i, o, a) {            
            program = new vuh::Program<Specs, Params>(*_get_device(), (file_path + std::string("\shaders/bin/treeensembleclassifier.spv")).c_str());
            program->grid(1024/PROCESSKERNEL_SIZE, 1024/PROCESSKERNEL_SIZE, 64/PROCESSKERNEL_SIZE);
			program->spec(64,64,64);
            program->bind({class_ids, class_nodeids, class_treeids, classlabels_int64s, nodes_falsenodeids, nodes_featureids, nodes_missing_value_tracks_true, nodes_nodeids, nodes_treeids, nodes_truenodeids, post_transform, base_values_t, class_weights_t, classlabels_strings_t, nodes_hitrates_t, nodes_modes_t, nodes_values_t}, 
                            tensor_dict[X_input],
                            tensor_dict[Y_input_o], tensor_dict[Z_input_o] );
    }

    vuh::Device* TreeEnsembleClassifier::_get_device() {
            for(auto t_name: inputs) {
                if(tensor_dict.end() != tensor_dict.find(t_name)) return tensor_dict[t_name]->dev;
            }
            return device;
    }
};

#endif
