#pragma once
#include "VulkanCpp/VulkanPhysicalDevice.h"
#include <vulkan/vulkan.h>
#include <cstdint>

namespace engine3d{
    namespace vk{
        class VulkanLogicalDevice{
        public:
            VulkanLogicalDevice();
            ~VulkanLogicalDevice();

            VkDevice VkLogicalDeviceInstance();
            uint32_t& QueueFamily();

        private:
            uint32_t m_QueueFamily;
            VulkanPhysicalDevice m_PhysicalDevice;
            VkDevice m_Device; // logical device
        };
    };
};
