#include "VulkanCpp/VulkanWindow.h"
#include <VulkanCpp/Application.h>


namespace engine3d{
    static Application* g_Instance = nullptr;

    Application::Application() : m_Window(900,600, "Engine3D"){
        g_Instance = this;
    }

    void Application::ExecuteMainloop(){
        while(m_Window.IsActive()){
            m_Window.OnUpdatePerTick();
        }
    }

    vk::VulkanWindow& Application::Get(){ return g_Instance->m_Window; }
};
