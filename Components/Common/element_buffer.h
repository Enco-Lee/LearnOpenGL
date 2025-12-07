#pragma once
#include "utils.h"
#include "buffer.h"
#include <memory>

namespace Hub
{
    class ElementBuffer;
    using SPElementBuffer = std::shared_ptr<ElementBuffer>;

    class ElementBuffer final : public Buffer
    {
    public:
        static SPElementBuffer create();
        static SPElementBuffer create(const void* data, size_t length, BufferUsage::buffer_usage_t usage);

        ~ElementBuffer();

    private:
        ElementBuffer();
        ElementBuffer(const void* data, size_t length, BufferUsage::buffer_usage_t usage);
    };
} // namespace Hub