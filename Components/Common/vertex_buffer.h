#pragma once
#include "utils.h"
#include "buffer.h"
#include <memory>

namespace Hub
{
    class VertexBuffer;
    using SPVertexBuffer = std::shared_ptr<VertexBuffer>;

    class VertexBuffer final : public Buffer
    {
    public:
        static SPVertexBuffer create();
        static SPVertexBuffer create(const void* data, size_t length, BufferUsage::buffer_usage_t usage);

        ~VertexBuffer();

    private:
        VertexBuffer();
        VertexBuffer(const void* data, size_t length, BufferUsage::buffer_usage_t usage);
    };
} // namespace Hub