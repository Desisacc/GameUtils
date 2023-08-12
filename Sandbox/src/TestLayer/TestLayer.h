#pragma once

#include <memory>

#include <Hazel.h>

#include "TestLayer/TestApp.h"

namespace TestLayer {

	class Test : public Hazel::Layer
	{
	public:
		Test();
		virtual ~Test() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnUpdate(Hazel::Timestep ts) override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Hazel::Event& event) override;
	private:
		//bool OnMouseButtonPressed(Hazel::MouseButtonPressedEvent& e);
		//bool OnMouseButtonReleased(Hazel::MouseButtonReleasedEvent& e);
	private:
		std::unique_ptr<GT::BaseGameApp> m_App = nullptr;
	};
}