#include "command.h"

namespace backend {

	Command::Command(const Device* _dev, uint32_t _queue_family_index) : dev(_dev), queue_family_index(_queue_family_index) {
		create_command_pool();
		create_command_buffer();
		VkFenceCreateInfo fenceCreateInfo;
		fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		fenceCreateInfo.pNext = 0;
		fenceCreateInfo.flags = 0;

		VkResult ret = vkCreateFence(dev->vkdevice(), &fenceCreateInfo, 0, &fence);
		if (ret != VK_SUCCESS)
			fprintf(stderr, "vkCreateFence failed %d\n", ret);
	}

	Command::~Command() {
		vkDestroyFence(dev->vkdevice(), fence, 0);
		vkFreeCommandBuffers(dev->vkdevice(), command_pool, 1, &command_buffer);
		vkDestroyCommandPool(dev->vkdevice(), command_pool, 0);
	}


	int Command::create_command_pool() {
		VkCommandPoolCreateInfo commandPoolCreateInfo;
		commandPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		commandPoolCreateInfo.pNext = 0;
		commandPoolCreateInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
		commandPoolCreateInfo.queueFamilyIndex = queue_family_index;

		VkResult ret = vkCreateCommandPool(dev->vkdevice(), &commandPoolCreateInfo, 0, &command_pool);
		if (ret != VK_SUCCESS) return -1;
		return 0;
	}


	int Command::create_command_buffer() {
		VkCommandBufferAllocateInfo commandBufferAllocateInfo;
		commandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		commandBufferAllocateInfo.pNext = 0;
		commandBufferAllocateInfo.commandPool = command_pool;
		commandBufferAllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		commandBufferAllocateInfo.commandBufferCount = 1;

		VkResult ret = vkAllocateCommandBuffers(dev->vkdevice(), &commandBufferAllocateInfo, &command_buffer);
		if (ret != VK_SUCCESS) return -1;
		return 0;
	}

	int Command::begin_command_buffer() {
		VkCommandBufferBeginInfo commandBufferBeginInfo;
		commandBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		commandBufferBeginInfo.pNext = 0;
		commandBufferBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
		commandBufferBeginInfo.pInheritanceInfo = 0;

		VkResult ret = vkBeginCommandBuffer(command_buffer, &commandBufferBeginInfo);
		if (ret != VK_SUCCESS) return -1;
		return 0;
	}

	int Command::end_command_buffer() {
		VkResult ret = vkEndCommandBuffer(command_buffer);
		if (ret != VK_SUCCESS) return -1;
		return 0;
	}

	int Command::queue_submit_and_wait_fence()
	{
		VkQueue queue = dev->acquire_queue(queue_family_index);
		if (queue == 0) return -1;

		{
			VkSubmitInfo submitInfo;
			submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
			submitInfo.pNext = 0;
			submitInfo.waitSemaphoreCount = 0;
			submitInfo.pWaitSemaphores = 0;
			submitInfo.pWaitDstStageMask = 0;
			submitInfo.commandBufferCount = 1;
			submitInfo.pCommandBuffers = &command_buffer;
			submitInfo.signalSemaphoreCount = 0;
			submitInfo.pSignalSemaphores = 0;

			VkResult ret = vkQueueSubmit(queue, 1, &submitInfo, fence);
			if (ret != VK_SUCCESS) return -1;
			
		}

		{
			VkResult ret = vkWaitForFences(dev->vkdevice(), 1, &fence, VK_TRUE, UINT64_MAX);
			if (ret != VK_SUCCESS) return -1;
		}

		dev->reclaim_queue(queue_family_index, queue);
		return 0;
	}
}

namespace backend {

	VkCompute::VkCompute(const Device* _dev) : Command(_dev, _dev->info.compute_queue_family_index) {
		if (dev->info.support_VK_KHR_push_descriptor)		
			begin_command_buffer();
		
	}

