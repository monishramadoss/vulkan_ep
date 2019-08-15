#ifndef LSTM_H
#define LSTM_H 
#include <pybind11/pybind11.h>
#include "../layer.h"
/*

Computes an one-layer LSTM. This operator is usually supported via some
custom implementation such as CuDNN.

Notations:

`X` - input tensor

`i` - input gate

`o` - output gate

`f` - forget gate

`c` - cell gate

`t` - time step (t-1 means previous time step)

`W[iofc]` - W parameter weight matrix for input, output, forget, and cell gates

`R[iofc]` - R recurrence weight matrix for input, output, forget, and cell gates

`Wb[iofc]` - W bias vectors for input, output, forget, and cell gates

`Rb[iofc]` - R bias vectors for input, output, forget, and cell gates

`P[iof]`  - P peephole weight vector for input, output, and forget gates

`WB[iofc]` - W parameter weight matrix for backward input, output, forget, and cell gates

`RB[iofc]` - R recurrence weight matrix for backward input, output, forget, and cell gates

`WBb[iofc]` - W bias vectors for backward input, output, forget, and cell gates

`RBb[iofc]` - R bias vectors for backward input, output, forget, and cell gates

`PB[iof]`  - P peephole weight vector for backward input, output, and forget gates

`H` - Hidden state

`num_directions` - 2 if direction == bidirectional else 1

Activation functions:

  Relu(x)                - max(0, x)

  Tanh(x)                - (1 - e^{-2x})/(1 + e^{-2x})

  Sigmoid(x)             - 1/(1 + e^{-x})

  (NOTE: Below are optional)

  Affine(x)              - alpha*x + beta

  LeakyRelu(x)           - x if x >= 0 else alpha * x

  ThresholdedRelu(x)     - x if x >= alpha else 0

  ScaledTanh(x)          - alpha*Tanh(beta*x)

  HardSigmoid(x)         - min(max(alpha*x + beta, 0), 1)

  Elu(x)                 - x if x >= 0 else alpha*(e^x - 1)

  Softsign(x)            - x/(1 + |x|)

  Softplus(x)            - log(1 + e^x)

Equations (Default: f=Sigmoid, g=Tanh, h=Tanh):

  - it = f(Xt*(Wi^T) + Ht-1*(Ri^T) + Pi (.) Ct-1 + Wbi + Rbi)

  - ft = f(Xt*(Wf^T) + Ht-1*(Rf^T) + Pf (.) Ct-1 + Wbf + Rbf)

  - ct = g(Xt*(Wc^T) + Ht-1*(Rc^T) + Wbc + Rbc)

  - Ct = ft (.) Ct-1 + it (.) ct

  - ot = f(Xt*(Wo^T) + Ht-1*(Ro^T) + Po (.) Ct + Wbo + Rbo)

  - Ht = ot (.) h(Ct)
This operator has **optional** inputs/outputs. See [the doc](IR.md) for more details about the representation of optional arguments. An empty string may be used in the place of an actual argument's name to indicate a missing argument. Trailing optional arguments (those not followed by an argument that is present) may also be simply omitted.

input: The input sequences packed (and potentially padded) into one 3-D tensor with the shape of `[seq_length, batch_size, input_size]`.
input: The weight tensor for the gates. Concatenation of `W[iofc]` and `WB[iofc]` (if bidirectional) along dimension 0. The tensor has shape `[num_directions, 4*hidden_size, input_size]`.
input: The recurrence weight tensor. Concatenation of `R[iofc]` and `RB[iofc]` (if bidirectional) along dimension 0. This tensor has shape `[num_directions, 4*hidden_size, hidden_size]`.
input: The bias tensor for input gate. Concatenation of `[Wb[iofc], Rb[iofc]]`, and `[WBb[iofc], RBb[iofc]]` (if bidirectional) along dimension 0. This tensor has shape `[num_directions, 8*hidden_size]`. Optional: If not specified - assumed to be 0.
input: Optional tensor specifying lengths of the sequences in a batch. If not specified - assumed all sequences in the batch to have length `seq_length`. It has shape `[batch_size]`.
input: Optional initial value of the hidden. If not specified - assumed to be 0. It has shape `[num_directions, batch_size, hidden_size]`.
input: Optional initial value of the cell. If not specified - assumed to be 0. It has shape `[num_directions, batch_size, hidden_size]`.
input: The weight tensor for peepholes. Concatenation of `P[iof]` and `PB[iof]` (if bidirectional) along dimension 0. It has shape `[num_directions, 3*hidde_size]`. Optional: If not specified - assumed to be 0.
output: A tensor that concats all the intermediate output values of the hidden. It has shape `[seq_length, num_directions, batch_size, hidden_size]`. 
output: The last output value of the hidden. It has shape `[num_directions, batch_size, hidden_size]`.
output: The last output value of the cell. It has shape `[num_directions, batch_size, hidden_size]`.

*/
//LSTM
//INPUTS:                   X_input, W_input, R_input
//OPTIONAL_INPUTS:          B_input_opt, sequence_lens_input_opt, initial_h_input_opt, initial_c_input_opt, P_input_opt
//OUTPUS:                   
//OPTIONAL_OUTPUTS:         Y_output_opt, Y_h_output_opt, Y_c_output_opt
//PARAMETERS:               
//PARAMETER_TYPES:          
//OPTIONAL_PARAMETERS:      activation_alpha, activation_beta, activations, clip, direction, hidden_size, input_forget
//OPTIONAL_PARAMETERS_TYPE: Tensor*, Tensor*, Tensor*, float, int, int, int

