
#include "breakout/camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace bk
{

    Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : m_Position(position), m_WorldUp(up), m_Yaw(yaw), m_Pitch(pitch)
    {
        UpdateCameraVectors();
    }

    Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
    : m_Position(glm::vec3(posX, posY, posZ)), m_WorldUp(glm::vec3(upX, upY, upZ)), m_Yaw(yaw), m_Pitch(pitch)
    {
        UpdateCameraVectors();
    }

    glm::mat4 Camera::GetViewMatrix() const
    {
        return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
    }

    void Camera::ProcessKeyboard(CameraMovement direction, float deltaTime)
    {
        float velocity = m_MovementSpeed * deltaTime;
        if (direction == CameraMovement::eForward)
            m_Position += m_Front * velocity;
        if (direction == CameraMovement::eBackward)
            m_Position -= m_Front * velocity;
        if (direction == CameraMovement::eLeft)
            m_Position -= m_Right * velocity;
        if (direction == CameraMovement::eRight)
            m_Position += m_Right * velocity;
        if (direction == CameraMovement::eUp)
            m_Position += m_Up * velocity;
        if (direction == CameraMovement::eDown)
            m_Position -= m_Up * velocity;

    }

    void Camera::ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch)
    {
        xOffset *= m_MouseSensitivity;
        yOffset *= m_MouseSensitivity;

        m_Yaw += xOffset;
        m_Pitch += yOffset;

        // Make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch)
        {
            if (m_Pitch > 89.0f)
                m_Pitch = 89.0f;
            if (m_Pitch < -89.0f)
                m_Pitch = -89.0f;
        }

        // Update Front, Right and Up Vectors using the updated Euler angles
        UpdateCameraVectors();
    }

    void Camera::ProcessMouseScroll(float yoffset)
    {
        if (m_Zoom >= 1.0f && m_Zoom <= 45.0f)
            m_Zoom -= yoffset;
        if (m_Zoom <= 1.0f)
            m_Zoom = 1.0f;
        if (m_Zoom >= 45.0f)
            m_Zoom = 45.0f;
    }

    void Camera::UpdateCameraVectors()
    {
        // Calculate the new Front vector
        glm::vec3 front;
        front.x = static_cast<float>(cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch)));
        front.y = static_cast<float>(sin(glm::radians(m_Pitch)));
        front.z = static_cast<float>(sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch)));

        m_Front = glm::normalize(front);

        // Also re-calculate the Right and Up vector
        m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        m_Up    = glm::normalize(glm::cross(m_Right, m_Front));
    }
} // namespace breakout
