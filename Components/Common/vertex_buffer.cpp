#include "vertex_buffer.h"

namespace Hub
{

    SPVertexBuffer VertexBuffer::create()
    {
        return SPVertexBuffer(new VertexBuffer());
    }

    SPVertexBuffer VertexBuffer::create(const void* data, size_t length, BufferUsage::buffer_usage_t usage)
    {
        return SPVertexBuffer(new VertexBuffer(data, length, usage));
    }

    VertexBuffer::~VertexBuffer() {}

    VertexBuffer::VertexBuffer() : Buffer(buffer_t::ArrayBuffer) {}

    VertexBuffer::VertexBuffer(const void* data, size_t length, BufferUsage::buffer_usage_t usage) :
        Buffer(buffer_t::ArrayBuffer, data, length, usage)
    {}

} // namespace Hub