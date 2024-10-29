/* #include "VulkanCpp/Vulkan.h" */
#include <stdio.h>
#include <vector>
#include <vulkan/vulkan_core.h>
#include <GLFW/glfw3.h>

static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
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

void make_debug_messenger(){
    VkDebugUtilsMessengerCreateInfoEXT debugMsgCreateInfo = {
        .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
        .pNext = nullptr,
        .messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
        .messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
        .pfnUserCallback = &DebugCallback,
        .pUserData = nullptr
    };
}
/* VK_LAYER_KHRONOS_validation 	Vulkan API validation and error checking. */
/* VK_LAYER_LUNARG_api_dump 	Print API calls and their parameters and values. */
/* VK_LAYER_KHRONOS_profiles 	Helps test across a wide range of hardware capabilities without physical access to every device. */
/* VK_LAYER_KHRONOS_synchronization2 	Implements the VK_KHR_synchronization2VK_KHR_synchronization2 extension, for use on systems without a driver that implements it. */
/* VK_LAYER_KHRONOS_shader_object */

#if defined(_WIN32)
static std::vector<const char *> extensions = {
    VK_KHR_SURFACE_EXTENSION_NAME,
    "VK_KHR_win32_surface"
};
#elif defined(__APPLE__)
static std::vector<const char*> extensions = {
    VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME,
    VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME,
};
#elif defined(__linux__)
static std::vector<const char*> extensions = {
    "VK_KHR_xcb_surface",
};
#else // this is if we aren't on Win32, Mac, or even linux for some odd reason.
#endif


std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation",
    "VK_LAYER_KHRONOS_validation",
    "VK_LAYER_LUNARG_api_dump",
    "VK_LAYER_KHRONOS_profiles",
    "VK_LAYER_KHRONOS_synchronization2",
    "VK_LAYER_KHRONOS_shader_object"
};

int main(){

    static std::vector<const char *> extensions{
        VK_KHR_SURFACE_EXTENSION_NAME, // Used to bind our window to vulkan
#if defined(_WIN32)
            "VK_KHR_win32_surface",
#elif defined(__APPLE__)
            /* "VK_MVK_macos_surface", */
        VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME,
        VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME,
#elif defined(__linux__)
    "VK_KHR_xcb_surface",
#endif
        // enables callback to our application when errors happen in vulkan
        VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
    };

    if(!glfwInit()){
        printf("GLFW not init-ed!\n");
        return -1;
    }

    if(!glfwVulkanSupported()){
        printf("Vulkan not supported\n");
        return -2;
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);


    GLFWwindow* window = glfwCreateWindow(900, 600, "Test", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    
    VkApplicationInfo appInfo ={
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
            .pNext = nullptr,
            .pApplicationName = "Test",
            .pEngineName = "Test", 
            .engineVersion = VK_MAKE_API_VERSION(1, 1, 0, 0),
            .apiVersion = VK_API_VERSION_1_0
    };

    VkInstanceCreateInfo createInfo={
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
            .pNext = nullptr,
            .flags = VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR, // reserve for future use
            .pApplicationInfo = &appInfo,
            .enabledLayerCount = (uint32_t)validationLayers.size(), //! list of extensions. Up to app developer to make sure if these are supported
            .ppEnabledLayerNames = validationLayers.data(),
            .enabledExtensionCount = (uint32_t)extensions.size(),
            .ppEnabledExtensionNames = extensions.data()
    };

    VkInstance instance;
    auto res = vkCreateInstance(&createInfo, nullptr, &instance);
    
    if(res != VK_SUCCESS){
        printf("Not successfull!\n");
        return 0;
    }

    // make_debug_messenger();
    //! @note Debug callback requires validatoin layers and debug utils to be enabled in extensions as it is not part of the vulkan core.
    VkDebugUtilsMessengerCreateInfoEXT debugMsgCreateInfo = {
        .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
        .pNext = nullptr,
        .messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
        .messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
        .pfnUserCallback = &DebugCallback,
        .pUserData = nullptr
    };
    
    VkSurfaceKHR surface;
    //! @note Creating our surface
    //! @note TODO -- Probably want to abstract this and deal with window surfaces using Vulkan and the targeted platforms-specific windowing system
    VkResult surface_res = glfwCreateWindowSurface(instance, window, nullptr, &surface);

    if(surface_res != VK_SUCCESS){
        /* ConsoleLogError("glfwCreateWindowSurface errored message is ===>\t\t{}", VkResultToString(surface_res)); */
    }

    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();
    }

}
