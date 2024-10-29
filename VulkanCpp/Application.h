#pragma once 
#include <VulkanCpp/VulkanWindow.h>

namespace engine3d{

    class Application{
    public:
        Application();

        void ExecuteMainloop();

        static vk::VulkanWindow& Get();

    protected:
        virtual void OnUpdatePerTick() = 0;
    private:
        vk::VulkanWindow m_Window;
    };
}
