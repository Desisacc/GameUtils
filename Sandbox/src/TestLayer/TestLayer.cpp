#include "TestLayer/TestLayer.h"

namespace TestLayer {

	Test::Test()
		: Layer("TestLayer") {}

	void Test::OnAttach()
	{
		HZ_PROFILE_FUNCTION();

		Hazel::Renderer2D::SetQuadCenter(Hazel::Renderer2D::QuadCenter::LeftBottom);

		m_App = std::make_unique<TestApp>();

		GT::BaseGameApp::InitValues gameAppInitValues;
		gameAppInitValues.MapWidth = gameAppInitValues.MapWidth * 2;
		gameAppInitValues.CameraType = GT::DefaultCameras::Type::FocusedOnObject;
		m_App->InitApp(gameAppInitValues);
	}

	void Test::OnDetach()
	{
		HZ_PROFILE_FUNCTION();
	}

	void Test::OnUpdate(Hazel::Timestep ts)
	{
		HZ_PROFILE_FUNCTION();
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

	void Test::OnImGuiRender()
	{
		HZ_PROFILE_FUNCTION();

		m_App->OnImGuiRenderApp();
	}

	void Test::OnEvent(Hazel::Event& e)
	{
		HZ_PROFILE_FUNCTION();

		m_App->OnEventApp(e);

		//Hazel::EventDispatcher dispatcher(e);
		//dispatcher.Dispatch<Hazel::MouseButtonPressedEvent>(HZ_BIND_EVENT_FN(TestLayer::OnMouseButtonPressed));
		//dispatcher.Dispatch<Hazel::MouseButtonReleasedEvent>(HZ_BIND_EVENT_FN(TestLayer::OnMouseButtonReleased));
	}

}

//bool TestLayer::OnMouseButtonPressed(Hazel::MouseButtonPressedEvent& e)
//{
//	// Get Current Tile
//	const glm::vec3& cameraPosition = s_CameraController.m_Camera.GetPosition();
//	const glm::vec2 invertedMousePosition = { Hazel::Input::GetMouseX() + cameraPosition.x, Global::GetScreenHeight() - Hazel::Input::GetMouseY() - 1 + cameraPosition.y };
//	const glm::u32vec2 currentTile = { (uint32_t)(invertedMousePosition.x / Global::GetTileWidth()), (uint32_t)(invertedMousePosition.y / Global::GetTileHeight()) };
//
//	s_Map.AddCarbonToMap(currentTile);
//
//	m_LastClickedTile = currentTile;
//
//	return false;
//}
//
//bool TestLayer::OnMouseButtonReleased(Hazel::MouseButtonReleasedEvent& e)
//{
//	// Get Current Tile
//	const glm::vec3& cameraPosition = s_CameraController.m_Camera.GetPosition();
//	const glm::vec2 invertedMousePosition = { Hazel::Input::GetMouseX() + cameraPosition.x, Global::GetScreenHeight() - Hazel::Input::GetMouseY() - 1 + cameraPosition.y };
//	const glm::u32vec2 currentTile = { (uint32_t)(invertedMousePosition.x / Global::GetTileWidth()), (uint32_t)(invertedMousePosition.y / Global::GetTileHeight()) };
//
//	s_Map.AddCarbonLinkWithCurrentSaturation(m_LastClickedTile, currentTile);
//
//	return false;
//}