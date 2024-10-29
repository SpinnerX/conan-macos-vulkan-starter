#include <VulkanCpp/Application.h>
#include <VulkanCpp/Vulkan.h>
#include <VulkanCpp/VulkanPhysicalDevice.h>
#include <cstdint>
#include <stdexcept>
#include <vulkan/vulkan_core.h>
#include <sstream>

namespace engine3d::vk{
    //////////////////////////////////////////
    /////////// PHYSICAL DEVICE /////////////
    //////////////////////////////////////////

    //! @note Extracts the available physical devices on our current platform.
    static std::vector<VkPhysicalDevice> get_available_devices(){
        uint32_t devices_count = 0;

        VkResult res = vkEnumeratePhysicalDevices(Vulkan::GetVkInstance(), &devices_count, nullptr);
        printf("devices_count (afterwards) === %i\n", devices_count);
        if(res != VK_SUCCESS){
            printf("get_available_devices error number ===>>> %i\n", res);
        }
        std::vector<VkPhysicalDevice> devices(devices_count);
        printf("vector size (afterwards) === %zu\n", devices.size());        
        res = vkEnumeratePhysicalDevices(Vulkan::GetVkInstance(), &devices_count, devices.data());
        return devices;
    }

    static void print_physical_device_property(VkPhysicalDeviceProperties properties){
        printf("==================================================\n");
        std::stringstream ss;
        ss << "Device ID: " << properties.deviceID << '\n';
        ss << "Device Name: " << properties.deviceName << '\n';
        ss << "Driver Version: " << properties.driverVersion << '\n';
        ss << "API Version: " << properties.apiVersion << '\n';
    }
    
    VulkanPhysicalDevice::VulkanPhysicalDevice() : m_CurrentDeviceIdx(0){
        printf("==================================================\n");
        printf("==================================================\n");
        printf("==================================================\n");
        printf("VULKAN PHYSICAL DEVICE CONSTRUCTED\n");
        std::vector<VkPhysicalDevice> devices = get_available_devices();
        m_PhysicalDevices.resize(devices.size());
        printf("Original Devices Vector Size === %zu\n", devices.size());
        printf("After resize ==== %zu\n", m_PhysicalDevices.size());


        for(uint32_t i = 0; i < devices.size(); i++){
            VkPhysicalDevice dev = devices[i];
            m_PhysicalDevices[i].device = dev;

            if(m_PhysicalDevices[i].device == nullptr){
                printf("==================>>>> Physical Device Nullptr!\n");
            }
            vkGetPhysicalDeviceProperties(dev, &m_PhysicalDevices[i].deviceProperties);
            VkPhysicalDeviceProperties property = m_PhysicalDevices[i].deviceProperties;
            print_physical_device_property(property);





            // Getting the amount of queue families
            uint32_t queueFamilyAmount;
            vkGetPhysicalDeviceQueueFamilyProperties(dev, &queueFamilyAmount, nullptr);
            printf("Queue Family Amount ===========>>>>> %i\n", queueFamilyAmount);

            m_PhysicalDevices[i].queueFamProperties.resize(queueFamilyAmount);
            m_PhysicalDevices[i].queueSupportedPresented.resize(queueFamilyAmount);

            for(uint32_t q = 0; q < queueFamilyAmount; q++){
                const VkQueueFamilyProperties& queueProper = m_PhysicalDevices[i].queueFamProperties[q];
                VkQueueFlags flags = queueProper.queueFlags;

                printf("VkQueueFlags flags ================>>>>> %i\n", flags);

                auto res = vkGetPhysicalDeviceSurfaceSupportKHR(dev, q, Application::Get().GetVkSurface(), &m_PhysicalDevices[i].queueSupportedPresented[q]);

                if(res != VK_SUCCESS){
                    printf("vkGetPhysicalDeviceSurfaceSupportKHR error number ===>>>> %i\n", res);
                }
            }

            //! @note checking and validating if surface formats are available.
            uint32_t format_count = 0;
            auto res = vkGetPhysicalDeviceSurfaceFormatsKHR(dev, Application::Get().GetVkSurface(), &format_count, nullptr); // getting amount of surface formats available

            if(res != VK_SUCCESS){
                printf("vkGetPhysicalDeviceSurfaceFormatsKHR error number ===>>>> %i\n", res);
            }

            m_PhysicalDevices[i].surfaceFormats.resize(format_count);

            res = vkGetPhysicalDeviceSurfaceFormatsKHR(dev, Application::Get().GetVkSurface(), &format_count, m_PhysicalDevices[i].surfaceFormats.data());
            
            if(res != VK_SUCCESS){
                printf("vkGetPhysicalDeviceSurfaceFormatsKHR error number ===>>>> %i\n", res);
            }


            //! @note checking which presentation modes are present on our current platform.
            uint32_t present_mode_count = 0;
            res = vkGetPhysicalDeviceSurfacePresentModesKHR(dev, Application::Get().GetVkSurface(), &present_mode_count, nullptr);
            
            if(res != VK_SUCCESS){
                printf("vkGetPhysicalDeviceSurfacePresentModesKHR error number ===>>>> %i\n", res);
            }
            
            res = vkGetPhysicalDeviceSurfacePresentModesKHR(dev, Application::Get().GetVkSurface(), &present_mode_count, m_PhysicalDevices[i].presentModes.data());
            
            if(res != VK_SUCCESS){
                printf("vkGetPhysicalDeviceSurfacePresentModesKHR error number ===>>>> %i\n", res);
            }

            vkGetPhysicalDeviceFeatures(dev, &m_PhysicalDevices[i].deviceFeatures); 
        }
    }