	VkCompute::~VkCompute()
	{
		if (!dev->info.support_VK_KHR_push_descriptor) {
			for (size_t i = 0; i < descriptorsets.size(); ++i) {
				vkFreeDescriptorSets(dev->vkdevice(), descriptor_pools[i], 1, &descriptorsets[i]);
				vkDestroyDescriptorPool(dev->vkdevice(), descriptor_pools[i], 0);
			}
		}
	}

	void VkCompute::record_upload(const DeviceTensor& m) {
		/*if (m.allocator->mappable)
			return;
		record_prepare_transfer_barrier(m);
		if (dev->info.support_VK_KHR_push_descriptor)
			return copy_buffer(m.staging_buffer(), 0, m.buffer(), m.buffer_offset(), m.total() * m.elemsize);

		record_type r;
		r.type = 0;
		r.copy.src = m.staging_buffer();
		r.copy.src_offset = 0;
		r.copy.dst = m.buffer();
		r.copy.dst_offset = m.buffer_offset();
		r.copy.size = m.total() * m.elemsize;
		delayed_records.push_back(r);*/
	}

	void VkCompute::record_download(const DeviceTensor& m) {
		/*if (m.allocator->mappable)
			return;
		record_prepare_transfer_barrier(m);
		if (dev->info.support_VK_KHR_push_descriptor)
			return copy_buffer(m.buffer(), m.buffer_offset(), m.staging_buffer(), 0, m.total() * m.elemsize);

		record_type r;
		r.type = 0;
		r.copy.src = m.buffer();
		r.copy.src_offset = m.buffer_offset();
		r.copy.dst = m.staging_buffer();
		r.copy.dst_offset = 0;
		r.copy.size = m.total() * m.elemsize;
		delayed_records.push_back(r);*/
	}

	void VkCompute::record_clone(const DeviceTensor& src, const DeviceTensor& dst){
		/*record_prepare_transfer_barrier(src);
		record_prepare_transfer_barrier(dst);
		if (dev->info.support_VK_KHR_push_descriptor)
			return copy_buffer(src.buffer(), src.buffer_offset(), dst.buffer(), dst.buffer_offset(), src.total() * src.elemsize);

		record_type r;
		r.type = 0;
		r.copy.src = src.buffer();
		r.copy.src_offset = src.buffer_offset();
		r.copy.dst = dst.buffer();
		r.copy.dst_offset = dst.buffer_offset();
		r.copy.size = src.total() * src.elemsize;
		delayed_records.push_back(r);*/
	}

	void VkCompute::record_copy_region(const DeviceTensor& src, const DeviceTensor& dst, const VkBufferCopy& region) {
		/*std::vector<VkBufferCopy> regions(1);
		regions[0] = region;
		record_copy_regions(src, dst, regions);*/
	}
	
	void VkCompute::record_copy_regions(const DeviceTensor& src, const DeviceTensor& dst, const std::vector<VkBufferCopy>& regions) {
		/*record_prepare_transfer_barrier(src);
		record_prepare_transfer_barrier(dst);
		if (dev->info.support_VK_KHR_push_descriptor)
			return copy_buffer_regions(src.buffer(), dst.buffer(), regions);

		record_type r;
		r.type = 1;
		r.copy_regions.src = src.buffer();
		r.copy_regions.dst = dst.buffer();
		r.regions = regions;
		delayed_records.push_back(r);*/
	}


