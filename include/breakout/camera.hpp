#pragma once

#include <glm/glm.hpp>

namespace bk
{
    enum class CameraMovement
    {
        eForward,
        eBackward,
        eLeft,
        eRight,
        eUp,
        eDown,
    };

    class Camera
    {
    public:

        explicit Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
               glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
               float yaw = m_YAW,
               float pitch = m_PITCH);

        Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

        [[nodiscard]] glm::mat4 GetViewMatrix() const;

        void ProcessKeyboard(CameraMovement direction, float deltaTime);

        void ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch = true);

        void ProcessMouseScroll(float yOffset);


        /// Getters

        [[nodiscard]] glm::vec3 GetPosition() const { return m_Position; }

        [[nodiscard]] glm::vec3 GetFront() const { return m_Front; }

        [[nodiscard]] glm::vec3 GetUp() const { return m_Up; }

        [[nodiscard]] glm::vec3 GetRight() const { return m_Right; }

        [[nodiscard]] glm::vec3 GetWorldUp() const { return m_WorldUp; }

        [[nodiscard]] float GetYaw() const { return m_Yaw; }

        [[nodiscard]] float GetPitch() const { return m_Pitch; }

        [[nodiscard]] float GetRoll() const { return m_Roll; }

        [[nodiscard]] float GetMovementSpeed() const { return m_MovementSpeed; }

        [[nodiscard]] float GetMouseSensitivity() const { return m_MouseSensitivity; }

        [[nodiscard]] float GetZoom() const { return m_Zoom; }


        /// Setters

        void SetPosition(const glm::vec3& position) { m_Position = position; }

        void SetFront(const glm::vec3& front) { m_Front = front; }

        void SetUp(const glm::vec3& up) { m_Up = up; }

        void SetRight(const glm::vec3& right) { m_Right = right; }

        void SetWorldUp(const glm::vec3& worldUp) { m_WorldUp = worldUp; }

        void SetYaw(float yaw) { m_Yaw = yaw; }

        void SetPitch(float pitch) { m_Pitch = pitch; }

        void SetRoll(float roll) { m_Roll = roll; }

        void SetMovementSpeed(float speed) { m_MovementSpeed = speed; }

        void SetMouseSensitivity(float sensitivity) { m_MouseSensitivity = sensitivity; }

        void SetZoom(float zoom) { m_Zoom = zoom; }

    private:

        void UpdateCameraVectors();

        glm::vec3 m_Position { 0 };
        glm::vec3 m_Front { 0 };
        glm::vec3 m_Up { 0 };
        glm::vec3 m_Right { 0 };
        glm::vec3 m_WorldUp { 0 };

        // Euler Angles
        float m_Yaw { m_YAW };
        float m_Pitch { m_PITCH };
        float m_Roll { m_ROLL };

        // Camera options
        float m_MovementSpeed { m_SPEED };
        float m_MouseSensitivity { m_SENSITIVITY };
        float m_Zoom { m_ZOOM };

        // Default camera values
        constexpr static float m_YAW { -90.0f };
        constexpr static float m_PITCH { 0.0f };
        constexpr static float m_ROLL { 0.0f };
        constexpr static float m_SPEED { 2.5f };
        constexpr static float m_SENSITIVITY { 0.1f };
        constexpr static float m_ZOOM { 45.0f };

    };

} // tiny

