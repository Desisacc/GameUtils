#pragma once

#include <memory>

#include <Hazel.h>
#include <imgui.h>

#include "GT/Utils/Vectors.h"
#include "GT/Utils/GlobalData.h"
#include "GT/GameApp/GameAppCamera.h"
#include "GT/GameApp/Overlay.h"

// TODO: Change our own vector<> class for a typedef of glm::vec class, it's just easier and better...
// TODO: Template GlobalData so it returns multiple types
// TODO: Change update camera and overlay situation, overlay elements are rendered in incorrect positions whenever the camera position is not { 0, 0 }

// TODO: Add default behavior for mouse clicks relative to the screen and map
// TODO: Fix Hitbox component by implementing hitbox offset
// TODO: Change how static spritesheets work, each instance should share the same Hazel::Texture2D 
// but retain different information on when the spritesheet should be updated
// an option could be separating the spritesheet info from the actual rendering implementation (SpriteSheetView)
// TODO: Change name of instance of spritesheet to something different to the class name

namespace GT {

	class BaseGameApp
	{
	public:
		struct InitValues
		{
			uint32_t WindowWidth = Hazel::WindowProps::DEFAULT_WINDOW_WIDTH;
			uint32_t WindowHeight = Hazel::WindowProps::DEFAULT_WINDOW_HEIGHT;
			uint32_t MapWidth = Hazel::WindowProps::DEFAULT_WINDOW_WIDTH;
			uint32_t MapHeight = Hazel::WindowProps::DEFAULT_WINDOW_HEIGHT;
			DefaultCameras::Type CameraType = DefaultCameras::Type::Invalid;
		};
	public:
		BaseGameApp() = default;
		void InitApp(const InitValues& initValues);
		void DestructApp();

		void OnUpdateApp(Hazel::Timestep ts);
		void OnRenderApp();
		void OnImGuiRenderApp();
		void OnEventApp(Hazel::Event& e);

		void QuitCurrentOverlay() 
		{ 
			m_CurrentOverlay = nullptr;
			m_Camera->GetCamera().SetPosition({ m_SavedCameraPosition.x, m_SavedCameraPosition.y, m_SavedCameraPosition.z });
		}
		void SetCurrentOverlay(const std::string& name)
		{
			auto overlayIt = m_Overlays.find(name);
			Assert(overlayIt != m_Overlays.end(), "{0} overlay could not be found!", name.c_str());
			m_CurrentOverlay = &overlayIt->second;

			const glm::vec3& cameraPosition = m_Camera->GetCamera().GetPosition();
			m_SavedCameraPosition = { cameraPosition.x, cameraPosition.y, cameraPosition.z };
			m_Camera->GetCamera().SetPosition({ 0.0f, 0.0f, 0.0f });
		}
	protected:
		virtual void Init() = 0;
		virtual void Destruct() {};
		virtual void OnUpdate(Hazel::Timestep ts) = 0;
		virtual void OnRender() = 0;
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Hazel::Event& e) {}

		Vector2<float> GetCameraPosition() const 
		{ 
			const glm::vec3& cameraPosition = m_Camera->GetCamera().GetPosition();
			return { cameraPosition.x, cameraPosition.y };
		}
		Overlay& AddOverlay(const std::string& name) 
		{ 
			return m_Overlays[name]; 
		}

		bool OnMouseClickEvent(Hazel::MouseButtonPressedEvent& e)
		{
			if (e.GetMouseButton() == Hazel::Mouse::ButtonLeft)
				GlobalData::AddMouseClick(GT::Input::GetMousePosition());

			return false;
		}
	protected:
		GT::GameAppCamera::CameraOnUpdateArguments m_CameraOnUpdateArguments;

		std::unordered_map<std::string, GT::Overlay> m_Overlays;
		GT::Overlay* m_CurrentOverlay = nullptr;
	private:
		bool OnWindowResized(Hazel::WindowResizeEvent& e)
		{
			GlobalData::SetWindowSize({ e.GetWidth(), e.GetHeight() });
			return false;
		}
	private:
		std::shared_ptr<GameAppCamera> m_Camera = nullptr;
		GT::Vector3<float> m_SavedCameraPosition = { 0.0f, 0.0f, 0.0f };
	};

	/*class GameApp
	{
	public:
		struct InitValues
		{
			uint32_t WindowWidth = Hazel::WindowProps::DEFAULT_WINDOW_WIDTH;
			uint32_t WindowHeight = Hazel::WindowProps::DEFAULT_WINDOW_HEIGHT;
			uint32_t MapWidth = Hazel::WindowProps::DEFAULT_WINDOW_WIDTH;
			uint32_t MapHeight = Hazel::WindowProps::DEFAULT_WINDOW_HEIGHT;
			DefaultCameras::Type CameraType = DefaultCameras::Type::Invalid;
		};
	public:
		GameApp() = default;
		void InitGameApp(const InitValues& initValues);

		void OnUpdate(const GameAppCamera::CameraOnUpdateArguments& cameraOnUpdateArguments);
		void OnEvent(Hazel::Event& e);

		const std::shared_ptr<GameAppCamera>& GetCamera() const { return m_Camera; }
	private:
		bool OnWindowResized(Hazel::WindowResizeEvent& e)
		{
			GlobalData::SetWindowSize({ e.GetWidth(), e.GetHeight() });

			return false;
		}
	private:
		std::shared_ptr<GameAppCamera> m_Camera = nullptr;
	};*/

}