	void VkCompute::record_pipeline(const Pipeline* pipeline, const std::vector<DeviceTensor>& bindings, const std::vector<vk_constant_type>& constants, const DeviceTensor& m)
	{
		const int binding_count = bindings.size();
		for (int i = 0; i < binding_count; ++i) {
			if (bindings[i].data->state == 4)
				continue;
			record_prepare_compute_barrier(bindings[i]);
		}

		record_bind_pipeline(pipeline->pipeline);
		record_update_bindings(pipeline->pipeline_layout, pipeline->descriptorset_layout, pipeline->descriptor_update_template, bindings);
		record_push_constants(pipeline->pipeline_layout, constants);

		uint32_t group_count_xyz[3];
		group_count_xyz[0] = (m.dim[2] + pipeline->local_size_x - 1) / pipeline->local_size_x;
		group_count_xyz[1] = (m.dim[1] + pipeline->local_size_y - 1) / pipeline->local_size_y;
		group_count_xyz[2] = (m.dim[0] + pipeline->local_size_z - 1) / pipeline->local_size_z;

		record_dispatch(group_count_xyz);
	}

	void VkCompute::record_bind_pipeline(VkPipeline pipeline){
		if (dev->info.support_VK_KHR_push_descriptor)
			return bind_pipeline(pipeline);

		record_type r;
		r.type = 2;
		r.bind_pipeline.pipeline = pipeline;
		delayed_records.push_back(r);
	}

	void VkCompute::record_update_bindings(VkPipelineLayout pipeline_layout, VkDescriptorSetLayout descriptorset_layout, VkDescriptorUpdateTemplateKHR descriptor_update_template, const std::vector<DeviceTensor>& bindings) {
		const int binding_count = bindings.size();

		if (binding_count == 0)
			return;

		std::vector<VkDescriptorBufferInfo> descriptorBufferInfos(binding_count);
		for (int i = 0; i < binding_count; ++i)
		{
			/*descriptorBufferInfos[i].buffer = bindings[i].buffer();
			descriptorBufferInfos[i].offset = bindings[i].buffer_offset();
			descriptorBufferInfos[i].range = bindings[i].total() * bindings[i].elemsize;*/
		}

		if (dev->info.support_VK_KHR_push_descriptor)
			return update_bindings(pipeline_layout, descriptor_update_template, descriptorBufferInfos);

		// create new descriptor_pool and descriptorset
		VkDescriptorPool descriptor_pool;
		{
			VkDescriptorPoolSize poolSize;
			poolSize.type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
			poolSize.descriptorCount = binding_count;

			VkDescriptorPoolCreateInfo descriptorPoolCreateInfo;
			descriptorPoolCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
			descriptorPoolCreateInfo.pNext = 0;
			descriptorPoolCreateInfo.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
			descriptorPoolCreateInfo.maxSets = 1;
			descriptorPoolCreateInfo.poolSizeCount = 1;
			descriptorPoolCreateInfo.pPoolSizes = &poolSize;

			VkResult ret = vkCreateDescriptorPool(dev->vkdevice(), &descriptorPoolCreateInfo, 0, &descriptor_pool);
			if (ret != VK_SUCCESS)
			{
				fprintf(stderr, "vkCreateDescriptorPool failed %d\n", ret);
				return;
			}
		}
		descriptor_pools.push_back(descriptor_pool);

		VkDescriptorSet descriptorset;
		{
			VkDescriptorSetAllocateInfo descriptorSetAllocateInfo;
			descriptorSetAllocateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
			descriptorSetAllocateInfo.pNext = 0;
			descriptorSetAllocateInfo.descriptorPool = descriptor_pool;
			descriptorSetAllocateInfo.descriptorSetCount = 1;
			descriptorSetAllocateInfo.pSetLayouts = &descriptorset_layout;

			VkResult ret = vkAllocateDescriptorSets(dev->vkdevice(), &descriptorSetAllocateInfo, &descriptorset);
			if (ret != VK_SUCCESS)
			{
				fprintf(stderr, "vkAllocateDescriptorSets failed %d\n", ret);
				return;
			}
		}
		descriptorsets.push_back(descriptorset);

		//     fprintf(stderr, "update descriptorset %p\n", descriptorset);

		if (dev->info.support_VK_KHR_descriptor_update_template)
		{
			dev->vkUpdateDescriptorSetWithTemplateKHR(dev->vkdevice(), descriptorset, descriptor_update_template, descriptorBufferInfos.data());
		}
		else
		{
			std::vector<VkWriteDescriptorSet> writeDescriptorSets(binding_count);
			for (int i = 0; i < binding_count; ++i)
			{
				writeDescriptorSets[i].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
				writeDescriptorSets[i].pNext = 0;
				writeDescriptorSets[i].dstSet = descriptorset;
				writeDescriptorSets[i].dstBinding = i;
				writeDescriptorSets[i].dstArrayElement = 0;
				writeDescriptorSets[i].descriptorCount = 1;
				writeDescriptorSets[i].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
				writeDescriptorSets[i].pImageInfo = 0;
				writeDescriptorSets[i].pBufferInfo = &descriptorBufferInfos[i];
				writeDescriptorSets[i].pTexelBufferView = 0;
			}

			vkUpdateDescriptorSets(dev->vkdevice(), binding_count, writeDescriptorSets.data(), 0, 0);
		}

		record_type r;
		r.type = 3;
		r.bind_descriptorset.pipeline_layout = pipeline_layout;
		r.bind_descriptorset.descriptorset = descriptorset;
		delayed_records.push_back(r);
	}

