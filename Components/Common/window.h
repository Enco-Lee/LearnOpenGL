#pragma once
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <memory>
#include <string>

namespace Hub
{
    namespace Status
    {
        enum class status_t
        {
            FAILED  = 0,
            SUCCESS = 1
        };
    }

    class Window
    {
        using WindowHandle = GLFWwindow*;

    public:
        Window(int width = 800, int height = 600, std::string name = "Window");
        ~Window();

        Status::status_t init();
        WindowHandle     getNativeHandle() const;

        void swapBuffer();
        void pollEvents();

        bool shouldClose() const;
        void setShouldClose(bool val);
        int  getKey(int key);

        void setFramebufferSizeCallback(GLFWframebuffersizefun callBack);
        void setKeyCallback(GLFWkeyfun callBack);

        int getWidth() const;
        int getHeight() const;

        int getFrameBufferWidth() const;
        int getFrameBufferHeight() const;

    private:
        int _width;
        int _height;

        std::string _name;
        GLFWwindow* _window = nullptr;

        void destroy();
    };
} // namespace Hub