    VulkanPhysicalDevice::~VulkanPhysicalDevice(){}

    uint32_t VulkanPhysicalDevice::SelectDevice(VkQueueFlags p_ReqQueueFlag_t, bool p_IsSupportPresent){
        printf("SelecteDevice() ==== %zu\n", m_PhysicalDevices.size());

        for(uint32_t i = 0; i < m_PhysicalDevices.size(); i++){
            printf("Index i == %zu\n", m_PhysicalDevices[i].queueFamProperties.size());
            for(uint32_t j = 0; j < m_PhysicalDevices[i].queueFamProperties.size(); j++){
                const VkQueueFamilyProperties qFamProps = m_PhysicalDevices[i].queueFamProperties[j];

                if((qFamProps.queueFlags & p_ReqQueueFlag_t) and ((bool)m_PhysicalDevices[i].queueSupportedPresented[j] == p_IsSupportPresent)){
                   m_CurrentDeviceIdx = i;
                   int queueFamily = j;
                   return queueFamily;
                }
            }
        }

        return 0;
    }

    PhysicalDeviceAttributes& VulkanPhysicalDevice::SelectedActiveDevice(){
        return m_PhysicalDevices[m_CurrentDeviceIdx];
    }

    VkPhysicalDevice VulkanPhysicalDevice::SelectedVkPhysicalDevice(){
        if(m_CurrentDeviceIdx <= 0){
            printf("m_CurrentDeviceIdx === %i\n", m_CurrentDeviceIdx);
            throw std::runtime_error("Out-of-bounds error and will not select a vulkan physical device");
        }
        return m_PhysicalDevices[m_CurrentDeviceIdx].device;
    }

    VkBool32 VulkanPhysicalDevice::IsGeometryShaderSupported(){
        return SelectedActiveDevice().deviceFeatures.geometryShader;
    }

    VkBool32 VulkanPhysicalDevice::IsTesselationSupported(){
        return SelectedActiveDevice().deviceFeatures.tessellationShader;
    }
    
    uint32_t VulkanPhysicalDevice::GetQueueFamilyCount(){
        return m_QueueFamCount;
    }

}    
