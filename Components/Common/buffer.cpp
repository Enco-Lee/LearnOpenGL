#include "buffer.h"

namespace Hub
{
    Buffer::Buffer(buffer_t bufferType) : _bufferType(bufferType)
    {
        glGenBuffers(1, &_obj);
    }

    Buffer::~Buffer()
    {
        glDeleteBuffers(1, &_obj);
    }

    Buffer::operator GLuint() const
    {
        return _obj;
    }

    void Buffer::data(const void* data, size_t length, BufferUsage::buffer_usage_t usage)
    {
        glBindBuffer(_bufferType, _obj);
        glBufferData(_bufferType, length, data, usage);
    }

    void Buffer::subData(const void* data, size_t offset, size_t length)
    {
        glBindBuffer(_bufferType, _obj);
        glBufferSubData(_bufferType, offset, length, data);
    }

    void Buffer::getSubData(void* data, size_t offset, size_t length)
    {
        glBindBuffer(_bufferType, _obj);
        glGetBufferSubData(_bufferType, offset, length, data);
    }

    Buffer::Buffer(buffer_t bufferType, const void* data, size_t length, BufferUsage::buffer_usage_t usage) :
        Buffer(bufferType)
    {
        this->data(data, length, usage);
    }
} // namespace Hub