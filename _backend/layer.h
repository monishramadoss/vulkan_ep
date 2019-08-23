#pragma once
#ifndef LAYER_H
#define LAYER_H
#include <map>
#include <vector>
#include <string>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
namespace py = pybind11;

#include "tensor.h"
#include "kernel/vuh.h"

namespace backend {
	
#define PROCESSKERNEL_SIZE 32
	
	class Layer
	{
	public:
		std::string name;
		Layer(std::string name) : name(name) {}
		virtual ~Layer() {}
		//virtual void forward() {}
		virtual void init() {}
		virtual void bind() {}
		virtual void build() {}
	protected:
		using Specs = vuh::typelist<uint32_t, uint32_t, uint32_t>;
		//virtual void parameter_proc(std::map<std::string, std::vector<std::string>> a()) {}
	};
}

namespace backend {
	inline std::map<std::string, Layer*> layer_dict;

	template<typename T> std::vector<T> convert(py::list l) {
		std::vector<T> x;
		for (auto i : l)
			x.push_back(i.cast<T>());
		return x;
	}

	inline char static_execution = 0;
}


#endif //!LAYER_H