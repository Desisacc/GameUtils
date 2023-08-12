#pragma once

#include <vector>
#include <unordered_map>
#include <string>

#include "TestLayer/GameObjects/Player.h"
#include "TestLayer/GameObjects/EndFlag.h"
#include "TestLayer/GameObjects/Platform.h"
#include "TestLayer/GameObjects/MovablePlatform.h"
#include "TestLayer/GameObjects/Projectile.h"
#include "TestLayer/GameObjects/Spike.h"
#include "TestLayer/GameObjects/JumpOrb.h"

namespace TestLayer {

	class LevelLoader
	{
	public:
		struct Level
		{
			std::vector<Platform> Platforms;
			std::vector<MovablePlatform> MovablePlatforms;
			std::vector<JumpOrb> JumpOrbs;
			std::vector<Projectile> Projectiles;
			std::vector<Spike> Spikes;
			Player Player;
			EndFlag EndFlag;

			Level() = default;
		};
	public:
		LevelLoader() = delete;
		static void InitLevels();

		// Returns a value to indicate if all levels have been completed
		static bool LoadLevelFromFile(uint32_t levelNumber);
		// Returns a value to indicate if all levels have been completed
		static bool LoadNextLevelFromFile();
		
		static void ResetCurrentLevel();
	private:
		static std::unordered_map<uint32_t, std::string> m_Levels;
		static uint32_t m_CurrentLevelNumber;
		static Level m_CurrentLevel;
	};

	/*struct Level
		{
			std::vector<std::vector<char>> CharMap;

			Level() = default;
			void Init(const std::vector<std::vector<char>>& charMap) { CharMap = charMap; }
		};*/
	/*
	static std::unordered_map<uint32_t, Level> m_Levels;
	static bool LoadLevel(uint32_t levelNumber);
	static bool LoadNextLevel();
	std::unordered_map<uint32_t, LevelLoader::Level> LevelLoader::m_Levels = {};
	*/

}