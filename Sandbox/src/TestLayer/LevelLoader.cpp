#include "TestLayer/LevelLoader.h"

#include "TestLayer/GameObjects/GlobalObjects.h"
#include "TestLayer/LevelSerializer.h"

namespace TestLayer {

	std::unordered_map<uint32_t, std::string> LevelLoader::m_Levels = {};
	uint32_t LevelLoader::m_CurrentLevelNumber = 0;
	LevelLoader::Level LevelLoader::m_CurrentLevel = LevelLoader::Level();

	void LevelLoader::InitLevels()
	{
		/*Level& levelOne = m_Levels[1];
		const std::vector<std::vector<char>> levelOneMap =
		{
			{ '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'X', 'X', '.', 'X' },
			{ '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'E', 'X' },
			{ 'X', 'L', '.', 'X', '.', '.', '.', '.', 'K', '.', '.', '.', '.', 'X', 'X', 'X' },
			{ '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', 'X', '.', '.', '.' },
			{ '.', '.', '.', '.', 'X', '.', '.', '.', 'X', '.', 'X', 'X', '.', '.', '.', '.' },
			{ '.', '.', '.', '.', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.' },
			{ '.', '.', '.', '.', '.', '.', '.', '.', 'X', 'X', '.', '.', '.', '.', '.', '.' },
			{ 'P', '.', '.', '.', 'X', 'L', 'O', '.', 'X', 'X', 'X', '.', '.', '.', '.', '.' },
			{ 'X', 'X', 'X', 'X', 'X', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.' }
		};
		levelOne.Init(levelOneMap);

		Level& levelTwo = m_Levels[2];
		const std::vector<std::vector<char>> levelTwoMap =
		{
			{ '.', '.', '.', 'X', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', '.' },
			{ '.', '.', 'E', 'X', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', '.' },
			{ '.', 'X', 'X', '.', '.', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', '.' },
			{ '.', 'X', 'X', '.', 'X', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', '.' },
			{ '.', '.', 'X', '.', 'X', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', '.' },
			{ 'X', '.', 'X', '.', 'X', '.', '.', 'X', '.', '.', '.', '.', '.', '.', '.', '.' },
			{ '.', '.', 'X', '.', 'X', '.', '.', '.', '.', 'X', '.', '.', 'X', '.', '.', '.' },
			{ '.', '.', '.', '.', 'X', '.', '.', '.', 'X', '.', '.', '.', '.', 'X', '.', 'P' },
			{ 'X', 'X', 'X', 'X', 'X', 'X', '.', '.', 'S', 'S', 'S', 'S', 'S', 'S', 'X', 'X' }
		};
		levelTwo.Init(levelTwoMap);*/

		std::string& levelOneFilepath = m_Levels[1];
		levelOneFilepath = "assets\\levels\\one.txt";
		
		std::string& levelTwoFilepath = m_Levels[2];
		levelTwoFilepath = "assets\\levels\\two.txt";
	}

	bool LevelLoader::LoadLevelFromFile(uint32_t levelNumber)
	{
		auto levelIt = m_Levels.find(levelNumber);
		if (levelIt == m_Levels.end())
		{
			HZ_WARN("Level {0} could not be found!", levelNumber);
			return true;
		}

		m_CurrentLevelNumber = levelNumber;
		const std::string& levelFilepath = levelIt->second;

		LevelSerializer::DeserializeLevelFromFile(levelFilepath, m_CurrentLevel);
		GlobalObjects::LoadObjectsFromLevel(m_CurrentLevel);
		return false;
	}

	bool LevelLoader::LoadNextLevelFromFile()
	{
		const bool hasCompletedGame = LoadLevelFromFile(m_CurrentLevelNumber + 1);
		return hasCompletedGame;
	}

	void LevelLoader::ResetCurrentLevel()
	{
		GlobalObjects::LoadObjectsFromLevel(m_CurrentLevel);
	}

	/*bool LevelLoader::LoadLevel(uint32_t levelNumber)
	{
		GlobalObjects::ClearObjects();

		auto levelIt = m_Levels.find(levelNumber);
		if (levelIt == m_Levels.end())
		{
			HZ_WARN("Level {0} could not be found!", levelNumber);
			return true;
		}

		m_CurrentLevel = levelNumber;
		const Level& level = levelIt->second;

		LevelSerializer::DeserializeLevel(level);
		return false;
	}*/
	/*bool LevelLoader::LoadNextLevel()
	{
		GlobalObjects::GetPlayer().ResetCompletedLevelState();

		const bool hasCompletedGame = LoadLevel(m_CurrentLevel + 1);
		return hasCompletedGame;
	}*/

}