#ifndef XOR_H
#define XOR_H

#include "kernel/kernel.hpp"
#include "kernel/layer.hpp"

namespace kernel {
	namespace layers {
		class Xor : public layer
		{
		public:
			Xor();
			bool forward(tensor& in, tensor& in2, tensor& out);
			void reshapeOutTensor(tensor& in, tensor& out);
			virtual bool forward(std::vector<tensor>& ins, std::vector<tensor>& outs);
		private:
			bool computeGroupCount();
			int m_total;
		};
	}
}

#endif