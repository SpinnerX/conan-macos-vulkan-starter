#pragma once
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>
#include <vector>

namespace engine3d{
    namespace vk{

        struct PhysicalDeviceAttributes{
            VkPhysicalDevice device;
            VkPhysicalDeviceProperties deviceProperties;
            std::vector<VkQueueFamilyProperties> queueFamProperties;
            std::vector<uint32_t> queueSupportedPresented;
            std::vector<VkSurfaceFormatKHR> surfaceFormats;
            VkSurfaceCapabilitiesKHR surfaceCapabilities;
            VkPhysicalDeviceMemoryProperties memoryProperties;
            std::vector<VkPresentModeKHR> presentModes;
            VkPhysicalDeviceFeatures deviceFeatures;
        };

        class VulkanPhysicalDevice{
            using PhysicalDevice = PhysicalDeviceAttributes;
        public:
            VulkanPhysicalDevice();
            ~VulkanPhysicalDevice();
            //! @note Initializing physical devices.
            /* static void InitializePhysicalDevice(); */
            /* static void CleanupPhysicalDevice(); */
            
            uint32_t SelectDevice(VkQueueFlags p_ReqFlags_t, bool p_IsSupportPresent);

            static VkSurfaceCapabilitiesKHR GetSurfaceCapabilities();
            static std::vector<VkPresentModeKHR> GetPresentationModes();
            static std::vector<VkSurfaceFormatKHR> GetSurfaceFormats();
            VkPhysicalDevice SelectedVkPhysicalDevice();
            PhysicalDevice& SelectedActiveDevice();
            VkBool32 IsGeometryShaderSupported();
            VkBool32 IsTesselationSupported();

            VkSurfaceCapabilitiesKHR SurfaceCapabilities();
            std::vector<VkSurfaceFormatKHR> SurfaceFormats();
            std::vector<VkPresentModeKHR> PresentationModes();

            uint32_t GetQueueFamilyCount();

        private:
            VkPhysicalDevice SelectedDeviceImpl();
        private:
            std::vector<PhysicalDevice> m_PhysicalDevices;
            uint32_t m_CurrentDeviceIdx; // index of our currently selected device.
            uint32_t m_QueueFamCount=0;
        };
    };
};
