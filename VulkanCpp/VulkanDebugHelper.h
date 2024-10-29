#pragma once
#include <vulkan/vulkan_core.h>

namespace engine3d{
    namespace vk{
        
        VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
                VkDebugUtilsMessageSeverityFlagBitsEXT Severity,
                VkDebugUtilsMessageTypeFlagsEXT Type,
                const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                void* pUserData);

        /* void debug_messenger_create( */
    };
};
