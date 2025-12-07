#pragma once
#include "utils.h"

namespace Hub
{
    namespace BufferUsage
    {
        enum buffer_usage_t
        {
            StreamDraw  = GL_STREAM_DRAW,
            StreamRead  = GL_STREAM_READ,
            StreamCopy  = GL_STREAM_COPY,
            StaticDraw  = GL_STATIC_DRAW,
            StaticRead  = GL_STATIC_READ,
            StaticCopy  = GL_STREAM_COPY,
            DynamicDraw = GL_DYNAMIC_DRAW,
            DynamicRead = GL_DYNAMIC_READ,
            DynamicCopy = GL_DYNAMIC_COPY
        };
    }

    class Buffer
    {
    public:
        virtual ~Buffer();
        operator GLuint() const;
        void data(const void* data, size_t length, BufferUsage::buffer_usage_t usage);
        void subData(const void* data, size_t offset, size_t length);
        void getSubData(void* data, size_t offset, size_t length);

        enum buffer_t
        {
            ArrayBuffer        = GL_ARRAY_BUFFER,
            ElementArrayBuffer = GL_ELEMENT_ARRAY_BUFFER,
            UniformBuffer      = GL_UNIFORM_BUFFER,
        };

    protected:
        Buffer(buffer_t bufferType);
        Buffer(buffer_t bufferType, const void* data, size_t length, BufferUsage::buffer_usage_t usage);
        GLuint   _obj;
        buffer_t _bufferType;
    };

} // namespace Hub