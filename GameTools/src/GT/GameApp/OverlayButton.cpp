#include "gtpch.h"
#include "GT/GameApp/OverlayButton.h"

#include "GT/Collider.h"

namespace GT {

	void OverlayButton::Init(GT::Vector2<float> position, GT::Vector2<float> size, float depth, const SpriteSheet::InitializerForSpriteSheet& spriteSheetData, std::function<void()> onAction)
	{
		Get<Component::Positional>().SetPositional({ position, size, depth });
		//Get<Component::ObjectRenderable>().InitRenderable(spriteSheetData);
		m_OnAction = onAction;
	}

	void OverlayButton::OnUpdate(Hazel::Timestep ts)
	{
		Get<Component::ObjectRenderable>().OnUpdate(ts);
	}

	void OverlayButton::OnRender()
	{
		Get<Component::ObjectRenderable>().OnRender(Get<Component::Positional>());
	}

	void OverlayButton::HandleMouseClicks(const std::vector<GT::Vector2<float>>& mouseClicks)
	{
		// const& to avoid warning although it's not necessary
		for (const GT::Vector2<float>& mouseClick : mouseClicks)
		{
			const Component::Positional mouseClickPositional({ mouseClick, { 1.0f, 1.0f }, 0.0f });

			const bool clickIntersectsWithButton = GT::Collider::RectanglesHaveIntersection(mouseClickPositional.GetRectangle(), Get<Component::Positional>().GetRectangle());
			if (clickIntersectsWithButton)
				m_OnAction();
		}
	}

}