#include "frame_buffer.h"

namespace Hub
{
    SPFrameBuffer FrameBuffer::create()
    {
        return SPFrameBuffer(new FrameBuffer());
    }

    FrameBuffer::~FrameBuffer()
    {
        glDeleteBuffers(1, &_obj);
    }

    FrameBuffer::operator GLuint() const
    {
        return _obj;
    }

    FrameBuffer::FrameBuffer()
    {
        glGenFramebuffers(1, &_obj);
    }

} // namespace Hub