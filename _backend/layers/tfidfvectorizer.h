#ifndef TFIDFVECTORIZER_H
#define TFIDFVECTORIZER_H 
#include <pybind11/pybind11.h>
#include "../layer.h"
/*

This transform extracts n-grams from the input sequence and save them as a vector. Input can
be either a 1-D or 2-D tensor. For 1-D input, output is the n-gram representation of that input.
For 2-D input, the output is also a  2-D tensor whose i-th row is the n-gram representation of the i-th input row.
More specifically, if input shape is [C], the corresponding output shape would be [max(ngram_indexes) + 1].
If input shape is [N, C], this operator produces a [N, max(ngram_indexes) + 1]-tensor.

In contrast to standard n-gram extraction, here, the indexes of extracting an n-gram from the original
sequence are not necessarily consecutive numbers. The discontinuity between indexes are controlled by the number of skips.
If the number of skips is 2, we should skip two tokens when scanning through the original sequence.
Let's consider an example. Assume that input sequence is [94, 17, 36, 12, 28] and the number of skips is 2.
The associated 2-grams are [94, 12] and [17, 28] respectively indexed by [0, 3] and [1, 4].
If the number of skips becomes 0, the 2-grams generated are [94, 17], [17, 36], [36, 12], [12, 28]
indexed by [0, 1], [1, 2], [2, 3], [3, 4], respectively.

The output vector (denoted by Y) stores the count of each n-gram;
Y[ngram_indexes[i]] indicates the times that the i-th n-gram is found. The attribute ngram_indexes is used to determine the mapping
between index i and the corresponding n-gram's output coordinate. If pool_int64s is [94, 17, 17, 36], ngram_indexes is [1, 0],
ngram_counts=[0, 0], then the Y[0] (first element in Y) and Y[1] (second element in Y) are the counts of [17, 36] and [94, 17],
respectively. An n-gram which cannot be found in pool_strings/pool_int64s should be ignored and has no effect on the output.
Note that we may consider all skips up to S when generating the n-grams.

The examples used above are true if mode is "TF". If mode is "IDF", all the counts larger than 1 would be truncated to 1 and
the i-th element in weights would be used to scale (by multiplication) the count of the i-th n-gram in pool. If mode is "TFIDF",
this operator first computes the counts of all n-grams and then scale them by the associated values in the weights attribute.

Only one of pool_strings and pool_int64s can be set. If pool_int64s is set, the input should be an integer tensor.
If pool_strings is set, the input must be a string tensor.

input: Input for n-gram extraction
output: Ngram results

*/
//TfIdfVectorizer
//INPUTS:                   X_input
//OPTIONAL_INPUTS:          
//OUTPUS:                   Y_output
//OPTIONAL_OUTPUTS:         
//PARAMETERS:               max_gram_length, max_skip_count, min_gram_length, mode, ngram_counts, ngram_indexes
//PARAMETER_TYPES:          int, int, int, int, Shape_t, Shape_t
//OPTIONAL_PARAMETERS:      pool_int64s, pool_strings, weights
//OPTIONAL_PARAMETERS_TYPE: Shape_t, Tensor*, Tensor*

namespace py = pybind11;

//class stuff
namespace backend {   

    class TfIdfVectorizer : public Layer {
        typedef struct {    
            int max_gram_length; int max_skip_count; int min_gram_length; int mode; Shape_t ngram_counts; Shape_t ngram_indexes; Shape_t pool_int64s; Tensor* pool_strings; Tensor* weights;
        } parameter_descriptor;  

        typedef struct {
            Tensor* X_input;
            
        } input_desriptor;

        typedef struct {
            Tensor* Y_output;
            
        } output_descriptor;

        typedef struct {
            int max_gram_length; int max_skip_count; int min_gram_length; int mode; Shape_t ngram_counts; Shape_t ngram_indexes; Shape_t pool_int64s;
		Shape_t pool_strings; Shape_t weights;
            Shape_t X_input;
            
            Shape_t Y_output;
            
        } binding_descriptor;

        parameter_descriptor parameters;
        input_desriptor      input;
        output_descriptor    output;
        binding_descriptor   binding;

        vuh::Device* _get_device();
        vuh::Program<Specs, binding_descriptor>* program;        

    public:
        TfIdfVectorizer(std::string, parameter_descriptor _parameter_descriptor);
    
        void forward() { program->run(); }
        
        void call(); 
        void init(); 

        ~TfIdfVectorizer() {}

    };
    
}


//cpp stuff
namespace backend {    
   
    TfIdfVectorizer::TfIdfVectorizer(std::string n, parameter_descriptor _parameter_descriptor) : Layer(n) {
        parameters = _parameter_descriptor;
        program = new vuh::Program<Specs, binding_descriptor>(*_get_device(), std::string(file_path + std::string("/shaders/bin/tfidfvectorizer.spv")).c_str());
        program->grid(1024/PROCESSKERNEL_SIZE, 1024/PROCESSKERNEL_SIZE, 64/PROCESSKERNEL_SIZE);
        program->spec(64,64,64);
      
    }  

    vuh::Device* TfIdfVectorizer::_get_device() {
        for(auto t_name: inputs) {
            if(tensor_dict.end() != tensor_dict.find(t_name)) return tensor_dict[t_name]->dev;
        }
        return device;
    }
    
    void TfIdfVectorizer::init() {
		binding.X_input = input.X_input->shape();
 
		binding.Y_output = output.Y_output->shape();
 
		binding.max_gram_length = parameters.max_gram_length;
  		binding.max_skip_count = parameters.max_skip_count;
  		binding.min_gram_length = parameters.min_gram_length;
  		binding.mode = parameters.mode;
  		binding.ngram_counts = parameters.ngram_counts;
  		binding.ngram_indexes = parameters.ngram_indexes;
  		binding.pool_int64s = parameters.pool_int64s;
  		binding.pool_strings = parameters.pool_strings->shape();
  		binding.weights = parameters.weights->shape();
 
        program->bind(binding, *parameters.pool_strings->data(), *parameters.weights->data(), *input.X_input->data(), *output.Y_output->data());
    }
    
    void TfIdfVectorizer::call(){
       
    }


}



//python stuff
/*namespace backend {
    PYBIND11_MODULE(_backend, m) {
        py::class_<TfIdfVectorizer, Layer>(m, "TfIdfVectorizer")
            .def("forward", &TfIdfVectorizer::forward);    
    }
}*/

#endif
