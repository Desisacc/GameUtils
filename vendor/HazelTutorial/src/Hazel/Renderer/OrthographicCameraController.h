#pragma once

#include "Hazel/Renderer/OrthographicCamera.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/MouseEvent.h"

#include "Hazel/Core/Timestep.h"

namespace Hazel
{

	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		void OnResize(float width, float height);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }

		float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(float level) { m_ZoomLevel = level; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;

		bool m_Rotation;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f; //In degrees, in the anti-clockwise direction
		float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;
	};

	// MODED
	template<typename ... Args>
	class CameraControllerSandboxTemplate
	{
	public:
		CameraControllerSandboxTemplate(float screenWidth, float screenHeight/*, std::function<void(Args ...)> onUpdate = nullptr*/) noexcept
			: m_Camera(0.0f, screenWidth, 0.0f, screenHeight)/*, m_OnUpdate(onUpdate)*/
		{
		}

		virtual void OnUpdate(Args ... args) = 0;
		/*{
			HZ_ASSERT(m_OnUpdate, "m_OnUpdate is nullptr");

			m_OnUpdate(std::forward<Args>(args) ...);
		}*/

		virtual void OnEvent(Hazel::Event& e) = 0;
		//{
		//	Hazel::EventDispatcher dispatcher(e);
		//	dispatcher.Dispatch<Hazel::WindowResizeEvent>(HZ_BIND_EVENT_FN(CameraControllerSandboxTemplate<Args ...>::OnWindowResized));
		//
		//	//dispatcher.Dispatch<Hazel::MouseScrolledEvent>(HZ_BIND_EVENT_FN(CameraControllerSandbox::OnMouseScrolled));
		//}

		/*
		void SetOnUpdateFunction(std::function<void(Args ...)> onUpdateFunction) { m_OnUpdate = onUpdateFunction; }
		// DEBUG
		std::function<void(Args ...)> GetOnUpdateFunc() { return m_OnUpdate; }
		// DEBUG
		
		Hazel::OrthographicCamera& GetCamera() { return m_Camera; }
		const Hazel::OrthographicCamera& GetCamera() const { return m_Camera; }

		float GetCameraSpeed() const { return m_Speed; }
		void SetCameraSpeed(float speed) { m_Speed = speed; }

		float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(float level) { m_ZoomLevel = level; }
		*/
	public:
		virtual bool OnWindowResized(Hazel::WindowResizeEvent& e) = 0;
		/*{
			Global::SetScreenWidth(e.GetWidth());
			Global::SetScreenHeight(e.GetHeight());

			m_Camera.SetProjection(0.0f, (float)Global::GetScreenWidth(), 0.0f, (float)Global::GetScreenHeight());
			return false;
		}*/

		//bool OnMouseScrolled(Hazel::MouseScrolledEvent& e);
	public:
		float m_ZoomLevel = 1.0f;
		float m_Speed = 20.0f;
		Hazel::OrthographicCamera m_Camera;

		//std::function<void(Args ...)> m_OnUpdate = nullptr;
	};
	// MODED

}