	void VkCompute::record_push_constants(VkPipelineLayout pipeline_layout, const std::vector<vk_constant_type>& constants) {
		if (dev->info.support_VK_KHR_push_descriptor)
			return push_constants(pipeline_layout, constants);

		record_type r;
		r.type = 4;
		r.push_constants.pipeline_layout = pipeline_layout;
		r.constants = constants;
		delayed_records.push_back(r);
	}

	void VkCompute::record_dispatch(const uint32_t* group_count_xyz) {
		if (dev->info.support_VK_KHR_push_descriptor)
			return dispatch(group_count_xyz);

		record_type r;
		r.type = 5;
		r.dispatch.group_count_xyz[0] = group_count_xyz[0];
		r.dispatch.group_count_xyz[1] = group_count_xyz[1];
		r.dispatch.group_count_xyz[2] = group_count_xyz[2];
		delayed_records.push_back(r);
	}

	void VkCompute::record_transfer_compute_barrier(const DeviceTensor& m) {
		/*m.data->state = 3;
		if (dev->info.support_VK_KHR_push_descriptor)
			return transfer_compute_barrier(m.buffer(), m.buffer_offset(), m.total() * m.elemsize);

		record_type r;
		r.type = 6;
		r.transfer_compute_barrier.buffer = m.buffer();
		r.transfer_compute_barrier.offset = m.buffer_offset();
		r.transfer_compute_barrier.size = m.total() * m.elemsize;
		delayed_records.push_back(r);*/
	}

	void VkCompute::record_compute_transfer_barrier(const DeviceTensor& m) {
		/*m.data->state = 2;
		if (dev->info.support_VK_KHR_push_descriptor)
			return compute_transfer_barrier(m.buffer(), m.buffer_offset(), m.total() * m.elemsize);

		record_type r;
		r.type = 7;
		r.compute_transfer_barrier.buffer = m.buffer();
		r.compute_transfer_barrier.offset = m.buffer_offset();
		r.compute_transfer_barrier.size = m.total() * m.elemsize;
		delayed_records.push_back(r);*/
	}


	void VkCompute::record_compute_compute_barrier(const DeviceTensor& m) {
		/*m.data->state = 3;
		if (dev->info.support_VK_KHR_push_descriptor)
			return compute_compute_barrier(m.buffer(), m.buffer_offset(), m.total() * m.elemsize);

		record_type r;
		r.type = 8;
		r.compute_compute_barrier.buffer = m.buffer();
		r.compute_compute_barrier.offset = m.buffer_offset();
		r.compute_compute_barrier.size = m.total() * m.elemsize;
		delayed_records.push_back(r);*/
	}

