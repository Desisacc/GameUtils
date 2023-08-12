#pragma once

#include <GT.h>

#include "GameEditor/EditorObjects/Map.h"

namespace GameEditorLayer {

	class GameEditorApp : public GT::BaseGameApp
	{
	public:
		virtual void Init() override;
		virtual void OnUpdate(Hazel::Timestep ts) override;
		virtual void OnRender() override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Hazel::Event& e) override;
	private:
		GT::Vector2<uint32_t> ConvertToTileCoordinates(GT::Vector2<float> mouseClick)
		{
			return { static_cast<uint32_t>(mouseClick.x / m_Map.GetTileSize().x), static_cast<uint32_t>(mouseClick.y / m_Map.GetTileSize().y) };
		}
	private:
		Map m_Map;
	};

}