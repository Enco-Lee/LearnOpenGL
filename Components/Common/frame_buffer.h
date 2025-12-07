#pragma once
#include "utils.h"

namespace Hub
{
    class FrameBuffer;
    using SPFrameBuffer = std::shared_ptr<FrameBuffer>;

    class FrameBuffer
    {
    public:
        static SPFrameBuffer create();
        ~FrameBuffer();
        operator GLuint() const;

    private:
        FrameBuffer();
        GLuint _obj;
    };
} // namespace Hub