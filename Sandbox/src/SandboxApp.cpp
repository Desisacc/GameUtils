#include <Hazel.h>
#include <Hazel/Core/EntryPoint.h>

//#include "TestLayer/TestLayer.h"
//#include "GameEditor/GameEditorLayer.h"
#include "MouseGame/MouseGameLayer.h"

class Sandbox : public Hazel::Application
{
public:
	Sandbox()
	{
		//PushLayer(new TestLayer::Test);
		//PushLayer(new GameEditorLayer::GameEditor);
		PushLayer(new MouseGameLayer::MouseGame);
	}
	
	~Sandbox()
	{

	}
};

Hazel::Application* Hazel::CreateApplication()
{
	return new Sandbox();
}