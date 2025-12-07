#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <algorithm>

namespace Hub
{
    Camera::Camera() :
        _position(Vector3(0.0f, 0.0f, 3.0f)), _up(Vector3(0.0f, 1.0f, 0.0f)), _yaw(-90.0f), _pitch(0.0f),
        _front(Vector3(0.0f, 0.0f, -1.0f)), _worldUp(Vector3(0.0f, 1.0f, 0.0f)), _moveSpeed(2.5f),
        _mouseSensitivity(0.1f), _fov(45.0f)

    {
        updateCameraVectors();
    }

    Matrix4 Camera::getViewMatrix()
    {
        return glm::lookAt(_position, _position + _front, _up);
    }

    Matrix4 Camera::getProjectionMatrix(float widthHeightRatio, float nearPlane, float farPlane)
    {
        return glm::perspective(glm::radians(_fov), widthHeightRatio, nearPlane, farPlane);
    }

    void Camera::processKeyBoard(CameraMovement dirction, float deltaTime)
    {
        float velocity = _moveSpeed * deltaTime;
        switch (dirction)
        {
            case CameraMovement::FORWORD:
                _position += _front * velocity;
                break;
            case CameraMovement::BACKWORD:
                _position -= _front * velocity;
                break;
            case CameraMovement::LEFT:
                _position -= _right * velocity;
                break;
            case CameraMovement::RIGHT:
                _position += _right * velocity;
                break;
        }
    }

    void Camera::processMouseMovement(float xOffset, float yOffset, bool constrainPitch /*= true*/)
    {
        xOffset *= _mouseSensitivity;
        yOffset *= _mouseSensitivity;
        _yaw += xOffset;
        _pitch += yOffset;
        if (constrainPitch)
        {
            _pitch = std::clamp(_pitch, -89.f, 89.f);
        }
        updateCameraVectors();
    }

    void Camera::processMouseScroll(float yOffset)
    {
        _fov -= yOffset;
        setFov(_fov);
    }

    void Camera::setPosition(const Vector3& pos)
    {
        _position = pos;
    }

    Vector3 Camera::getPosition()
    {
        return _position;
    }

    float Camera::getFov()
    {
        return _fov;
    }

    void Camera::setFov(float fov)
    {
        _fov = std::clamp(_fov, 1.f, 89.f);
    }

    Vector3 Camera::getFront() const
    {
        return _front;
    }

    void Camera::updateCameraVectors()
    {
        Vector3 front;
        auto    radianYaw   = glm::radians(_yaw);
        auto    radianPitch = glm::radians(_pitch);
        front.x             = std::cos(radianYaw) * std::cos(radianPitch);
        front.y             = std::sin(radianPitch);
        front.z             = std::sin(radianYaw) * std::cos(radianPitch);
        _front              = glm::normalize(front);
        _right              = glm::normalize(glm::cross(_front, _worldUp));
        _up                 = glm::normalize(glm::cross(_right, _front));
    }

} // namespace Hub