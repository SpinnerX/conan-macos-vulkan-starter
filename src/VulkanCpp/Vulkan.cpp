#include <VulkanCpp/Vulkan.h>
#include <VulkanCpp/VulkanDebugHelper.h>
#include <stdexcept>
#include <vector>
#include <vulkan/vulkan_core.h>
#include <cstdint>

namespace engine3d::vk{
    
#if defined(_WIN32)
    static std::vector<const char *> extensions = {
        VK_KHR_SURFACE_EXTENSION_NAME,
        VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
        "VK_KHR_win32_surface"
    };
#elif defined(__APPLE__)
    static std::vector<const char*> extensions = {
        VK_KHR_SURFACE_EXTENSION_NAME,
        VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
        "VK_KHR_surface",
        "VK_EXT_metal_surface",

        VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME,
        VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME,
    };
#elif defined(__linux__)
    static std::vector<const char*> extensions = {
        VK_KHR_SURFACE_EXTENSION_NAME,
        VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
        "VK_KHR_xcb_surface",
    };
#else // this is if we aren't on Win32, Mac, or even linux for some odd reason.
#endif

    static std::vector<const char*> validationLayers = {
        "VK_LAYER_KHRONOS_validation",
        "VK_LAYER_LUNARG_api_dump",
        "VK_LAYER_KHRONOS_profiles",
        "VK_LAYER_KHRONOS_synchronization2",
        "VK_LAYER_KHRONOS_shader_object",
    };

    VkInstance g_Instance;

    void Vulkan::InitializeVulkan(){
        //! @note to initialize vulkan we need to first specify our application properties.
        //! @note Initialize vulkan's instance information for instantiation.
        VkApplicationInfo appInfo = {
            .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
            .pApplicationName = "Engine3D",
            .pEngineName = "Engine3D",
            .engineVersion = VK_MAKE_API_VERSION(1, 1, 0, 0),
            .apiVersion = VK_API_VERSION_1_0
        };

        VkInstanceCreateInfo createInfo = {
            .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
            .pNext = nullptr,
            .flags = VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR,
            .pApplicationInfo = &appInfo,
            .enabledLayerCount = static_cast<uint32_t>(validationLayers.size()),
            .ppEnabledLayerNames = validationLayers.data(),
            .enabledExtensionCount = static_cast<uint32_t>(extensions.size()),
            .ppEnabledExtensionNames = extensions.data()
        };

        VkResult res = vkCreateInstance(&createInfo, nullptr, &g_Instance);

        if(res != VK_SUCCESS){
            throw std::runtime_error("vkCreateInstance errored message ===> ");
        }

        //! @note Setting the debug callback
        /* VkDebugUtilsMessengerCreateInfoEXT debugMsgCreateInfo = { */
        /*     .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT, */
        /*     .pNext = nullptr, */
        /*     .messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT, */
        /*     .messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT, */
        /*     .pfnUserCallback = &DebugCallback, */
        /*     .pUserData = nullptr */
        /* }; */
    }

    VkInstance& Vulkan::GetVkInstance(){ return g_Instance; }
};
