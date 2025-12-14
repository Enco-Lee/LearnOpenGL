#pragma once
#include <vector>
#include <glm/vec3.hpp>
//#include <rttr/registration>
//using namespace rttr;

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