	void VkCompute::record_transfer_transfer_barrier(const DeviceTensor& m) {
		/*m.data->state = 2;
		if (dev->info.support_VK_KHR_push_descriptor)
			return transfer_transfer_barrier(m.buffer(), m.buffer_offset(), m.total() * m.elemsize);

		record_type r;
		r.type = 9;
		r.transfer_transfer_barrier.buffer = m.buffer();
		r.transfer_transfer_barrier.offset = m.buffer_offset();
		r.transfer_transfer_barrier.size = m.total() * m.elemsize;
		delayed_records.push_back(r);*/
	}

	void VkCompute::record_prepare_transfer_barrier(const DeviceTensor& m) {
		if (m.data->state == 2)
			return record_transfer_transfer_barrier(m);

		if (m.data->state == 3)
			return record_compute_transfer_barrier(m);

		m.data->state = 2;
	}

	void VkCompute::record_prepare_compute_barrier(const DeviceTensor& m) {
		if (m.data->state == 2)
			return record_transfer_compute_barrier(m);

		if (m.data->state == 3)
			return record_compute_compute_barrier(m);

		m.data->state = 3;
	}

	int VkCompute::submit_and_wait()
	{
		if (dev->info.support_VK_KHR_push_descriptor) {
			end_command_buffer();
			return queue_submit_and_wait_fence();
		}

		begin_command_buffer();

		for (size_t i = 0; i < delayed_records.size(); ++i) {
			const record_type& r = delayed_records[i];
			switch (r.type) {
			case 0:
				copy_buffer(r.copy.src, r.copy.src_offset, r.copy.dst, r.copy.dst_offset, r.copy.size);
				break;
			case 1:
				copy_buffer_regions(r.copy_regions.src, r.copy_regions.dst, r.regions);
				break;
			case 2:
				bind_pipeline(r.bind_pipeline.pipeline);
				break;
			case 3:
				bind_descriptorset(r.bind_descriptorset.pipeline_layout, r.bind_descriptorset.descriptorset);
				break;
			case 4:
				push_constants(r.push_constants.pipeline_layout, r.constants);
				break;
			case 5:
				dispatch(r.dispatch.group_count_xyz);
				break;
			case 6:
				transfer_compute_barrier(r.transfer_compute_barrier.buffer, r.transfer_compute_barrier.offset, r.transfer_compute_barrier.size);
				break;
			case 7:
				compute_transfer_barrier(r.compute_transfer_barrier.buffer, r.compute_transfer_barrier.offset, r.compute_transfer_barrier.size);
				break;
			case 8:
				compute_compute_barrier(r.compute_compute_barrier.buffer, r.compute_compute_barrier.offset, r.compute_compute_barrier.size);
				break;
			case 9:
				transfer_transfer_barrier(r.compute_compute_barrier.buffer, r.compute_compute_barrier.offset, r.compute_compute_barrier.size);
				break;
			}
		}

		end_command_buffer();
		delayed_records.clear();
		return queue_submit_and_wait_fence();
	}

	int VkCompute::reset() {
		VkResult ret = vkResetCommandBuffer(command_buffer, 0);
		if (ret != VK_SUCCESS) return -1;

		ret = vkResetFences(dev->vkdevice(), 1, &fence);
		if (ret != VK_SUCCESS) return -1;

		if (dev->info.support_VK_KHR_push_descriptor) {
			begin_command_buffer();
		}

		return 0;
	}
	
	void VkCompute::copy_buffer(VkBuffer src, size_t src_offset, VkBuffer dst, size_t dst_offset, size_t size) {
		VkBufferCopy region;
		region.srcOffset = src_offset;
		region.dstOffset = dst_offset;
		region.size = size;
		vkCmdCopyBuffer(command_buffer, src, dst, 1, &region);
	}
	
	void VkCompute::copy_buffer_regions(VkBuffer src, VkBuffer dst, const std::vector<VkBufferCopy>& regions) {
		vkCmdCopyBuffer(command_buffer, src, dst, regions.size(), regions.data());
	}

