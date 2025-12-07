#pragma once
#include <glm/glm.hpp>

namespace Hub
{
    using Vector2 = glm::vec2;
    using Vector3 = glm::vec3;
    using Vector4 = glm::vec4;

    using Matrix3 = glm::mat3;
    using Matrix4 = glm::mat4;

    using Real = float;

    inline Real length2(Vector3 v)
    {
        return v.x * v.x + v.y * v.y + v.z * v.z;
    }
} // namespace Hub
