#include "MouseGame/MouseGameLayer.h"

namespace MouseGameLayer {

	MouseGame::MouseGame()
		: Layer("MouseGameLayer") {}

	void MouseGame::OnAttach()
	{
		Hazel::Renderer2D::SetQuadCenter(Hazel::Renderer2D::QuadCenter::LeftBottom);

		m_App = std::make_unique<MouseGameApp>();

		GT::BaseGameApp::InitValues gameAppInitValues;
		gameAppInitValues.CameraType = GT::DefaultCameras::Type::FreeMove;
		m_App->InitApp(gameAppInitValues);
	}

	void MouseGame::OnDetach()
	{
		m_App->DestructApp();
	}

	void MouseGame::OnUpdate(Hazel::Timestep ts)
	{
		if (ts > 0.018f)
		{
			HZ_WARN("ts was more than 18 ms, {0}", (float)ts);
			ts = 0.018f;
		}

		m_App->OnUpdateApp(ts);

		m_App->OnRenderApp();
	}

	void MouseGame::OnImGuiRender()
	{
		m_App->OnImGuiRenderApp();
	}

	void MouseGame::OnEvent(Hazel::Event& e)
	{
		m_App->OnEventApp(e);
	}

}