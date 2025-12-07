#pragma once
#include "window.h"
#include <memory>

namespace Hub
{
    class Application
    {
    public:
        Application() = default;

        virtual ~Application()
        {
            destory();

            glfwTerminate();
        }

        void init();

        virtual void initData() {};

        virtual void update(); // logic tick
        virtual void render(); // render tick
        void         run();    // main tick

        virtual void destory() {};

    protected:
        std::unique_ptr<Window> _currentWindow;

    private:
        void createContext(); // include init window
    };
} // namespace Hub