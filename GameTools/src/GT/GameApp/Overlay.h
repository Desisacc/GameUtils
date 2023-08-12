#pragma once

#include <Hazel.h>

#include "GT/Utils/GlobalData.h"
#include "GT/GameApp/OverlayButton.h"
#include "GT/Input/MouseInput.h"

namespace GT {

	class Overlay
	{
	public:
		Overlay() = default;
		void Init(const GT::Vector4<float>& backgroundColor);
		void Init(const std::string& filepath, const GT::Vector4<float>& backgroundColor);
		void Init(const Hazel::Ref<Hazel::Texture2D>& backgroundTexture, const GT::Vector4<float>& backgroundColor);

		void OnUpdate(Hazel::Timestep ts);
		void OnRender();
		void OnEvent(Hazel::Event& e);

		OverlayButton& AddButton() 
		{ 
			return m_Buttons.emplace_back(); 
		}

		bool StopsGame() const { return m_BackgroundTexture || m_BackgroundColor.a; }
		bool CoversScreen() const { return m_BackgroundTexture || m_BackgroundColor.a == 1.0f; }
	private:
		bool OnMouseClickEvent(Hazel::MouseButtonPressedEvent& e)
		{
			if (e.GetMouseButton() == Hazel::Mouse::ButtonLeft)
				m_MouseClicks.push_back(Input::GetMousePosition());

			return false;
		}
	private:
		std::vector<OverlayButton> m_Buttons;
		Hazel::Ref<Hazel::Texture2D> m_BackgroundTexture = nullptr;
		GT::Vector4<float> m_BackgroundColor = { 0.0f, 0.0f, 0.0f, 0.0f };

		std::vector<GT::Vector2<float>> m_MouseClicks;
	};

}