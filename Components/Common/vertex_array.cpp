#include "vertex_array.h"

namespace Hub
{
    SPVertexArray VertexArray::create()
    {
        return SPVertexArray(new VertexArray());
    }

    VertexArray::~VertexArray()
    {
        glDeleteVertexArrays(1, &_obj);
    }

    VertexArray::operator GLuint() const
    {
        return _obj;
    }

    void VertexArray::bindAttribute(const Atrribute&    atrribute,
                                    uint                count,
                                    const VertexBuffer& buffer,
                                    Type::type_t        type,
                                    uint                stride,
                                    intptr_t            offset)
    {
        glBindVertexArray(_obj);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glEnableVertexAttribArray(atrribute);
        glVertexAttribPointer(atrribute, count, type, GL_FALSE, stride, (GLvoid*)(offset));
    }

    void VertexArray::bindElements(const ElementBuffer& element)
    {
        glBindVertexArray(_obj);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element);
    }

    void VertexArray::bindTransformFeedback(uint index, const VertexBuffer& buffer)
    {
        glBindVertexArray(_obj);
        glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, index, buffer);
    }

    VertexArray::VertexArray()
    {
        glGenVertexArrays(1, &_obj);
    }

} // namespace Hub