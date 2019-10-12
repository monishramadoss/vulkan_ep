#ifndef ACOSH_H
#define ACOSH_H

#include "kernel/kernel.hpp"
#include "kernel/layer.hpp"

namespace kernel {
	namespace layers {
		class Acosh : public layer
		{
		public:
			Acosh();
			bool forward(tensor& in, tensor& out);
			void reshapeOutTensor(tensor& in, tensor& out);
			virtual bool forward(std::vector<tensor>& ins, std::vector<tensor>& outs);
		private:
			bool computeGroupCount();
			int m_total;			
		};
	}
}

#endif