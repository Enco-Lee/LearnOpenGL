#pragma once
#include "gmath.h"

namespace Hub
{
    enum class CameraMovement
    {
        FORWORD,
        BACKWORD,
        LEFT,
        RIGHT
    };

    class Camera
    {
    public:
        Camera(const Camera&)            = delete;
        Camera(Camera&&)                 = delete;
        Camera& operator=(const Camera&) = delete;
        Camera& operator=(Camera&&)      = delete;

        Camera();

        Matrix4 getViewMatrix();
        Matrix4 getProjectionMatrix(float widthHeightRatio, float nearPlane = 0.1f, float farPlane = 100.f);

        void processKeyBoard(CameraMovement dirction, float deltaTime);
        void processMouseMovement(float xOffset, float yOffset, bool constrainPitch = true);
        void processMouseScroll(float yOffset);

        void    setPosition(const Vector3& pos);
        Vector3 getPosition();

        float getFov();
        void  setFov(float fov);

        Vector3 getFront() const;

        // 摄像机属性
        Vector3 _position;
        Vector3 _front;
        Vector3 _up;
        Vector3 _right;
        Vector3 _worldUp;

        // 摄像机角度
        float _yaw;
        float _pitch;

        // 摄像机其他相关配置
        float _moveSpeed;
        float _mouseSensitivity;
        float _fov;

    private:
        void updateCameraVectors();
    };
} // namespace Hub