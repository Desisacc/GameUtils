#pragma once

#include <Hazel.h>
#include "GameEditor/GameEditorApp.h"

namespace GameEditorLayer {

	class GameEditor : public Hazel::Layer
	{
	public:
		GameEditor();
		virtual ~GameEditor() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnUpdate(Hazel::Timestep ts) override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Hazel::Event& e) override;
	private:
		std::unique_ptr<GT::BaseGameApp> m_App = nullptr;
	};

}