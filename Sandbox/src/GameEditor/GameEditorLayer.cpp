#include "GameEditor/GameEditorLayer.h"

namespace GameEditorLayer {

	GameEditor::GameEditor()
		: Layer("GameEditorLayer") {}

	void GameEditor::OnAttach()
	{
		Hazel::Renderer2D::SetQuadCenter(Hazel::Renderer2D::QuadCenter::LeftBottom);

		m_App = std::make_unique<GameEditorApp>();

		GT::BaseGameApp::InitValues gameAppInitValues;
		gameAppInitValues.CameraType = GT::DefaultCameras::Type::FreeMove;
		m_App->InitApp(gameAppInitValues);
	}

	void GameEditor::OnDetach()
	{

	}

	void GameEditor::OnUpdate(Hazel::Timestep ts)
	{
		if (ts > 0.018f)
		{
			HZ_WARN("ts was more than 18 ms, {0}", (float)ts);
			ts = 0.018f;
		}

		// Update
		m_App->OnUpdateApp(ts);

		// Render
		m_App->OnRenderApp();
	}

	void GameEditor::OnImGuiRender()
	{
		m_App->OnImGuiRenderApp();
	}

	void GameEditor::OnEvent(Hazel::Event& e)
	{
		m_App->OnEventApp(e);
	}

}