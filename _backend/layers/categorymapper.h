#ifndef CATEGORYMAPPER_H
#define CATEGORYMAPPER_H //CategoryMapper

//INPUTS:                   X_input
//OPTIONAL_INPUTS:          
//OUTPUS:                   Y_output
//OPTIONAL_OUTPUTS:         
//PARAMETERS:               
//PARAMETER_TYPES:          
//OPTIONAL_PARAMETERS:      cats_int64s, cats_strings, default_int64, default_string
//OPTIONAL_PARAMETERS_TYPE: Shape_t, Tensor*, int, int



namespace backend {
    class CategoryMapper : public Layer {
        
        vuh::Device* _get_device();

        struct Params{
            Shape_t cats_int64s; int default_int64; int default_string;
			
            //input
            Shape_t X_input;
            
            //output
            Shape_t Y_output;
            
        };

        vuh::Program<Specs, Params>* program;

    public:
        CategoryMapper(std::string n, std::vector<std::string> i, std::vector<std::string> o, std::map<std::string, std::vector<std::string>> a);
        void forward(){ program->run(); }
        
        Shape_t cats_int64s; Tensor* cats_strings; int default_int64; int default_string;
		
        //input
        std::string X_input;
        
        //output
        std::string Y_output;
        
        //std::vector<uint32_t> output_shape();
   
        ~CategoryMapper(){}
    };
}


namespace backend {    
    CategoryMapper::CategoryMapper(std::string n, std::vector<std::string> i, std::vector<std::string> o, std::map<std::string, std::vector<std::string>> a) : Layer(n, i, o, a) {            
            program = new vuh::Program<Specs, Params>(*_get_device(), (file_path + std::string("\shaders/bin/categorymapper.spv")).c_str());
            program->grid(1024/PROCESSKERNEL_SIZE, 1024/PROCESSKERNEL_SIZE, 64/PROCESSKERNEL_SIZE);
			program->spec(64,64,64);
            program->bind({cats_int64s, default_int64, default_string, tensor_dict[X_input]->shape(), tensor_dict[Y_output]->shape()}, 
                            tensor_dict[X_input],
                            tensor_dict[Y_output] );
    }

    vuh::Device* CategoryMapper::_get_device() {
            for(auto t_name: inputs) {
                if(tensor_dict.end() != tensor_dict.find(t_name)) return tensor_dict[t_name]->dev;
            }
            return device;
    }
};

#endif
