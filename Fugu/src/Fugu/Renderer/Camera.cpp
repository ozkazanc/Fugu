#include "fgpch.h"
#include "Camera.h"

#include "Fugu/Input.h"
#include "Fugu/KeyCodes.h"
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Fugu {
	Camera::Camera()
	{
		UpdateCameraVectors();
	}
	Camera::Camera(const glm::vec3& position, const glm::vec3& up)
		:m_Position(position),
		m_WorldUp(up)
	{
		UpdateCameraVectors();
	}

	void Camera::UpdateCameraVectors() {
		glm::vec3 front;
		front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		front.y = sin(glm::radians(m_Pitch));
		front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));

		m_Front = glm::normalize(front);
		m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
		m_Up = glm::normalize(glm::cross(m_Right, m_Front));
	}

	void Camera::OnUpdate(Timestep ts) {
		float ts_ = ts;
		if (Input::IsKeyPressed(FG_KEY_A)) {
			m_Position -= glm::rotate(m_Right, glm::radians(m_Rotation), m_Front) * m_MovementSpeed * ts_;
		}
		if (Input::IsKeyPressed(FG_KEY_D)) {
			m_Position += glm::rotate(m_Right, glm::radians(m_Rotation), m_Front) * m_MovementSpeed * ts_;
		}
		if (Input::IsKeyPressed(FG_KEY_S)) {
			m_Position -= glm::rotate(m_Up, glm::radians(m_Rotation), m_Front) * m_MovementSpeed * ts_;
		}
		if (Input::IsKeyPressed(FG_KEY_W)) {
			m_Position += glm::rotate(m_Up, glm::radians(m_Rotation), m_Front) * m_MovementSpeed * ts_;
		}
		if (Input::IsKeyPressed(FG_KEY_C)) {
			m_Position += m_Front * m_MovementSpeed * ts_;
		}
		if (Input::IsKeyPressed(FG_KEY_X)) {
			m_Position -= m_Front * m_MovementSpeed * ts_;
		}
		if (Input::IsKeyPressed(FG_KEY_Q)) {
			m_Rotation -= m_RotationSpeed * ts_;
		}
		if (Input::IsKeyPressed(FG_KEY_E)) {
			m_Rotation += m_RotationSpeed * ts_;
		}
		if (Input::IsKeyPressed(FG_KEY_P)) {
			FG_TRACE("Position: x={0}, y={1}, z={2}", m_Position.x, m_Position.y, m_Position.z);
		}

		if (m_Rotation > 180.0) { m_Rotation -= 360.0f; }
		else if (m_Rotation <= -180.0f) { m_Rotation += 360.0f; }
				
		//m_Front.y = 0.0f; // Uncomment if we want to keep the camera on the xz-axis. Similar to an actual FPS camera
		// We only take the xz component of Front vector so that we do not leave the ground(preventing looking up and flying up)
	}
	void Camera::OnEvent(Event& event) {
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FC(Camera::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FC(Camera::OnWindowResized));
		dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FC(Camera::OnMouseMoved));
	}

	glm::mat4 Camera::GetViewMatrix() const {
		return glm::lookAt(m_Position, m_Position + m_Front, glm::rotate(m_Up, glm::radians(m_Rotation), m_Front));
	}

	glm::mat4 Camera::GetViewProjectionMatrix() const { 
		return GetProjectionMatrix() * GetViewMatrix(); 
	}

	glm::mat4 Camera::GetProjectionMatrix() const {
		FG_CORE_ASSERT(false, "Should not access projection matrix of a projectionless camera!");
		return glm::mat4(1.0f);
	}

	bool Camera::OnMouseMoved(MouseMovedEvent& e) {
		if (m_LookAround) {
			float xPos_ = e.GetX();
			float yPos_ = e.GetY();
			if (m_FirstMouse)
			{
				m_LastX = xPos_;
				m_LastY = yPos_;
				m_FirstMouse = false;
			}

			float xOffset = xPos_ - m_LastX;
			float yOffset = m_LastY - yPos_; // reversed since y-coordinates go from bottom to top

			m_LastX = xPos_;
			m_LastY = yPos_;

			m_Yaw += xOffset * m_MouseSensetivity;
			m_Pitch += yOffset * m_MouseSensetivity;


			if (m_Pitch > 89.0f)
				m_Pitch = 89.0f;
			else if (m_Pitch < -89.0f)
				m_Pitch = -89.0f;

			UpdateCameraVectors();
		}
		return false;
	}
	bool Camera::OnMouseScrolled(MouseScrolledEvent& e)
	{
		if (m_Zoom >= 1.0f && m_Zoom <= 45.0f)
			m_Zoom -= e.GetYOffset();
		if (m_Zoom <= 1.0f)
			m_Zoom = 1.0f;
		if (m_Zoom >= 45.0f)
			m_Zoom = 45.0f;

		m_ZoomLevel -= e.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		return false;
	}

	bool Camera::OnWindowResized(WindowResizeEvent& e) {
		m_AspectRatio = static_cast<float>(e.GetWidth()) / static_cast<float>(e.GetHeight());
		return false;
	}

	OrthographicCamera::OrthographicCamera(float aspectRatio)
	{
		m_AspectRatio = aspectRatio;
		m_Width = aspectRatio;
		m_Height = 1.0f;
	}

	OrthographicCamera::OrthographicCamera(uint32_t width, uint32_t height)
		:m_Width((float)width),
		m_Height((float)height)
	{
		m_AspectRatio = static_cast<float>(width) / static_cast<float>(height);
	}

	OrthographicCamera::OrthographicCamera(float aspectRatio, const glm::vec3& position, const glm::vec3& up) 
		:Camera(position, up)
	{
		m_AspectRatio = aspectRatio;
		m_Width = aspectRatio;
		m_Height = 1.0f;
	}

	glm::mat4 OrthographicCamera::GetProjectionMatrix() const {
		return glm::ortho(-m_Width * m_ZoomLevel / 2.0f, m_Width * m_ZoomLevel / 2.0f, 
			-m_Height * m_ZoomLevel / 2.0f, m_Height * m_ZoomLevel / 2.0f,
			0.1f, 100.0f);
	}


	PerspectiveCamera::PerspectiveCamera(float aspectRatio)
	{
		m_AspectRatio = aspectRatio;
	}

	PerspectiveCamera::PerspectiveCamera(float aspectRatio, const glm::vec3& position, const glm::vec3& up)
		:Camera(position, up)
	{
		m_AspectRatio = aspectRatio;
	}

	glm::mat4 PerspectiveCamera::GetProjectionMatrix() const {
		return glm::perspective(glm::radians(m_Zoom), m_AspectRatio, 0.1f, 100.0f);
	}
}