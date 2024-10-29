#include <VulkanCpp/VulkanDebugHelper.h>
#include <stdio.h>

namespace engine3d::vk{
    VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT Severity,
        VkDebugUtilsMessageTypeFlagsEXT Type,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData
        ){
        /* ConsoleLogWarn("Debug callback: {}\n", pCallbackData->pMessage); */
        /* ConsoleLogWarn("\tSeverity {}", GetDebugSeverity(Severity)); */
        /* ConsoleLogWarn("\tType {}", GetDebugType(Type)); */
        /* ConsoleLogWarn("\tObjects"); */

        for(uint32_t i = 0; i < pCallbackData->objectCount; i++){
            /* ConsoleLogWarn("{} ", pCallbackData->pObjects[i].objectHandle); */
            printf("%llu\n", pCallbackData->pObjects[i].objectHandle);
        }
        return false;
    }

};
