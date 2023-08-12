#include "TestLayer/LevelSerializer.h"

#include <GT.h>

#include "TestLayer/GameObjects/GlobalObjects.h"
#include "TestLayer/GameObjects/Player.h"
#include "TestLayer/GameObjects/EndFlag.h"
#include "TestLayer/GameObjects/Platform.h"
#include "TestLayer/GameObjects/MovablePlatform.h"
#include "TestLayer/GameObjects/Projectile.h"
#include "TestLayer/GameObjects/Spike.h"
#include "TestLayer/GameObjects/JumpOrb.h"

namespace TestLayer {

	const GT::Vector2<float> LevelSerializer::TILE_SIZE = { TILE_LENGTH, TILE_LENGTH };

	/*std::vector<std::vector<char>> LevelSerializer::s_TileMap = std::vector<std::vector<char>>();

	void LevelSerializer::ValidateMap()
	{
		// The serializer can't take an empty map
		GT::Assert(!s_TileMap.empty(), "s_TileMap is empty!");
		
		// All rows from a map must have an equal number of cells (it's not necessary to check the first row)
		const std::vector<char>& firstRow = s_TileMap.front();
		std::for_each(s_TileMap.begin() + 1, s_TileMap.end(), [&firstRow](const std::vector<char>& currentRow)
		{
			GT::Assert(firstRow.size() == currentRow.size(), "Firt row has {0} tiles but one of the rows has {2} tiles", firstRow.size(), currentRow.size());
		});
	}

	void LevelSerializer::HandleTile(char tile, GT::Vector2<size_t> tilePositionInTiles)
	{
		const GT::Vector2<float> tilePosition = { tilePositionInTiles.x * TILE_LENGTH, tilePositionInTiles.y * TILE_LENGTH };

		switch (tile)
		{
		case 'P':
		{
			GlobalObjects::GetPlayer().Init(tilePosition, Player::PLAYER_SIZE);
			break;
		}
		case 'E':
		{
		GlobalObjects::GetEndFlag().Init(tilePosition, TILE_SIZE);
			break;
		}
		case 'X':
		{
			Platform& currentPlatform = GlobalObjects::GetPlatforms().emplace_back();
			currentPlatform.Init(tilePosition, TILE_SIZE);
			break;
		}
		case 'L':
		{
			MovablePlatform& currentMovablePlatform = GlobalObjects::GetMovablePlatforms().emplace_back();
			currentMovablePlatform.Init(tilePosition, TILE_SIZE, { MovablePlatform::PLATFORM_SPEED, 0.0f });
			break;
		}
		case 'K':
		{
			MovablePlatform& currentMovablePlatform = GlobalObjects::GetMovablePlatforms().emplace_back();
			currentMovablePlatform.Init(tilePosition, TILE_SIZE, { 0.0f, MovablePlatform::PLATFORM_SPEED });
			break;
		}
		case 'O':
		{
			JumpOrb& currentJumpOrb = GlobalObjects::GetJumpOrbs().emplace_back();
			currentJumpOrb.Init(tilePosition, TILE_SIZE);
			break;
		}
		case '-':
		{
			Projectile& currentProjectile = GlobalObjects::GetProjectiles().emplace_back();
			currentProjectile.Init(tilePosition, Projectile::PROJECTILE_SIZE, { Projectile::DEFAULT_SPEED, Projectile::DEFAULT_SPEED });
			break;
		}
		case 'S':
		{
			Spike& currentSpike = GlobalObjects::GetSpikes().emplace_back();
			currentSpike.Init(tilePosition, TILE_SIZE);
			break;
		}
		case '.':
		{
			break;
		}
		default:
			GT::Assert(false, "Unknown tileType in Map ('{0}')! Position: {1}, {2}", tile, tilePosition.x, tilePosition.y);
		}
	}

	void LevelSerializer::DeserializeLevel(const LevelLoader::Level& level)
	{
		s_TileMap = level.CharMap;

		// Makes sure the char map doesn't have invalid input that will throw an exception
		ValidateMap();

		// Go through each tile in map (y-axis needs to be done in reverse )
		const size_t numberOfRows = s_TileMap.size();
		const size_t numberOfColumns = s_TileMap.front().size();
		for (size_t currentRowIndex = 0; currentRowIndex < numberOfRows; currentRowIndex++)
		{
			const std::vector<char>& currentRow = s_TileMap[currentRowIndex];
			const size_t currentIndexY = numberOfRows - currentRowIndex - 1;

			for (size_t currentIndexX = 0; currentIndexX < numberOfColumns; currentIndexX++)
			{
				const char currentTile = currentRow[currentIndexX];

				HandleTile(currentTile, { currentIndexX, currentIndexY });
			}
		}

		// New map will fit the measurements of the new level
		GT::GlobalData::SetMapSize({ (uint32_t)(numberOfColumns * TILE_LENGTH), (uint32_t)(numberOfRows * TILE_LENGTH) });

		s_TileMap = std::vector<std::vector<char>>();
	}*/

	void LevelSerializer::DeserializeLevelFromFile(const std::string& filepath, LevelLoader::Level& level)
	{
		std::fstream mapFile(filepath, std::ios::in);
		std::vector<std::string> lines;
		while (std::getline(mapFile, lines.emplace_back()));

		GlobalObjects::ClearObjectsOfLevel(level);

		GT::Deserializer::DeserializeGlobalData(lines);

		GT::Component::ForEachComponentType([&lines](auto& object) 
		{ 
			const std::string objectType = GT::Serializer::GetTypeName(object) + '{';
			while (objectType == lines[0])
				GT::Deserializer::DeserializeComponents(lines, object.GetPositional()); 
		}, level.Player, level.EndFlag);

		GT::Component::ForEachComponentVector([&lines](auto& objects)
		{ 
			auto* tempObject = &objects.emplace_back();
			const std::string objectType = GT::Serializer::GetTypeName(*tempObject) + '{';
			while (objectType == lines[0])
			{
				GT::Deserializer::DeserializeComponents(lines, tempObject->GetPositional());
				tempObject = &objects.emplace_back();
			}
			objects.pop_back();

		}, level.Platforms, level.JumpOrbs);

		GT::Component::ForEachComponentVector([&lines](auto& objects)
		{ 
			auto* tempObject = &objects.emplace_back();
			const std::string objectType = GT::Serializer::GetTypeName(*tempObject) + '{';
			while (objectType == lines[0])
			{
				GT::Deserializer::DeserializeComponents(lines, tempObject->GetPositional(), tempObject->GetDirectional());
				tempObject = &objects.emplace_back();
			}
			objects.pop_back();
		}, level.MovablePlatforms, level.Spikes, level.Projectiles);
	}

}