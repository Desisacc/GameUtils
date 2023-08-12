#pragma once

#include <Hazel.h>

#include "GT/Components/Components.h"

namespace GT {

	class OverlayButton : public Component::ElementInContainer<OverlayButton, Component::Positional, Component::ObjectRenderable>
	{
	public:
		OverlayButton() = default;
		void Init(GT::Vector2<float> position, GT::Vector2<float> size, float depth, const SpriteSheet::InitializerForSpriteSheet& spriteSheetData, std::function<void()> onAction);

		void OnUpdate(Hazel::Timestep ts);
		void OnRender();

		void HandleMouseClicks(const std::vector<GT::Vector2<float>>& mouseClicks);
	private:
		std::function<void()> m_OnAction = nullptr;
	};

}