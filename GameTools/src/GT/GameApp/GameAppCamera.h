#pragma once

#include <Hazel.h>

#include "GT/Utils/Vectors.h"
#include "GT/Utils/GlobalData.h"

namespace GT {

	class GameAppCamera
	{
	public:
		struct CameraOnUpdateArguments
		{
			Vector3<float> ObjectToFollowPosition = { 0.0f, 0.0f, 0.0f };
			Vector2<float> ObjectToFollowSize = { 0.0f, 0.0f };
			Hazel::Timestep ts;
		};
	public:
		GameAppCamera() = default;
		virtual ~GameAppCamera() = default;
		void InitCamera(float windowWidth, float windowHeight)
		{
			m_Camera.SetProjection(0.0f, windowWidth, 0.0f, windowHeight);
		}

		virtual void OnUpdate(const CameraOnUpdateArguments& cameraOnUpdateArguments) = 0;

		void OnEvent(Hazel::Event& e)
		{
			Hazel::EventDispatcher dispatcher(e);

			dispatcher.Dispatch<Hazel::WindowResizeEvent>(HZ_BIND_EVENT_FN(GameAppCamera::OnWindowResizedCallback));
		}

		void SetProjection(float windowWidth, float windowHeight)
		{
			m_Camera.SetProjection(0.0f, windowWidth, 0.0f, windowHeight);
		}

		Hazel::OrthographicCamera& GetCamera() { return m_Camera; }
		const Hazel::OrthographicCamera& GetCamera() const { return m_Camera; }
	protected:
		virtual void OnWindowResize() {}

		bool OnWindowResizedCallback(Hazel::WindowResizeEvent& e)
		{
			OnWindowResize();

			SetProjection((float)e.GetWidth(), (float)e.GetHeight());
			return false;
		}
	protected:
		static constexpr float SLOW_SPEED = 50.0f;
		static constexpr float FAST_SPEED = 150.0f;
	protected:
		float m_ZoomLevel = 1.0f;
		float m_Speed = 20.0f;
		Hazel::OrthographicCamera m_Camera = Hazel::OrthographicCamera(0.0f, 0.0f, 0.0f, 0.0f);
	};

	namespace DefaultCameras {

		enum class Type : uint32_t
		{
			Invalid = 0, FreeMove, FocusedOnObject, Custom
		};

		class CameraFreeMove : public GameAppCamera
		{
		public:
			CameraFreeMove() = default;
			virtual ~CameraFreeMove() = default;

			virtual void OnUpdate(const CameraOnUpdateArguments& cameraOnUpdateArguments) override;
		};

		class CameraFocusedOnObject : public GameAppCamera
		{
		public:
			CameraFocusedOnObject() = default;
			virtual ~CameraFocusedOnObject() = default;

			virtual void OnUpdate(const CameraOnUpdateArguments& cameraOnUpdateArguments) override;
		};

	}

}