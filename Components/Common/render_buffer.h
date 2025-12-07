#pragma once
#include "utils.h"

namespace Hub
{
    class RenderBuffer;
    using SPRenderBuffer = std::shared_ptr<RenderBuffer>;

    class RenderBuffer
    {
    public:
        static SPRenderBuffer create();
        ~RenderBuffer();
        operator GLuint() const;

    private:
        RenderBuffer();
        GLuint _obj;
    };
} // namespace Hub