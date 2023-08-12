#include "gtpch.h"
#include "GT/GameApp/Overlay.h"

namespace GT {

	void Overlay::Init(const GT::Vector4<float>& backgroundColor)
	{
		Init(Hazel::Ref<Hazel::Texture2D>(nullptr), backgroundColor);
	}
	void Overlay::Init(const std::string& filepath, const GT::Vector4<float>& backgroundColor)
	{
		Init(Hazel::Texture2D::Create(filepath), backgroundColor);
	}
	void Overlay::Init(const Hazel::Ref<Hazel::Texture2D>& backgroundTexture, const GT::Vector4<float>& backgroundColor)
	{
		m_BackgroundTexture = backgroundTexture;
		m_BackgroundColor = backgroundColor;
	}

	void Overlay::OnUpdate(Hazel::Timestep ts)
	{
		for (OverlayButton& button : m_Buttons)
		{
			button.OnUpdate(ts);
			button.HandleMouseClicks(m_MouseClicks);
		}

		m_MouseClicks.clear();
	}

	void Overlay::OnRender()
	{
		for (OverlayButton& button : m_Buttons)
			button.OnRender();

		if (m_BackgroundColor.a != 0.0f)
			Hazel::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { GlobalData::GetWindowWidth(), GlobalData::GetWindowHeight() }, { m_BackgroundColor.r, m_BackgroundColor.g, m_BackgroundColor.b, m_BackgroundColor.a });

		if (m_BackgroundTexture)
			Hazel::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { GlobalData::GetWindowWidth(), GlobalData::GetWindowHeight() }, m_BackgroundTexture);
	}

	void Overlay::OnEvent(Hazel::Event& e)
	{
		Hazel::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<Hazel::MouseButtonPressedEvent>(HZ_BIND_EVENT_FN(Overlay::OnMouseClickEvent));
	}

}