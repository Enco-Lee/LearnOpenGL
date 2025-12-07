#include "application.h"

namespace Hub
{
    void Application::init()
    {
        // init opengl
        createContext();
        // init data
        initData();
    }

    void Application::update()
    {
        // object update

        // input update
    }

    void Application::render()
    {
        // mesh render
    }

    void Application::run()
    {
        init();
        while (!_currentWindow->shouldClose())
        {
            update();
            render();

            // double buffer
            _currentWindow->swapBuffer();
            // events
            _currentWindow->pollEvents();
        }
    }

    void Application::createContext()
    {
        //
        _currentWindow = std::make_unique<Window>();
    }

} // namespace Hub
