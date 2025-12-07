#include "uniform_buffer.h"

namespace Hub
{

    SPUniformBuffer Hub::UniformBuffer::create()
    {
        return SPUniformBuffer(new UniformBuffer());
    }

    SPUniformBuffer Hub::UniformBuffer::create(const void* data, size_t length, BufferUsage::buffer_usage_t usage)
    {
        return SPUniformBuffer(new UniformBuffer(data, length, usage));
    }

    Hub::UniformBuffer::~UniformBuffer() {}

    void UniformBuffer::bindBufferRange(unsigned int point, unsigned int offset, unsigned int size)
    {
        glBindBufferRange(buffer_t::UniformBuffer, point, _obj, offset, size);
    }

    UniformBuffer::UniformBuffer() : Buffer(buffer_t::UniformBuffer) {}

    UniformBuffer::UniformBuffer(const void* data, size_t length, BufferUsage::buffer_usage_t usage) :
        Buffer(buffer_t::UniformBuffer, data, length, usage)
    {}

} // namespace Hub