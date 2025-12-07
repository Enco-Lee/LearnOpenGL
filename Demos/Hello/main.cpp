#include "application.h"
#include "shader.h"
#include "vertex_array.h"
#include "vertex_buffer.h"

namespace Hub
{
    class HelloApp : public Application
    {
    public:
        void initData()
        {
            shader             = Shader("./shader/shader.vs", "./shader/shader.fs");
            GLfloat vertices[] = {
                // 位置             // 颜色
                0.5f,
                -0.5f,
                0.0f,
                1.0f,
                0.0f,
                0.0f, // 右下
                -0.5f,
                -0.5f,
                0.0f,
                0.0f,
                1.0f,
                0.0f, // 左下
                0.0f,
                0.5f,
                0.0f,
                0.0f,
                0.0f,
                1.0f // 顶部
            };
            VAO = VertexArray::create();
            VBO = VertexBuffer::create(vertices, sizeof(vertices), BufferUsage::buffer_usage_t::StaticDraw);
            VAO->bindAttribute(0, 3, *VBO, Type::Float, 6 * sizeof(float), 0 * sizeof(float));
            VAO->bindAttribute(1, 3, *VBO, Type::Float, 6 * sizeof(float), 3 * sizeof(float));
        }

        void update() {}

        void render()
        {
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            // Draw
            shader.use();
            glBindVertexArray(*VAO);
            glDrawArrays(GL_TRIANGLES, 0, 3);
            glBindVertexArray(0);
        }

    private:
        Shader         shader;
        SPVertexArray  VAO;
        SPVertexBuffer VBO;
    };
} // namespace Hub

int main()
{
    using namespace Hub;
    HelloApp app;
    app.run();
    return 0;
}