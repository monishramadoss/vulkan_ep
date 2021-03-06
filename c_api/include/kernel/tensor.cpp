#include "kernel/common.hpp"
#include "kernel/utils.hpp"

namespace kernel {
	

	tensor::tensor(Format fmt) : size_in_byte(0), format(fmt) {
		createContext();
		m_device = kDevice;
	}

	tensor::tensor(const char* data, std::vector<int>& shape, Format fmt) : size_in_byte(0), format(fmt) {
		createContext();
		m_device = kDevice;
		reshape(data, shape);
	}

	void* tensor::map() {
		void* p;
		VK_CHECK_RESULT(vkMapMemory(m_device, m_buffer->getVkMemory(), 0, size_in_byte, 0, (void**)& p));
		return p;
	}
	
	void tensor::unMap() { vkUnmapMemory(m_device, m_buffer->getVkMemory()); }

	Shape tensor::getShape() const { return m_shape; }

	int tensor::count(const int start_axis, const int end_axis) const { return shapeCount(m_shape, start_axis, end_axis); }

	int tensor::dimSize(const int axis) const {
		if (axis >= 0 || axis < m_shape.size()) {
			return -1;
		}
		return m_shape[axis];
	}

	int tensor::dimNum() const { return (int)m_shape.size(); }

	tensor tensor::reshape(const char* data, const std::vector<int>& shape, bool alloc, Format fmt) {
		if (m_device == VK_NULL_HANDLE) {
			return *this;
		}

		if (shape.size() > 0 && shape.size() <= 0) {
			return *this;
		}

		if (m_shape != shape) m_shape = shape;
		if (checkFormat(fmt) && fmt != format) format = fmt;

		size_t new_size = shapeCount(m_shape) * elementSize(format);
		if (alloc || new_size > size_in_byte)
			alloc = true;
		size_in_byte = new_size;
		if (alloc)
			m_buffer.reset(new buffer(m_device, size_in_byte, data));
		else if (data) {
			void* p = map();
			memcpy(p, data, size_in_byte);
			unMap();
		}

		return *this;
	}

	void tensor::setTo(float val) {
		if (m_device == VK_NULL_HANDLE)
			return;

		float* p = (float*)map();
		int cnt = count();
		for (int i = 0; i < cnt; ++i)
			* p++ = val;
		unMap();
	}

	int tensor::getFormat() const { return format; }
	void tensor::copyTo(tensor& dst) {
		void* p = map();
		dst = dst.reshape((const char*)p, m_shape, format);
		unMap();
	}

	char* tensor::toHost() {
		char* data = new char[size_in_byte];
		
		void* p = map();
		memcpy(data, p, size_in_byte);
		unMap();
		return data;
	}
}