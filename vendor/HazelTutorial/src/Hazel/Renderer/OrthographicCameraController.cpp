#include "hzpch.h"
#include "Hazel/Renderer/OrthographicCameraController.h"

#include "Hazel/Core/Input.h"
#include "Hazel/Core/KeyCodes.h"

namespace Hazel
{

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: m_AspectRatio(aspectRatio), 
		m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), 
		m_Rotation(rotation)
	{
	}

	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		HZ_PROFILE_FUNCTION();

		const bool keyWIsPressed = Hazel::Input::IsKeyPressed(Key::W);
		const bool keySIsPressed = Hazel::Input::IsKeyPressed(Key::S);

		if (keyWIsPressed && !keySIsPressed)
		{
			//m_CameraPosition.y += m_CameraTranslationSpeed * ts;
			m_CameraPosition.x += -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}
		else if (keySIsPressed && !keyWIsPressed)
		{
			//m_CameraPosition.y -= m_CameraTranslationSpeed * ts;
			m_CameraPosition.x -= -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}

		const bool keyAIsPressed = Hazel::Input::IsKeyPressed(Key::A);
		const bool keyDIsPressed = Hazel::Input::IsKeyPressed(Key::D);

		if (keyAIsPressed && !keyDIsPressed)
		{
			//m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
			m_CameraPosition.x -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y -= sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}
		else if (keyDIsPressed && !keyAIsPressed)
		{
			//m_CameraPosition.x += m_CameraTranslationSpeed * ts;
			m_CameraPosition.x += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y += sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}

		if (m_Rotation)
		{
			const bool keyQIsPressed = Hazel::Input::IsKeyPressed(Key::Q);
			const bool keyEIsPressed = Hazel::Input::IsKeyPressed(Key::E);

			if (keyQIsPressed && !keyEIsPressed)
				m_CameraRotation += m_CameraRotationSpeed * ts;
			else if (keyEIsPressed && !keyQIsPressed)
				m_CameraRotation -= m_CameraRotationSpeed * ts;

			if (m_CameraRotation > 180.0f)
				m_CameraRotation -= 360.0f;
			else if (m_CameraRotation <= -180.0f)
				m_CameraRotation += 360.0f;

			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPosition);
		m_CameraTranslationSpeed = m_ZoomLevel;
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		HZ_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(HZ_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(HZ_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	void OrthographicCameraController::OnResize(float width, float height)
	{
		m_AspectRatio = width / height;
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		HZ_PROFILE_FUNCTION();

		m_ZoomLevel -= e.GetYOffset() * 0.5f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		HZ_PROFILE_FUNCTION();

		OnResize((float)e.GetWidth(), (float)e.GetHeight());
		return false;
	}

}