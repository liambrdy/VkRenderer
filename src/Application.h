#pragma once

#include <glad/vulkan.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <vector>
#include <string>
#include <optional>
#include <array>

const int MAX_FRAMES_IN_FLIGHT = 2;

struct QueueFamilyIndices
{
    std::optional<uint32_t> graphicsFamily, presentFamily;

    bool IsComplete()
    {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

struct SwapChainSupportDetail
{
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

struct Vertex
{
    glm::vec2 position;
    glm::vec3 color;

    static VkVertexInputBindingDescription GetBindingDescription()
    {
        VkVertexInputBindingDescription description = {};
        description.binding = 0;
        description.stride = sizeof(Vertex);
        description.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

        return description;
    }

    static std::array<VkVertexInputAttributeDescription, 2> GetAttributeDescriptions()
    {
        std::array<VkVertexInputAttributeDescription, 2> descriptions = {};
        descriptions[0].binding = 0;
        descriptions[0].location = 0;
        descriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
        descriptions[0].offset = offsetof(Vertex, position);

        descriptions[1].binding = 0;
        descriptions[1].location = 1;
        descriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        descriptions[1].offset = offsetof(Vertex, color);

        return descriptions;
    } 
};

class Application
{
public:
    Application(uint32_t width, uint32_t height);
    virtual ~Application();

    void SetFramebufferResized(bool resized) { m_framebufferResized = resized; }

    void Run();
private:
    void InitVulkan();
    void ShutdownVulkan();

    void DrawFrame();

    void CreateInstance();
    void CreateDebugMessenger();
    void CreateSurface();
    void GetPhysicalDevice();
    void CreateLogicalDevice();
    void CreateSwapChain();
    void CreateImageViews();
    void CreateRenderPass();
    void CreateGraphicsPipeline();
    void CreateFramebuffers();
    void CreateCommandPool();
    void CreateVertexBuffer();
    void CreateCommandBuffers();
    void CreateSyncObjects();

    std::vector<const char*> GetRequiredExtensions();
    bool CheckValidationLayerSupport();
    void GetDebugMessageCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& debugCreateInfo);
    bool CheckDeviceExtensionSuport(VkPhysicalDevice device);
    VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
    void RecreateSwapChain();
    void CleanupSwapChain();
    uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

    VkShaderModule CreateShaderModule(const std::vector<char>& src);

    QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
    SwapChainSupportDetail QuerySwapChainSupport(VkPhysicalDevice device);
private:
    GLFWwindow* m_window;
    uint32_t m_width, m_height;
    bool m_framebufferResized = false;

    const std::vector<const char*> m_validationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };

    const std::vector<const char*> m_deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    const std::vector<Vertex> m_vertices = {
        {{ 0.0f, -0.5f }, { 1.0f, 1.0f, 1.0f }},
        {{ 0.5f, 0.5f }, { 0.0f, 1.0f, 0.0f }},
        {{ -0.5f, 0.5f }, { 0.0f, 0.0f, 1.0f }}
    };

    VkInstance m_instance;
    VkDebugUtilsMessengerEXT m_debugMessenger;
    VkSurfaceKHR m_surface;
    VkPhysicalDevice m_physicalDevice;
    VkDevice m_device;
    VkQueue m_graphicsQueue, m_presentQueue;
    VkRenderPass m_renderPass;
    VkPipelineLayout m_pipelineLayout;
    VkPipeline m_graphicsPipeline;
    VkCommandPool m_commandPool;
    std::vector<VkCommandBuffer> m_commandBuffers;
    std::vector<VkSemaphore> m_imageAvailableSemaphores, m_renderFinishedSemaphores;
    std::vector<VkFence> m_inFlightFences;
    std::vector<VkFence> m_imagesInFlight;
    uint32_t m_currentFrame = 0;

    VkBuffer m_vertexBuffer;
    VkDeviceMemory m_vertexBufferMemory;

    VkSwapchainKHR m_swapChain;
    std::vector<VkImage> m_swapChainImages;
    std::vector<VkImageView> m_swapChainImageViews;
    std::vector<VkFramebuffer> m_swapChainFramebuffers;
    VkFormat m_swapChainImageFormat;
    VkExtent2D m_swapChainExtent;

    QueueFamilyIndices m_indices;
    SwapChainSupportDetail m_details;
};