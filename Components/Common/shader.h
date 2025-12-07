#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Hub
{
    class Shader
    {
    public:
        GLuint _programID;
        Shader() = default;
        // 构造器读取并构建 着色器
        Shader(const GLchar* vsPath, const GLchar* fsPath, const char* gsPath = nullptr);
        // 使用程序
        void use();

        void checkShaderCompile(const GLuint shader, const GLchar* filePath);
        void checkProgramLink();

        void setFloat(const GLchar* key, const GLfloat val);
        void setVec4(const GLchar* key, const glm::vec4& v);
        void setVec3(const GLchar* key, const glm::vec3& v);
        void setVec3(const GLchar* key, float x, float y, float z);
        void setVec2(const GLchar* key, const glm::vec2& v);
        void setInt(const GLchar* key, const GLint val);
        void setMatirx4(const GLchar* key, const glm::mat4& mat);
        void bindUniformBlock(const GLchar* key, unsigned int point);
    };
} // namespace Hub