#pragma once

#include "GT/Utils/Vectors.h"

namespace GT {

	class GlobalData
	{
	public:
		GlobalData() = delete;

		static uint32_t GetWindowWidth() { IsValidValue(WindowWidth, "GetWindowWidth"); return WindowWidth; }
		static void SetWindowWidth(uint32_t windowWidth) { IsValidValue(windowWidth, "SetWindowWidth"); WindowWidth = windowWidth; }

		static uint32_t GetWindowHeight() { IsValidValue(WindowHeight, "GetWindowHeight"); return WindowHeight; }
		static void SetWindowHeight(uint32_t windowHeight) { IsValidValue(windowHeight, "SetWindowHeight"); WindowHeight = windowHeight; };

		static Vector2<uint32_t> GetWindowSize() { return { GetWindowWidth(), GetWindowHeight() }; }
		static void SetWindowSize(Vector2<uint32_t> windowSize) { SetWindowWidth(windowSize.x); SetWindowHeight(windowSize.y); }

		static uint32_t GetMapWidth() { IsValidValue(MapWidth, "GetMapWidth"); return MapWidth; }
		static void SetMapWidth(uint32_t mapWidth) { IsValidValue(mapWidth, "SetMapWidth"); MapWidth = mapWidth; }

		static uint32_t GetMapHeight() { IsValidValue(MapHeight, "GetMapHeight"); return MapHeight; }
		static void SetMapHeight(uint32_t mapHeight) { IsValidValue(mapHeight, "SetMapHeight"); MapHeight = mapHeight; };

		static Vector2<uint32_t> GetMapSize() { return { GetMapWidth(), GetMapHeight() }; }
		static void SetMapSize(Vector2<uint32_t> mapSize) { SetMapWidth(mapSize.x); SetMapHeight(mapSize.y); }

		static void AddMouseClick(Vector2<float> mouseClick)
		{
			MouseClicks.push_back(mouseClick);
		}
		static const std::vector<Vector2<float>>& GetMouseClicks()
		{
			return MouseClicks;
		}
		static void ClearMouseClicks()
		{
			MouseClicks.clear();
		}
	private:
		static void IsValidValue(uint32_t value, const char* caller = "") { Assert(value, caller, value); }
	private:
		static uint32_t WindowWidth;
		static uint32_t WindowHeight;

		static uint32_t MapWidth;
		static uint32_t MapHeight;

		static std::vector<Vector2<float>> MouseClicks;
	};

}