set(VULKAN_INCLUDE_DIR ../VulkanCpp)
set(VULKAN_SRC_DIR VulkanCpp)


set(
    all_headers
    ${VULKAN_INCLUDE_DIR}/Application.h
    ${VULKAN_INCLUDE_DIR}/Vulkan.h
    ${VULKAN_INCLUDE_DIR}/VulkanPhysicalDevice.h
    ${VULKAN_INCLUDE_DIR}/VulkanLogicalDevice.h
    ${VULKAN_INCLUDE_DIR}/helper_functions.h
    ${VULKAN_INCLUDE_DIR}/VulkanDebugHelper.h
    ${VULKAN_INCLUDE_DIR}/VulkanWindow.h
)

set(
    all_src
    ${VULKAN_SRC_DIR}/Application.cpp
    ${VULKAN_SRC_DIR}/Vulkan.cpp
    ${VULKAN_SRC_DIR}/VulkanPhysicalDevice.cpp
    ${VULKAN_SRC_DIR}/VulkanLogicalDevice.cpp
    ${VULKAN_SRC_DIR}/helper_functions.cpp
    ${VULKAN_SRC_DIR}/VulkanDebugHelper.cpp
    ${VULKAN_SRC_DIR}/VulkanWindow.cpp
    ../app.cpp
)

add_executable(${PROJECT_NAME} ${all_headers} ${all_src})
