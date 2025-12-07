#pragma once
#include <glad/glad.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <iostream>
#include <string>

namespace Hub
{
    namespace Type
    {
        enum type_t
        {
            Byte          = GL_BYTE,
            UnsignedByte  = GL_UNSIGNED_BYTE,
            Short         = GL_SHORT,
            UnsignedShort = GL_UNSIGNED_SHORT,
            Int           = GL_INT,
            UnsignedInt   = GL_UNSIGNED_INT,
            Float         = GL_FLOAT,
            Double        = GL_DOUBLE,
        };

    }

    using uint = unsigned int;

    using Atrribute = GLint;
    using Uniform   = GLint;
    using Color     = glm::vec4;

    inline const float* color_ptr(const Color& color)
    {
        return glm::value_ptr(color);
    }
} // namespace Hub

inline GLenum glCheckError_(const char* file, int line)
{
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        std::string error;
        switch (errorCode)
        {
            case GL_INVALID_ENUM:
                error = "INVALID_ENUM";
                break;
            case GL_INVALID_VALUE:
                error = "INVALID_VALUE";
                break;
            case GL_INVALID_OPERATION:
                error = "INVALID_OPERATION";
                break;
            case GL_STACK_OVERFLOW:
                error = "STACK_OVERFLOW";
                break;
            case GL_STACK_UNDERFLOW:
                error = "STACK_UNDERFLOW";
                break;
            case GL_OUT_OF_MEMORY:
                error = "OUT_OF_MEMORY";
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                error = "INVALID_FRAMEBUFFER_OPERATION";
                break;
        }
        std::cout << error << " | " << file << " (" << line << ")" << std::endl;
    }
    return errorCode;
}

#define glCheckError() glCheckError_(__FILE__, __LINE__)
