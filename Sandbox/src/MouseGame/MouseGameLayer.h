#pragma once

#include <Hazel.h>
#include "MouseGame/MouseGameApp.h"

namespace MouseGameLayer {

	class MouseGame : public Hazel::Layer
	{
	public:
		MouseGame();
		virtual ~MouseGame() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnUpdate(Hazel::Timestep ts) override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Hazel::Event& e) override;
	private:
		std::unique_ptr<GT::BaseGameApp> m_App = nullptr;
	};

}