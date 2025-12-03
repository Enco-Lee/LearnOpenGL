#include "windows_system.h"
#include "logger/logger.h"

namespace zh
{
    WindowSystem::~WindowSystem()
    {
        clear();
    }

    void WindowSystem::initialize(WindowInfo windowInfo)
    {
        if (!glfwInit())
        {
            LOG_FATAL("Failed to initialize a GLFW window.");
            return;
        }

        unsigned int majorVersion = 3;
        unsigned int minorVersion = 3;
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        _window = glfwCreateWindow(windowInfo.width, windowInfo.height, windowInfo.title, nullptr, nullptr);

        _width  = windowInfo.width;
        _height = windowInfo.height;

        if (!_window)
        {
            LOG_FATAL("Failed to create a GLFW window.");
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(_window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            LOG_FATAL("Failed to init GLAD.");
            return;
        }

        // glViewport(0, 0, _width, _height);
        glfwSetWindowUserPointer(_window, this);
        glfwSetKeyCallback(_window, onKey);
        glfwSetMouseButtonCallback(_window, onMouseButton);
        glfwSetScrollCallback(_window, onScroll);
        glfwSetCursorPosCallback(_window, onCursorPos);
        glfwSetWindowSizeCallback(_window, onWindowSize);
        glfwSetWindowCloseCallback(_window, onClose);
    }

    void WindowSystem::onKey(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (auto* app = static_cast<WindowSystem*>(glfwGetWindowUserPointer(window)))
        {
            app->onKey(key, scancode, action, mods);
        }
    }

    void WindowSystem::onMouseButton(GLFWwindow* window, int button, int action, int mods) {}

    void WindowSystem::onScroll(GLFWwindow* window, double xoffset, double yoffset) {}

    void WindowSystem::onCursorPos(GLFWwindow* window, double xpos, double ypos) {}

    void WindowSystem::onWindowSize(GLFWwindow* window, int width, int height) {}

    void WindowSystem::onClose(GLFWwindow* window) {}

    void WindowSystem::regisiterOnKeyCallback(onKeyCallback callback)
    {
        _onKeyCallbacks.push_back(callback);
    }

    void WindowSystem::registerOnMouseButtonCallback(onMouseButtonCallback callback) {}

    void WindowSystem::registerOnScrollCallback(onScrollCallback callback) {}

    void WindowSystem::registerOnCursorPosCallback(onCursorPosCallback callback) {}

    void WindowSystem::registerOnWindowSizeCallback(onWindowSizeCallback callback) {}

    void WindowSystem::registerOnCloseCallback(onCloseCallback callback) {}

    void WindowSystem::onKey(int key, int scancode, int action, int mods)
    {
        for (auto& callback : _onKeyCallbacks)
        {
            callback(key, scancode, action, mods);
        }
    }

    void WindowSystem::onMouseButton(int button, int action, int mods)
    {
        for (auto& callback : _onMouseButtonCallbacks)
        {
            callback(button, action, mods);
        }
    }

    void WindowSystem::onScroll(double xoffset, double yoffset) {}

    void WindowSystem::onCursorPos(double xpos, double ypos) {}

    void WindowSystem::onWindowSize(int width, int height) {}

    void WindowSystem::onClose() {}

    void WindowSystem::clear()
    {
        glfwDestroyWindow(_window);
        glfwTerminate();
    }
} // namespace zh