namespace py = pybind11;

//class stuff
namespace backend {   

    class LSTM : public Layer {
        typedef struct {    
            Tensor* activation_alpha; Tensor* activation_beta; Tensor* activations; float clip; int direction; int hidden_size; int input_forget;
        } parameter_descriptor;  

        typedef struct {
            Tensor* X_input; Tensor* W_input; Tensor* R_input;
            Tensor* B_input_opt; Tensor* sequence_lens_input_opt; Tensor* initial_h_input_opt; Tensor* initial_c_input_opt; Tensor* P_input_opt;
        } input_desriptor;

        typedef struct {
            
            Tensor* Y_output_opt; Tensor* Y_h_output_opt; Tensor* Y_c_output_opt;
        } output_descriptor;

        typedef struct {
            float clip; int direction; int hidden_size; int input_forget;
		Shape_t activation_alpha; Shape_t activation_beta; Shape_t activations;
            Shape_t X_input; Shape_t W_input; Shape_t R_input;
            Shape_t B_input_opt; Shape_t sequence_lens_input_opt; Shape_t initial_h_input_opt; Shape_t initial_c_input_opt; Shape_t P_input_opt;
            
            Shape_t Y_output_opt; Shape_t Y_h_output_opt; Shape_t Y_c_output_opt;
        } binding_descriptor;

        parameter_descriptor parameters;
        input_desriptor      input;
        output_descriptor    output;
        binding_descriptor   binding;

        vuh::Device* _get_device();
        vuh::Program<Specs, binding_descriptor>* program;        

    public:
        LSTM(std::string, parameter_descriptor _parameter_descriptor);
    
        void forward() { program->run(); }
        
        void call(); 
        void init(); 

        ~LSTM() {}

    };
    
}


//cpp stuff
namespace backend {    
   
    LSTM::LSTM(std::string n, parameter_descriptor _parameter_descriptor) : Layer(n) {
        parameters = _parameter_descriptor;
        program = new vuh::Program<Specs, binding_descriptor>(*_get_device(), std::string(file_path + std::string("/shaders/bin/lstm.spv")).c_str());
        program->grid(1024/PROCESSKERNEL_SIZE, 1024/PROCESSKERNEL_SIZE, 64/PROCESSKERNEL_SIZE);
        program->spec(64,64,64);
      
    }  

    vuh::Device* LSTM::_get_device() {
        for(auto t_name: inputs) {
            if(tensor_dict.end() != tensor_dict.find(t_name)) return tensor_dict[t_name]->dev;
        }
        return device;
    }
    
    void LSTM::init() {
		binding.X_input = input.X_input->shape();
  		binding.W_input = input.W_input->shape();
  		binding.R_input = input.R_input->shape();
  		binding.B_input_opt = input.B_input_opt->shape();
  		binding.sequence_lens_input_opt = input.sequence_lens_input_opt->shape();
  		binding.initial_h_input_opt = input.initial_h_input_opt->shape();
  		binding.initial_c_input_opt = input.initial_c_input_opt->shape();
  		binding.P_input_opt = input.P_input_opt->shape();
 
		binding.Y_output_opt = output.Y_output_opt->shape();
  		binding.Y_h_output_opt = output.Y_h_output_opt->shape();
  		binding.Y_c_output_opt = output.Y_c_output_opt->shape();
 
		binding.clip = parameters.clip;
  		binding.direction = parameters.direction;
  		binding.hidden_size = parameters.hidden_size;
  		binding.input_forget = parameters.input_forget;
  		binding.activation_alpha = parameters.activation_alpha->shape();
  		binding.activation_beta = parameters.activation_beta->shape();
  		binding.activations = parameters.activations->shape();
 
        program->bind(binding, *parameters.activation_alpha->data(), *parameters.activation_beta->data(), *parameters.activations->data(), *input.X_input->data(), *input.W_input->data(), *input.R_input->data(), *input.B_input_opt->data(), *input.sequence_lens_input_opt->data(), *input.initial_h_input_opt->data(), *input.initial_c_input_opt->data(), *input.P_input_opt->data(), *output.Y_output_opt->data(), *output.Y_h_output_opt->data(), *output.Y_c_output_opt->data());
    }
    
    void LSTM::call(){
       
    }


}



//python stuff
/*namespace backend {
    PYBIND11_MODULE(_backend, m) {
        py::class_<LSTM, Layer>(m, "LSTM")
            .def("forward", &LSTM::forward);    
    }
}*/

#endif
