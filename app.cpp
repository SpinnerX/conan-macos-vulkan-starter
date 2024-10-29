#include <VulkanCpp/Vulkan.h>
#include <VulkanCpp/VulkanLogicalDevice.h>
#include <VulkanCpp/Application.h>
#include <vulkan/vulkan_core.h>
using namespace engine3d;



class EditorApplication : public Application{
public:
    EditorApplication() : Application(){}

protected:
    void OnUpdatePerTick() override {}
};

int main(){
    vk::Vulkan::InitializeVulkan();
    /* vk::VulkanLogicalDevice logical = vk::VulkanLogicalDevice(); */
    /* vk::VulkanPhysicalDevice physical = vk::VulkanPhysicalDevice(); */
    /* uint32_t queueFamily = physical.SelectDevice(VK_QUEUE_GRAPHICS_BIT, true); */

    EditorApplication* app = new EditorApplication();

    app->ExecuteMainloop();

}
