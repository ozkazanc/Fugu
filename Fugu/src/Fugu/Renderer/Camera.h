#pragma once
#include "Fugu/Timestep.h"
#include "Fugu/Events/MouseEvent.h"
#include "Fugu/Events/ApplicationEvent.h"

#include <glm/glm.hpp>

namespace Fugu {

	class Camera {
	protected:
		glm::vec3 m_Position = { 0.0f, 0.0f, 1.0f };
		glm::vec3 m_WorldUp = { 0.0f, 1.0f, 0.0f };

		glm::vec3 m_Front = { 0.0f, 0.0f, -1.0f };
		glm::vec3 m_Right = {0.0f , 0.0f, 0.0f };
		glm::vec3 m_Up = { 0.0f , 0.0f, 0.0f };

		const float m_MovementSpeed = 3.0f;
		float m_Yaw = -90.0f;
		float m_Pitch = 0.0f;
		float m_MouseSensetivity = 0.15f;

		const float m_RotationSpeed = 45.0f;
		float m_Rotation = 0.0f;

		float m_Zoom = 45.0f;
		float m_ZoomLevel = 1.0f;
		float m_AspectRatio = 1.6f / 0.9f;

		bool m_LookAround = false;
		bool m_FirstMouse = true;
		float m_LastX = 0.0f;
		float m_LastY = 0.0f;

	protected:
		void UpdateCameraVectors();
		
		bool OnMouseMoved(MouseMovedEvent& e);
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

	public:
		Camera();
		Camera(const glm::vec3& position, const glm::vec3& up);
		virtual ~Camera() = default;
		
		void OnEvent(Event& event);
		void OnUpdate(Timestep ts);

		glm::mat4 GetViewMatrix() const;
		glm::mat4 GetViewProjectionMatrix() const;
		virtual glm::mat4 GetProjectionMatrix() const;

		inline glm::vec3 GetCameraPosition() const { return m_Position; }
		inline void SetLookAround(bool lookAround) { m_LookAround = lookAround; }
	};

	class OrthographicCamera : public Camera {
	public:
		OrthographicCamera(float aspectRatio);
		OrthographicCamera(uint32_t width, uint32_t height);
		OrthographicCamera(float aspectRatio, const glm::vec3& position, const glm::vec3& up);

		virtual glm::mat4 GetProjectionMatrix() const override;
		void SetWidthHeight(float width, float height) { m_Width = width; m_Height = height; }
	private:
		float m_Width = 1;
		float m_Height = 1;
	};

	class PerspectiveCamera : public Camera {
	public:
		PerspectiveCamera(float aspectRatio);
		PerspectiveCamera(float aspectRatio, const glm::vec3& position, const glm::vec3& up);

		virtual glm::mat4 GetProjectionMatrix() const override;
	};
}