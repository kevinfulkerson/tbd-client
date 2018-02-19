#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "glm/glm.hpp"

namespace tbd
{
    class Camera
    {
      public:
        Camera();
        virtual ~Camera();

        void SetFOVRadians(float fovyRad);
        void SetFOVDegrees(float fovyDeg);
        void SetAspectRatio(float ratio);
        void SetNear(float near);
        void SetFar(float far);

        void SetFacing(const glm::vec3 &newFacing);
        void MoveFacing(const glm::vec3 &facingIncrement);
        void SetLocation(const glm::vec3 &newLocation);
        void MoveLocation(const glm::vec3 &locationIncrement);
        void SetUp(const glm::vec3 &up);

        glm::mat4 GetProjectionMatrix() const;
        glm::mat4 GetViewMatrix() const;

      private:
        glm::vec3 m_facing;
        glm::vec3 m_location;
        glm::vec3 m_up;

        float m_fovyRadians;
        float m_aspectRatio;
        float m_near;
        float m_far;

        glm::mat4 m_projectionMatrix;
        glm::mat4 m_viewMatrix;

        void setProjectionMatrix();
        void setViewMatrix();
    };
}

#endif //_CAMERA_H_