	void VkCompute::bind_pipeline(VkPipeline pipeline) {
		vkCmdBindPipeline(command_buffer, VK_PIPELINE_BIND_POINT_COMPUTE, pipeline);
	}

	void VkCompute::bind_descriptorset(VkPipelineLayout pipeline_layout, VkDescriptorSet descriptorset) {
		vkCmdBindDescriptorSets(command_buffer, VK_PIPELINE_BIND_POINT_COMPUTE, pipeline_layout, 0, 1, &descriptorset, 0, 0);
	}

	void VkCompute::update_bindings(VkPipelineLayout pipeline_layout, VkDescriptorUpdateTemplateKHR descriptor_update_template, const std::vector<VkDescriptorBufferInfo>& descriptorBufferInfos) {
		dev->vkCmdPushDescriptorSetWithTemplateKHR(command_buffer, descriptor_update_template, pipeline_layout, 0, descriptorBufferInfos.data());
	}

	void VkCompute::push_constants(VkPipelineLayout pipeline_layout, const std::vector<vk_constant_type>& constants) {
		vkCmdPushConstants(command_buffer, pipeline_layout, VK_SHADER_STAGE_COMPUTE_BIT, 0, constants.size() * sizeof(vk_constant_type), constants.data());
	}

	void VkCompute::dispatch(const uint32_t* group_count_xyz) {
		vkCmdDispatch(command_buffer, group_count_xyz[0], group_count_xyz[1], group_count_xyz[2]);
	}

	void VkCompute::transfer_compute_barrier(VkBuffer buffer, size_t offset, size_t size) {
		VkBufferMemoryBarrier bufferBarrier;
		bufferBarrier.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;
		bufferBarrier.pNext = 0;
		bufferBarrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
		bufferBarrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT | VK_ACCESS_SHADER_WRITE_BIT;
		bufferBarrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		bufferBarrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		bufferBarrier.buffer = buffer;
		bufferBarrier.offset = offset;
		bufferBarrier.size = size;
		VkPipelineStageFlags srcStageMask = VK_PIPELINE_STAGE_TRANSFER_BIT;
		VkPipelineStageFlags dstStageMask = VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT;
		vkCmdPipelineBarrier(command_buffer, srcStageMask, dstStageMask, 0, 0, 0, 1, &bufferBarrier, 0, 0);
	}

	void VkCompute::compute_transfer_barrier(VkBuffer buffer, size_t offset, size_t size) {
		VkBufferMemoryBarrier bufferBarrier;
		bufferBarrier.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;
		bufferBarrier.pNext = 0;
		bufferBarrier.srcAccessMask = VK_ACCESS_SHADER_READ_BIT | VK_ACCESS_SHADER_WRITE_BIT;
		bufferBarrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
		bufferBarrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		bufferBarrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		bufferBarrier.buffer = buffer;
		bufferBarrier.offset = offset;
		bufferBarrier.size = size;
		VkPipelineStageFlags srcStageMask = VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT;
		VkPipelineStageFlags dstStageMask = VK_PIPELINE_STAGE_TRANSFER_BIT;
		vkCmdPipelineBarrier(command_buffer, srcStageMask, dstStageMask, 0, 0, 0, 1, &bufferBarrier, 0, 0);
	}

	void VkCompute::compute_compute_barrier(VkBuffer buffer, size_t offset, size_t size) {
		VkBufferMemoryBarrier bufferBarrier;
		bufferBarrier.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;
		bufferBarrier.pNext = 0;
		bufferBarrier.srcAccessMask = VK_ACCESS_SHADER_WRITE_BIT;
		bufferBarrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
		bufferBarrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		bufferBarrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		bufferBarrier.buffer = buffer;
		bufferBarrier.offset = offset;
		bufferBarrier.size = size;
		VkPipelineStageFlags srcStageMask = VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT;
		VkPipelineStageFlags dstStageMask = VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT;
		vkCmdPipelineBarrier(command_buffer, srcStageMask, dstStageMask, 0, 0, 0, 1, &bufferBarrier, 0, 0);
	}

