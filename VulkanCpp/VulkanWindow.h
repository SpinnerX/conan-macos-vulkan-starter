#pragma once
#include <vulkan/vulkan_core.h>
#include <string>

class GLFWwindow;
namespace engine3d{
    namespace vk{
        /*
         * @note Represents our vulkan window wrapper that handles our swapchains are rendering images to our window.
        */
        struct Configurations{
            uint32_t width=900;
            uint32_t height = 600;
            std::string title="null";
        };

        class VulkanWindow{
        public:
            VulkanWindow(uint32_t p_Width, uint32_t p_Height, const std::string& p_Title);
            
            //! @note Helps us check if our current window surface is active.
            bool IsActive();

            //! @note Public Properties
            //! @note GetVkSurface() returns the vulkan surface of our window that we're rendering to.
            VkSurfaceKHR& GetVkSurface();
            GLFWwindow* GetNativeWindow();

            void OnUpdatePerTick();

        private:
            GLFWwindow* m_WindowHandler;
            VkSurfaceKHR m_Surface; // surface is what vulkan renders to.
            bool m_IsCurrentWindowActive=false;
        };
    };
};
