#include "VulkanCpp/Vulkan.h"
#include "VulkanCpp/helper_functions.h"
#include <VulkanCpp/VulkanWindow.h>
#include <stdexcept>
#include <vulkan/vulkan_core.h>

#if defined(__WIN32)
#define VK_USE_PLATFORM_WIN32_KHR
#endif

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#if defined(__WIN32)
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#endif
#include <vulkan/vulkan.h>

namespace engine3d::vk{
    
    VulkanWindow::VulkanWindow(uint32_t p_Width, uint32_t p_Height, const std::string& p_Title){
        if(!glfwInit()){
            throw std::runtime_error("glfwInit() failed to initialized");
        }

        if(!glfwVulkanSupported()){
            throw std::runtime_error("glfwVulkanSupported() failed because vulkan might not be supported!");
        }

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        uint32_t amountOfGlfwExtensions = 0;
        auto glfwExtensions = glfwGetRequiredInstanceExtensions(&amountOfGlfwExtensions);

        m_WindowHandler = glfwCreateWindow((int)p_Width, (int)p_Height, p_Title.c_str(), nullptr, nullptr);
        
        if(!m_WindowHandler){
            throw std::runtime_error("m_WindowHandler failed because was nullptr!");
        }

        glfwMakeContextCurrent(m_WindowHandler);
        
        if(Vulkan::GetVkInstance() == nullptr){
            throw std::runtime_error("Vulkan::GetVkSurface() was nullptr!");
        }

        VkResult res = glfwCreateWindowSurface(Vulkan::GetVkInstance(), m_WindowHandler, nullptr, &m_Surface);
        if(res != VK_SUCCESS){
            /* throw std::runtime_error("glfwCreateWindowSurface() failed because VKResult returned ===> " + VkResultToString(res)); */
            printf("VkResult (int) = %i\n", res);
        }

        m_IsCurrentWindowActive = true;
    }

    void VulkanWindow::OnUpdatePerTick(){
        glfwPollEvents();
    }

    VkSurfaceKHR& VulkanWindow::GetVkSurface(){ return m_Surface; }
    
    GLFWwindow* VulkanWindow::GetNativeWindow(){ return m_WindowHandler; }

    bool VulkanWindow::IsActive(){ return m_IsCurrentWindowActive; }
};
