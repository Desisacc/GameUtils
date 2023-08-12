#include "MouseGame/MouseGameObjects/ToAddFeatures/Button.h"

namespace MouseGameLayer {

	/*void Button::Init(GT::Vector2<float> position, GT::Vector2<float> size, float depth, const GT::SpriteSheet::InitializerForSpriteSheet& spriteSheetData, std::function<void()> onClick)
	{
		Get<GT::Component::Positional>().SetPositional({ position, size, depth });
		Get<GT::Component::ObjectRenderable>().InitRenderable(spriteSheetData);
		m_OnClick = onClick;
	}

	void Button::OnUpdate(Hazel::Timestep ts, std::vector<GT::Vector2<float>>& clicks)
	{
		auto& positional = Get<GT::Component::Positional>();

		for (size_t currentClickIndex = 0; currentClickIndex < clicks.size(); currentClickIndex++)
		{
			GT::Vector2<float> click = clicks[currentClickIndex];

			if (GT::Input::IsBeingClicked(positional.GetRectangle()))
			{
				m_OnClick();
				clicks.erase(clicks.begin() + currentClickIndex);
			}
		}

		Get<GT::Component::ObjectRenderable>().OnUpdate(ts);
	}

	void Button::OnRender()
	{
		Get<GT::Component::ObjectRenderable>().OnRender(Get<GT::Component::Positional>());
	}*/

}