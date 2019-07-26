
#ifndef REDUCELOGSUMEXP_H
#define REDUCELOGSUMEXP_H

#include <vector>
#include "../layer.h"
#include "../kernel/vuh.h"

namespace backend {
    class ReduceLogSumExp : public Layer {
    using Specs = vuh::typelist<uint32_t, uint32_t, uint32_t>;
    struct Params {

		int[] axes;
		int keepdims;
    };
    vuh::Program<Specs, Params>* program;

    public:
       ReduceLogSumExp (){
            device =  new vuh::Device(instance->devices().at(0));
		    program = new vuh::Program<Specs, Params>(*device, "../shaders/bin/reducelogsumexp.spv");
		    d_input = new vuh::Array<float>(*device, input);
		    d_output = new vuh::Array<float>(*device, output);
        }

        ~ReduceLogSumExp () {}

    };
}

#endif