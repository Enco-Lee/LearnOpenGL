#pragma once
#include <functional>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <memory>
#include <string>

namespace zh
{
    struct WindowInfo
    {
        int         width {1280};
        int         height {720};
        const char* title {"Hub"};
    };

    class WindowSystem
    {
    public:
        WindowSystem() = default;
        ~WindowSystem();

        void initialize(WindowInfo windowInfo);

        static void onKey(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void onMouseButton(GLFWwindow* window, int button, int action, int mods);
        static void onScroll(GLFWwindow* window, double xoffset, double yoffset);
        static void onCursorPos(GLFWwindow* window, double xpos, double ypos);
        static void onWindowSize(GLFWwindow* window, int width, int height);
        static void onClose(GLFWwindow* window);

        using onKeyCallback         = std::function<void(int, int, int, int)>;
        using onMouseButtonCallback = std::function<void(int, int, int)>;
        using onScrollCallback      = std::function<void(double, double)>;
        using onCursorPosCallback   = std::function<void(double, double)>;
        using onWindowSizeCallback  = std::function<void(int, int)>;
        using onCloseCallback       = std::function<void()>;

        void regisiterOnKeyCallback(onKeyCallback callback);
        void registerOnMouseButtonCallback(onMouseButtonCallback callback);
        void registerOnScrollCallback(onScrollCallback callback);
        void registerOnCursorPosCallback(onCursorPosCallback callback);
        void registerOnWindowSizeCallback(onWindowSizeCallback callback);
        void registerOnCloseCallback(onCloseCallback callback);

    protected:
        void onKey(int key, int scancode, int action, int mods);
        void onMouseButton(int button, int action, int mods);
        void onScroll(double xoffset, double yoffset);
        void onCursorPos(double xpos, double ypos);
        void onWindowSize(int width, int height);
        void onClose();

    private:
        void clear();

        GLFWwindow* _window {nullptr};

        int _width {0};
        int _height {0};

        std::vector<onKeyCallback>         _onKeyCallbacks;
        std::vector<onMouseButtonCallback> _onMouseButtonCallbacks;
        std::vector<onScrollCallback>      _onScrollCallbacks;
        std::vector<onCursorPosCallback>   _onCursorPosCallbacks;

        std::vector<onWindowSizeCallback> _onWindowSizeCallbacks;
        std::vector<onCloseCallback>      _onCloseCallbacks;
    };
} // namespace zh
