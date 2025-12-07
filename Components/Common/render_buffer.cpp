#include "render_buffer.h"

namespace Hub
{
    SPRenderBuffer Hub::RenderBuffer::create()
    {
        return SPRenderBuffer(new RenderBuffer());
    }

    RenderBuffer::~RenderBuffer()
    {
        glDeleteBuffers(1, &_obj);
    }

    RenderBuffer::operator GLuint() const
    {
        return _obj;
    }

    RenderBuffer::RenderBuffer()
    {
        glGenRenderbuffers(1, &_obj);
    }

} // namespace Hub