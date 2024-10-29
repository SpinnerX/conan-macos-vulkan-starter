#include <VulkanCpp/VulkanLogicalDevice.h>
#include <vulkan/vulkan_core.h>
#include <VulkanCpp/VulkanPhysicalDevice.h>

namespace engine3d::vk{
    static VkQueue g_GraphicsQueue;
    static VkQueue g_ComputeQueue;

    VulkanLogicalDevice::VulkanLogicalDevice(){
        m_PhysicalDevice = VulkanPhysicalDevice();
        m_QueueFamily = m_PhysicalDevice.SelectDevice(VK_QUEUE_GRAPHICS_BIT, true);

        float queuePriorities[] = {1.0f};

        VkDeviceQueueCreateInfo qCreateInfo = {
            .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
            .pNext = nullptr,
            .flags = 0,
            .queueFamilyIndex = m_QueueFamily,
            .queueCount = 1,
            .pQueuePriorities = &queuePriorities[1]
        };

        std::vector<const char *> device_extensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME,
            VK_KHR_SHADER_DRAW_PARAMETERS_EXTENSION_NAME
        };

        VkPhysicalDeviceFeatures physDevFeatures = {0};
        physDevFeatures.geometryShader = VK_TRUE;
        physDevFeatures.tessellationShader = VK_TRUE;

        VkDeviceCreateInfo devCreateInfo = {
            .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
            .pNext = nullptr,
            .flags = 0,
            .queueCreateInfoCount = 1,
            .pQueueCreateInfos = &qCreateInfo,
            .enabledLayerCount = 0,
            .ppEnabledLayerNames = nullptr,
            .enabledExtensionCount = (uint32_t)device_extensions.size(),
            .ppEnabledExtensionNames = device_extensions.data(),
            .pEnabledFeatures = &physDevFeatures
        };

        /* if(!m_PhysicalDevice.IsGeometryShaderSupported()){ */
        /*     printf("Geometry Shader not supported\n"); */
        /* } */

        /* if(!g_PhysicalDevice.IsTesselationSupported()){ */
        /*     printf("Tesellation Shader not supported\n"); */
        /* } */

        auto res = vkCreateDevice(m_PhysicalDevice.SelectedVkPhysicalDevice(), &devCreateInfo, nullptr, &m_Device);

        if(res != VK_SUCCESS){
            printf("vkCreateDevice error number ===>>>> %i\n", res);
        }

        vkGetDeviceQueue(m_Device, m_QueueFamily, 0, &g_GraphicsQueue);
    }

    VulkanLogicalDevice::~VulkanLogicalDevice(){}

    VkDevice VulkanLogicalDevice::VkLogicalDeviceInstance(){
        return m_Device;
    }

    uint32_t& VulkanLogicalDevice::QueueFamily(){
        return m_QueueFamily;
    }
};