	void VkCompute::transfer_transfer_barrier(VkBuffer buffer, size_t offset, size_t size) {
		VkBufferMemoryBarrier bufferBarrier;
		bufferBarrier.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;
		bufferBarrier.pNext = 0;
		bufferBarrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
		bufferBarrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
		bufferBarrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		bufferBarrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		bufferBarrier.buffer = buffer;
		bufferBarrier.offset = offset;
		bufferBarrier.size = size;
		VkPipelineStageFlags srcStageMask = VK_PIPELINE_STAGE_TRANSFER_BIT;
		VkPipelineStageFlags dstStageMask = VK_PIPELINE_STAGE_TRANSFER_BIT;
		vkCmdPipelineBarrier(command_buffer, srcStageMask, dstStageMask, 0, 0, 0, 1, &bufferBarrier, 0, 0);
	}

}

namespace backend {
	VkTransfer::VkTransfer(const Device* _vkdev) : Command(_vkdev, _vkdev->info.transfer_queue_family_index) {
		buffer_offset_alignment = dev->info.buffer_offset_alignment;
		staging_data = 0;
	}

	VkTransfer::~VkTransfer() {}

	void VkTransfer::record_upload(const Tensor& src, DeviceTensor& dst)
	{
		/*Tensor src_flattened = src.reshape(src.w * src.h * src.c);

		dst.create_like(src_flattened, weight_vkallocator, staging_vkallocator);

		// set weight blob as readonly
		dst.data->state = 4;

		if (dst.allocator->mappable)
		{
			dst.upload(src_flattened);
			return;
		}

		record_type r;
		r.size = src_flattened.total() * src_flattened.elemsize;
		r.t = src_flattened;
		r.d_t = dst;
		delayed_records.push_back(r);*/
	}


	int VkTransfer::submit_and_wait() {
		if (delayed_records.empty())
			return 0;

		int transfer_count = delayed_records.size();

		size_t staging_buffer_size = 0;
		for (int i = 0; i < transfer_count; ++i) {
			const record_type& r = delayed_records[i];
			staging_buffer_size += alignSize(r.size, buffer_offset_alignment);
		}

		staging_data = staging_allocator->fastMalloc(staging_buffer_size);

		size_t mapped_ptr_offset = 0;
		for (int i = 0; i < transfer_count; ++i) {
			const record_type& r = delayed_records[i];
			memcpy((unsigned char*)staging_data->mapped_ptr + mapped_ptr_offset, r.t.data, r.size);
			mapped_ptr_offset += alignSize(r.size, buffer_offset_alignment);
		}

		begin_command_buffer();

		size_t staging_buffer_offset = 0;
		for (int i = 0; i < transfer_count; ++i) {
			/*const record_type& r = delayed_records[i];
			copy_buffer(staging_data->buffer, staging_buffer_offset, r.d_t.buffer(), r.d_t.buffer_offset(), r.size);
			staging_buffer_offset += (r.size, buffer_offset_alignment);*/
		}

		end_command_buffer();
		int ret = queue_submit_and_wait_fence();

		staging_allocator->fastFree(staging_data);
		staging_data = 0;
		delayed_records.clear();
		return ret;
	}


	void VkTransfer::copy_buffer(VkBuffer src, size_t src_offset, VkBuffer dst, size_t dst_offset, size_t size) {
		VkBufferCopy region;
		region.srcOffset = src_offset;
		region.dstOffset = dst_offset;
		region.size = size;

		vkCmdCopyBuffer(command_buffer, src, dst, 1, &region);
	}

	void VkTransfer::copy_buffer_regions(VkBuffer src, VkBuffer dst, const std::vector<VkBufferCopy>& regions) {
		vkCmdCopyBuffer(command_buffer, src, dst, regions.size(), regions.data());
	}


}