#ifndef ABS_H
#define ABS_H

#include <vector>
#include "../layer.h"
#include "../tensor.h"
#include "../kernel/vuh.h"

namespace backend {
    class Abs : public Layer {
    public:
        Abs() {
        }
	
		Tensor& operator()(const Tensor& it){}

        void forward(){

        }

        void build_pipeline(){
            
        }

        ~Abs(){}

    };
}

#endif
