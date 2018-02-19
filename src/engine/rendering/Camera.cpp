#include "src/engine/rendering/Camera.hpp"

#include "glm/ext.hpp"

namespace tbd
{
    Camera::Camera() : m_facing(0.f, 0.f, 0.f),
                       m_location(0.f, 0.f, 0.f),
                       m_up(0.f, 0.f, 0.f),
                       m_fovyRadians(0.f),
                       m_aspectRatio(0.f),
                       m_near(0.f),
                       m_far(0.f)
    {
        setProjectionMatrix();
        setViewMatrix();
    }

    /* virtual */
    Camera::~Camera()
    {
    }

    void Camera::SetFOVRadians(float fovyRad)
    {
        m_fovyRadians = fovyRad;
        setProjectionMatrix();
    }

    void Camera::SetFOVDegrees(float fovyDeg)
    {
        m_fovyRadians = glm::radians(fovyDeg);
        setProjectionMatrix();
    }

    void Camera::SetAspectRatio(float ratio)
    {
        m_aspectRatio = ratio;
        setProjectionMatrix();
    }

    void Camera::SetNear(float near)
    {
        m_near = near;
        setProjectionMatrix();
    }

    void Camera::SetFar(float far)
    {
        m_far = far;
        setProjectionMatrix();
    }

    void Camera::SetFacing(const glm::vec3 &newFacing)
    {
        m_facing = newFacing;
        setViewMatrix();
    }

    void Camera::MoveFacing(const glm::vec3 &facingIncrement)
    {
        m_facing += facingIncrement;
        setViewMatrix();
    }

    void Camera::SetLocation(const glm::vec3 &newLocation)
    {
        m_location = newLocation;
        setViewMatrix();
    }

    void Camera::MoveLocation(const glm::vec3 &locationIncrement)
    {
        m_location += locationIncrement;
        setViewMatrix();
    }

    void Camera::SetUp(const glm::vec3 &up)
    {
        m_up = up;
        setViewMatrix();
    }

    glm::mat4 Camera::GetProjectionMatrix() const
    {
        return m_projectionMatrix;
    }

    glm::mat4 Camera::GetViewMatrix() const
    {
        return m_viewMatrix;
    }

    void Camera::setProjectionMatrix()
    {
        m_projectionMatrix = glm::perspective(
            m_fovyRadians, m_aspectRatio, m_near, m_far);
    }

    void Camera::setViewMatrix()
    {
        m_viewMatrix = glm::lookAt(m_location, m_facing, m_up);
    }
}