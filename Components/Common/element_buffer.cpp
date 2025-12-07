#include "element_buffer.h"

namespace Hub
{
    SPElementBuffer ElementBuffer::create()
    {
        return SPElementBuffer(new ElementBuffer());
    }

    SPElementBuffer ElementBuffer::create(const void* data, size_t length, BufferUsage::buffer_usage_t usage)
    {
        return SPElementBuffer(new ElementBuffer(data, length, usage));
    }

    ElementBuffer::~ElementBuffer() {}

    ElementBuffer::ElementBuffer() : Buffer(buffer_t::ElementArrayBuffer) {}

    ElementBuffer::ElementBuffer(const void* data, size_t length, BufferUsage::buffer_usage_t usage) :
        Buffer(buffer_t::ElementArrayBuffer, data, length, usage)
    {}

} // namespace Hub