#include "gtpch.h"
#include "GT/GameApp/BaseGameApp.h"

namespace GT {

	void BaseGameApp::InitApp(const InitValues& initValues)
	{
		const uint32_t& windowWidth = initValues.WindowWidth;
		const uint32_t& windowHeight = initValues.WindowHeight;

		// Init GlobalGameData
		GlobalData::SetWindowSize({ windowWidth, windowHeight });
		GlobalData::SetMapSize({ initValues.MapWidth, initValues.MapHeight });

		// Init Camera
		switch (initValues.CameraType)
		{
		case DefaultCameras::Type::FreeMove:
			m_Camera = std::make_shared<DefaultCameras::CameraFreeMove>();
			break;
		case DefaultCameras::Type::FocusedOnObject:
			m_Camera = std::make_shared<DefaultCameras::CameraFocusedOnObject>();
			break;
		case DefaultCameras::Type::Custom:
			Assert(false, "CameraType Custom is not implemented!");
			break;
		default:
			Assert(false, "CameraType in initValues was invalid");
			break;
		}
		m_Camera->SetProjection((float)windowWidth, (float)windowHeight);

		Init();
	}

	void BaseGameApp::DestructApp()
	{
		Destruct();
	}

	void BaseGameApp::OnUpdateApp(Hazel::Timestep ts)
	{

		if (m_CurrentOverlay)
		{
			m_CurrentOverlay->OnUpdate(ts);

			if (m_CurrentOverlay && !m_CurrentOverlay->StopsGame())
			{
				OnUpdate(ts);

				if (!m_CurrentOverlay)
					m_Camera->OnUpdate(m_CameraOnUpdateArguments);
			}
		}
		else
		{
			OnUpdate(ts);

			// This is done so that overlay buttons don't get offset by the camera position
			if (!m_CurrentOverlay)
				m_Camera->OnUpdate(m_CameraOnUpdateArguments);
		}

		GlobalData::ClearMouseClicks();
	}

	void BaseGameApp::OnRenderApp()
	{
		Hazel::Renderer2D::ResetStats();
		Hazel::RenderCommand::SetClearColor({ 0.8f, 0.3f, 0.3f, 1 });
		Hazel::RenderCommand::Clear();

		Hazel::Renderer2D::BeginScene(m_Camera->GetCamera());

		if (m_CurrentOverlay)
		{
			m_CurrentOverlay->OnRender();

			if (!m_CurrentOverlay->CoversScreen())
				OnRender();
		}
		else
		{
			OnRender();
		}

		Hazel::Renderer2D::EndScene();
	}

	void BaseGameApp::OnImGuiRenderApp()
	{
		OnImGuiRender();
	}

	void BaseGameApp::OnEventApp(Hazel::Event& e)
	{
		Hazel::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<Hazel::WindowResizeEvent>(HZ_BIND_EVENT_FN(BaseGameApp::OnWindowResized));

		if (m_CurrentOverlay)
		{
			m_CurrentOverlay->OnEvent(e);

			if (!m_CurrentOverlay->CoversScreen())
				OnEvent(e);
		}
		else
		{
			OnEvent(e);
		}

		m_Camera->OnEvent(e);
	}

	/*void GameApp::InitGameApp(const InitValues& initValues)
	{
		const auto& windowWidth = initValues.WindowWidth;
		const auto& windowHeight = initValues.WindowHeight;

		// Init GlobalGameData
		GlobalData::SetWindowSize({ windowWidth, windowHeight });
		GlobalData::SetMapSize({ initValues.MapWidth, initValues.MapHeight });

		// Init Camera
		switch (initValues.CameraType)
		{
		case DefaultCameras::Type::FreeMove:
			m_Camera = std::make_shared<DefaultCameras::CameraFreeMove>();
			break;
		case DefaultCameras::Type::FocusedOnObject:
			m_Camera = std::make_shared<DefaultCameras::CameraFocusedOnObject>();
			break;
		case DefaultCameras::Type::Custom:
			Assert(false, "CameraType Custom is not implemented!");
			break;
		default:
			Assert(false, "CameraType in initValues was invalid");
			break;
		}
		m_Camera->SetProjection(windowWidth, windowHeight);
	}

	void GameApp::OnUpdate(const GameAppCamera::CameraOnUpdateArguments& cameraOnUpdateArguments)
	{
		m_Camera->OnUpdate(cameraOnUpdateArguments);
	}

	void GameApp::OnEvent(Hazel::Event& e)
	{
		Hazel::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<Hazel::WindowResizeEvent>(HZ_BIND_EVENT_FN(GameApp::OnWindowResized));

		m_Camera->OnEvent(e);
	}*/

}