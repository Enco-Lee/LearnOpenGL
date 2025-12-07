#pragma once
#include <vector>
#include <glm/vec3.hpp>
#include <rttr/registration>
using namespace rttr;

class Vector3
{
public:
    float getX() const
    {
        return value.x;
    }
    float getY() const
    {
        return value.y;
    }

    float getZ() const {
        return value.z;
    }

    void setX(float x)
    {
        value.x = x;
    }

    void setY(float y)
    {
        value.y = y;
    }
    void setZ(float z)
    {
        value.z = z;
    }

private:
    glm::vec3 value;
};

struct LineData
{
    int id;
    int color;
    std::vector<Vector3> points;
};

struct QuadData
{
    int id;
    int status;
    std::vector<Vector3> vertices;
};

struct ObstacleData
{
    int id;
    int color;

    Vector3 size;
    Vector3 rotation;
    Vector3 position;
};

RTTR_REGISTRATION
{
    using namespace rttr;
    registration::class_<Vector3>("Vector3")
        .property("x", &Vector3::getX, &Vector3::setX)
        .property("y", &Vector3::getY, &Vector3::setY)
        .property("z", &Vector3::getZ, &Vector3::setZ);

    registration::class_<LineData>("LineData")
        .property("id", &LineData::id)
        .property("color", &LineData::color)
        .property("points", &LineData::points);
}
