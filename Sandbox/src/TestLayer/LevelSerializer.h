#pragma once

#include "TestLayer/LevelLoader.h"

namespace TestLayer {

	class LevelSerializer
	{
	public:
		static constexpr float TILE_LENGTH = 60.0f;
		static const GT::Vector2<float> TILE_SIZE;
	public:
		LevelSerializer() = delete;

		static void DeserializeLevelFromFile(const std::string& filepath, LevelLoader::Level& level);
	};

	/*
	static void DeserializeLevel(const LevelLoader::Level& level);
	private:
		static void ValidateMap();
		static void HandleTile(char tile, GT::Vector2<size_t> tilePositionInTiles);
	private:
		static std::vector<std::vector<char>> s_TileMap;
	*/

}