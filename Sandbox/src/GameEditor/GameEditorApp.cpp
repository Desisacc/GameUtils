#include "GameEditor/GameEditorApp.h"

namespace GameEditorLayer {

	void GameEditorApp::Init() 
	{
		Map::InitObjects();

		m_Map.Init();

		//constexpr const char* filepath = "C:\\Users\\olga_\\Desktop\\CustomProjects\\Sandbox\\assets\\levels\\lol.txt";
		
		/*std::fstream mapFile(filepath, std::ios::out);
	
		const std::string globalDataStr = GT::Serializer::SerializeGlobalData();
		mapFile << globalDataStr;
		mapFile.close();

		mapFile.open(filepath, std::ios::in);
		std::vector<std::string> lines;
		while (std::getline(mapFile, lines.emplace_back()));
		GT::Deserializer::DeserializeGlobalData(lines);*/

		/*class myClass : public Component::BasicGroupedComponent<myClass, Component::Directional> {};
		GT::myClass myObject;
		myObject.InitPositional({ 10.0f, 50.0f }, { 60.0f, 62.0f }, 0.2f);
		myObject.InitDirectional({ 50.0f, 30.0f });
		const std::string seriliazed = GT::Serializer::SerializeComponents(myObject.GetPositional(), myObject.GetDirectional());
		myObject.UpdatePreviousState();
		const std::string seriliazed2 = GT::Serializer::SerializeComponents(myObject.GetPositional(), myObject.GetDirectional());
		HZ_INFO("{0}\n", seriliazed.c_str());
		HZ_INFO("{0}\n", seriliazed2.c_str());*/

		/*std::vector<std::string> lines;
		std::fstream fileText("C:\\Users\\olga_\\Desktop\\CustomProjects\\Sandbox\\assets\\levels\\lol.txt", std::ios::in);
		while (std::getline(fileText, lines.emplace_back()))
		{}

		myClass myObject;
		GT::Deserializer::DeserializeComponents<GT::Component::Positional>(lines, myObject.GetPositional());*/		
	}

	void GameEditorApp::OnUpdate(Hazel::Timestep ts)
	{
		m_CameraOnUpdateArguments.ts = ts;

		for (GT::Vector2<float> mouseClick : m_MouseClicks)
		{
			// Add camera position to the mouse click
			const GT::Vector2<float> cameraPosition = GetCameraPosition();
			mouseClick.x += cameraPosition.x;
			mouseClick.y += cameraPosition.y;

			const GT::Vector2<uint32_t> clickedTile = ConvertToTileCoordinates(mouseClick);
			m_Map.HandleTileClick(clickedTile);
		}

		m_MouseClicks.clear();
	}

	void GameEditorApp::OnRender()
	{
		m_Map.OnRender();
	}

	void GameEditorApp::OnImGuiRender()
	{
		ImGui::Begin("ImGui Window");

		m_Map.OnImGuiRender();

		ImGui::End();
	}

	void GameEditorApp::OnEvent(Hazel::Event& e)
	{
		Hazel::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<Hazel::MouseButtonPressedEvent>(HZ_BIND_EVENT_FN(GT::BaseGameApp::OnMouseClickEvent));
	}

}