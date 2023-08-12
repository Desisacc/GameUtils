#pragma once

#include <Hazel.h>
#include "GT/Utils.h"

namespace GT {

	enum class CameraType : uint32_t
	{
		Invalid = 0, FreeMove, PlayerFocused
	};

	class CameraFocusedOnPlayer
	{
	public:
		static void OnUpdate(Vector3<uint32_t> playerPosition)
		{
			//HZ_INFO("FocusedOnPlayer class call!");
		}
	};

	class CameraFreeMove
	{
	public:
		template<typename Camera>
		static void OnUpdate(Camera& camera, Hazel::Timestep ts)
		{
			constexpr float SLOW_SPEED = 50.0f;
			constexpr float FAST_SPEED = 150.0f;

			const bool isKeyPressed_W = Hazel::Input::IsKeyPressed(Hazel::Key::W);
			const bool isKeyPressed_S = Hazel::Input::IsKeyPressed(Hazel::Key::S);
			const bool isKeyPressed_A = Hazel::Input::IsKeyPressed(Hazel::Key::A);
			const bool isKeyPressed_D = Hazel::Input::IsKeyPressed(Hazel::Key::D);

			const bool isKeyPressed_Shift = Hazel::Input::IsKeyPressed(Hazel::Key::LeftShift);

			camera.m_Speed = isKeyPressed_Shift ? SLOW_SPEED : FAST_SPEED;
			const float& cameraSpeed = camera.m_Speed;

			glm::vec3 cameraPosition = camera.m_Camera.GetPosition();

			if (isKeyPressed_W && !isKeyPressed_S)
				cameraPosition.y += cameraSpeed * ts;
			else if (!isKeyPressed_W && isKeyPressed_S)
				cameraPosition.y -= cameraSpeed * ts;

			if (isKeyPressed_D && !isKeyPressed_A)
				cameraPosition.x += cameraSpeed * ts;
			else if (isKeyPressed_A && !isKeyPressed_D)
				cameraPosition.x -= cameraSpeed * ts;

			cameraPosition.x = std::max(0.0f, cameraPosition.x);
			cameraPosition.x = std::min(std::max(0.0f, 1280.0f * 2.0f - 1280.0f), cameraPosition.x);

			cameraPosition.y = std::max(0.0f, cameraPosition.y);
			cameraPosition.y = std::min(std::max(0.0f, 720.0f * 2.0f - 720.0f), cameraPosition.y);

			camera.m_Camera.SetPosition(cameraPosition);
		}
	};

	template<typename CameraType, typename FuncOnEvent = std::function<void(Hazel::WindowResizeEvent&)>>
	class Camera
	{
	public:
		Camera() = default;
		void InitCamera(uint32_t windowWidth, uint32_t windowHeight, FuncOnEvent onEventFunction = nullptr)
		{
			m_Camera.SetProjection(0.0f, windowWidth, 0.0f, windowHeight);
			m_OnEventFunction = onEventFunction;
		}

		template<typename ... Args>
		void OnUpdate(Args&& ... args)
		{
			m_OnUpdateFunction(*this, std::forward<Args>(args)...);
		}

		void OnEvent(Hazel::Event& e)
		{
			Hazel::EventDispatcher dispatcher(e);
			
			auto& dispatchFunction = [this](Hazel::WindowResizeEvent& e) -> bool { return this->OnWindowResized(e); };
			dispatcher.Dispatch<Hazel::WindowResizeEvent>(dispatchFunction);
		}

		void SetProjection(uint32_t windowWidth, uint32_t windowHeight)
		{
			m_Camera.SetProjection(0.0f, windowWidth, 0.0f, windowHeight);
		}

		Hazel::OrthographicCamera& GetCamera() { return m_Camera; }
		const Hazel::OrthographicCamera& GetCamera() const { return m_Camera; }
	private:
		bool OnWindowResized(Hazel::WindowResizeEvent& e)
		{
			if (m_OnEventFunction)
				m_OnEventFunction(e);

			SetProjection(e.GetWidth(), e.GetHeight());
			return false;
		}
	private:
		float m_ZoomLevel = 1.0f;
		float m_Speed = 20.0f;
		Hazel::OrthographicCamera m_Camera = Hazel::OrthographicCamera(0.0f, 0.0f, 0.0f, 0.0f);

		decltype(&CameraType::OnUpdate<Camera<CameraType, FuncOnEvent>>) m_OnUpdateFunction = &CameraType::OnUpdate<Camera<CameraType, FuncOnEvent>>;
		FuncOnEvent m_OnEventFunction = nullptr;

		friend CameraType;
	};

}