#include "GameEditor/EditorObjects/Map.h"

#include <fstream>
#include <imgui.h>

#include "TestLayer/GameObjects/Player.h"
#include "TestLayer/GameObjects/MovablePlatform.h"
#include "TestLayer/GameObjects/Projectile.h"

namespace GameEditorLayer {

	void Map::Init()
	{
		m_MapMeasurementsInTiles = { GT::GlobalData::GetMapWidth() / m_TileLength, GT::GlobalData::GetMapHeight() / m_TileLength };

		m_OccupiedTiles.resize(m_MapMeasurementsInTiles.x);

		for (std::vector<TileType>& column : m_OccupiedTiles)
		{
			column.resize(m_MapMeasurementsInTiles.y);

			for (TileType& tile : column)
				tile = TileType::None_TT;
		}

		GT::SpriteSheet& tileSpriteSheet = m_TileSpriteSheet.GetSpriteSheetOfObject();
		tileSpriteSheet.DefaultInit("assets/textures/SquareFrame.png");

		GT::SpriteSheetView tileSpriteSheetView = m_TileSpriteSheet.GetSpriteSheetView();
		tileSpriteSheetView.DefaultInit(&tileSpriteSheet);
	}

	void Map::InitObjects()
	{
		Player::InitPlayer();
		EndFlag::InitEndFlag();
		Platform::InitPlatforms();
		MovablePlatform::InitMovablePlatforms();
		Spike::InitSpikes();
		Projectile::InitProjectiles();
		JumpOrb::InitJumpOrbs();
	}

	void Map::HandleTileClick(GT::Vector2<uint32_t> tileClicked)
	{
		if (tileClicked.x >= m_MapMeasurementsInTiles.x || tileClicked.y >= m_MapMeasurementsInTiles.y)
			return;

		m_CurrentClickedTile = tileClicked;

		if (m_CurrentTileType == m_OccupiedTiles[tileClicked.x][tileClicked.y])
			return;

		switch (m_CurrentTileType)
		{
		case TileType::Player_TT:
			SetTile(m_Player, tileClicked);
			break;

		case TileType::EndFlag_TT:
			SetTile(m_EndFlag, tileClicked);
			break;

		case TileType::Platform_TT:
			AddTileToVector(m_Platforms, tileClicked);
			break;

		case TileType::MovablePlatform_TT:
			AddTileToVector(m_MovablePlatforms, tileClicked);
			break;

		case TileType::Spike_TT:
			AddTileToVector(m_Spikes, tileClicked);
			break;

		case TileType::Projectile_TT:
			AddTileToVector(m_Projectiles, tileClicked);
			break;

		case TileType::JumpOrb_TT:
			AddTileToVector(m_JumpOrbs, tileClicked);
			break;

		case TileType::None_TT:
			DeleteTile(tileClicked);
			break;

		default:
			GT::Assert(false, "Unknown TileType! :{0}", static_cast<uint32_t>(m_CurrentTileType));
		}

		if (m_OccupiedTiles[tileClicked.x][tileClicked.y] != TileType::None_TT)
			DeleteTile(tileClicked);

		m_OccupiedTiles[tileClicked.x][tileClicked.y] = m_CurrentTileType;
	}

	void Map::OnRender()
	{
		GT::Component::ForEachComponentType([](auto& object)
			{ object.OnRender(); },
			m_Player, m_EndFlag);

		GT::Component::ForEachComponentTypeInVector([](auto& object)
			{ object.OnRender(); },
			m_Platforms, m_MovablePlatforms, m_Spikes, m_Projectiles, m_JumpOrbs);

		for (uint32_t x = 0; x < m_MapMeasurementsInTiles.x; x++)
		{
			for (uint32_t y = 0; y < m_MapMeasurementsInTiles.y; y++)
			{
				m_TileSpriteSheet.SetPosition(ToMapCoordinates({ x, y }));
				m_TileSpriteSheet.OnRender();
			}
		}
	}

	void Map::OnMapResize()
	{
		GT::GlobalData::SetMapSize({ m_MapMeasurementsInTiles.x * m_TileLength, m_MapMeasurementsInTiles.y * m_TileLength });

		size_t tileMapWidth = m_OccupiedTiles.size();
		size_t tileMapHeight = m_OccupiedTiles.front().size();

		if (m_MapMeasurementsInTiles.x < tileMapWidth)
		{
			const size_t columsToDelete = tileMapWidth - m_MapMeasurementsInTiles.x;
			m_OccupiedTiles.erase(m_OccupiedTiles.end() - columsToDelete, m_OccupiedTiles.end());

			tileMapWidth = m_OccupiedTiles.size();
		}
		else if (m_MapMeasurementsInTiles.x > tileMapWidth)
		{
			const size_t columsToAdd = m_MapMeasurementsInTiles.x - tileMapWidth;
			for (size_t currentColumn = 0; currentColumn < columsToAdd; currentColumn++)
			{
				std::vector<TileType>& columnToFill = m_OccupiedTiles.emplace_back();
				columnToFill.resize(tileMapHeight);
				for (TileType& tile : columnToFill)
					tile = TileType::None_TT;

				tileMapWidth = m_OccupiedTiles.size();
			}
		}

		if (m_MapMeasurementsInTiles.y < tileMapHeight)
		{
			const size_t rowsToDelete = tileMapHeight - m_MapMeasurementsInTiles.y;
			for (std::vector<TileType>& column : m_OccupiedTiles)
				column.erase(column.end() - rowsToDelete, column.end());

			tileMapHeight = m_OccupiedTiles.front().size();
		}
		else if (m_MapMeasurementsInTiles.y > tileMapHeight)
		{
			const size_t rowsToAdd = m_MapMeasurementsInTiles.y - tileMapHeight;
			for (std::vector<TileType>& column : m_OccupiedTiles)
			{
				for(size_t currentRow = 0; currentRow < rowsToAdd; currentRow++)
					column.push_back(TileType::None_TT);
			}

			tileMapHeight = m_OccupiedTiles.front().size();
		}

		if (m_CurrentClickedTile.x >= tileMapWidth)
			m_CurrentClickedTile.x = 0;
		if (m_CurrentClickedTile.y >= tileMapHeight)
			m_CurrentClickedTile.y = 0;

		GT::Component::ForEachComponentType([this](GT::Component::Positional& positional) 
			{ InvalidateIfOutsideMap(positional); }, 
			m_Player, m_EndFlag);

		GT::Component::ForEachComponentVector([this](auto& objects)
		{
			for (size_t currentObjectIndex = 0; currentObjectIndex < objects.size();)
			{
				auto& object = objects[currentObjectIndex];
				if (ObjectIsOutsideMap(object))
					objects.erase(objects.begin() + currentObjectIndex);
				else
					currentObjectIndex++;
			}
		}, m_Platforms, m_MovablePlatforms, m_Spikes, m_Projectiles, m_JumpOrbs);

		/*InvalidateIfOutsideMap(m_Player);
		InvalidateIfOutsideMap(m_EndFlag);

		DeleteTilesFromVectorIfOutsideMap(m_Platforms);
		DeleteTilesFromVectorIfOutsideMap(m_MovablePlatforms);
		DeleteTilesFromVectorIfOutsideMap(m_Spikes);
		DeleteTilesFromVectorIfOutsideMap(m_Projectiles);
		DeleteTilesFromVectorIfOutsideMap(m_JumpOrbs);*/
	}

#define EXPAND(x) x
#define CREATE_BUTTON(x) if (ImGui::Button(#x, { 100, 30 })) { SetCurrentTileType(Map::TileType::EXPAND(x)_TT); }

	void Map::OnImGuiRender()
	{
		const bool mapWidthHasChanged = ImGui::SliderInt("Map Width", (int*)&m_MapMeasurementsInTiles.x, 1, MAX_MAP_MEASUREMENT);
		const bool mapHeightHasChanged = ImGui::SliderInt("Map Height", (int*)&m_MapMeasurementsInTiles.y, 1, MAX_MAP_MEASUREMENT);

		if (mapWidthHasChanged || mapHeightHasChanged)
			OnMapResize();

		switch (m_OccupiedTiles[m_CurrentClickedTile.x][m_CurrentClickedTile.y])
		{
		case TileType::None_TT:
		case TileType::EndFlag_TT:
		case TileType::Platform_TT:
			break;
		case TileType::Player_TT:
			GT::Serializer::ImGuiInfo(m_Player.GetPositional(), Player::PLAYER_SIZE_RANGE);
			break;

		case TileType::MovablePlatform_TT:
			for (MovablePlatform& movablePlatform : m_MovablePlatforms)
			{
				if (movablePlatform.GetPosition() == ToMapCoordinates(m_CurrentClickedTile))
					GT::Serializer::ImGuiInfo(movablePlatform.GetDirectional(), MovablePlatform::PLATFORM_SPEED_RANGE);
			}
			break;

		case TileType::Spike_TT:
			for (Spike& spike : m_Spikes)
			{
				if (spike.GetPosition() == ToMapCoordinates(m_CurrentClickedTile))
					GT::Serializer::ImGuiInfo(spike.GetDirectional(), Spike::SPIKE_SPEED_RANGE);
			}
			break;

		case TileType::Projectile_TT:
			for (Projectile& projectile : m_Projectiles)
			{
				if (projectile.GetPosition() == ToMapCoordinates(m_CurrentClickedTile))
				{
					GT::Serializer::ImGuiInfo(projectile.GetPositional(), Projectile::PROJECTILE_SIZE_RANGE);
					GT::Serializer::ImGuiInfo(projectile.GetDirectional(), Projectile::PROJECTILE_SPEED_RANGE);
				}
			}
			break;

		case TileType::JumpOrb_TT:
			for (JumpOrb& jumpOrb : m_JumpOrbs)
			{
				if (jumpOrb.GetPosition() == ToMapCoordinates(m_CurrentClickedTile))
					GT::Serializer::ImGuiInfo(jumpOrb.GetPositional(), JumpOrb::JUMP_ORB_SIZE_RANGE);
			}
			break;

		default:
			GT::Assert(false, "Unknown TileType! :{0}", static_cast<uint32_t>(m_OccupiedTiles[m_CurrentClickedTile.x][m_CurrentClickedTile.y]));
		}

		CREATE_BUTTON(None);
		CREATE_BUTTON(Player);
		CREATE_BUTTON(EndFlag);
		CREATE_BUTTON(Platform);
		CREATE_BUTTON(MovablePlatform);
		CREATE_BUTTON(Spike);
		CREATE_BUTTON(Projectile);
		CREATE_BUTTON(JumpOrb);

		ImGui::InputText("Level Name", m_LevelName, sizeof(m_LevelName));

		if (ImGui::Button("Serialize Level", { 100, 30 }))
			SerializeMap(m_LevelName);
	}

	void Map::SerializeMap(const std::string& levelName)
	{
		std::fstream mapFile;
		GT::OpenFile(mapFile, __FILE__, "Sandbox", "assets\\levels\\", levelName + ".txt", GT::OpenFileMode::Output_OPM);
		/*const std::string currentFilepath = __FILE__;
		const std::string projectName = "Sandbox";
		const size_t indexToProjectName = currentFilepath.find(projectName);
		const std::string levelFolderFilepath = "\\assets\\levels\\";
		
		const std::string filepath = 
			currentFilepath.substr(0, indexToProjectName + projectName.length()) + 
			levelFolderFilepath + levelName + ".txt";

		std::fstream mapFile;
		mapFile.open(filepath, std::ios::out);
		if (!mapFile.is_open())
			GT::Assert(false, "mapFile could not be opened!");*/

		mapFile << GT::Serializer::SerializeGlobalData();

		GT::Component::ForEachComponentType([&mapFile](const auto& object) 
			{ mapFile << GT::Serializer::GetTypeName(object) << GT::Serializer::SerializeComponents(object.GetPositional()); },
			m_Player, m_EndFlag);

		GT::Component::ForEachComponentTypeInVector([&mapFile](const auto& object) 
			{ mapFile << GT::Serializer::GetTypeName(object) << GT::Serializer::SerializeComponents(object.GetPositional()); },
			m_Platforms, m_JumpOrbs);

		GT::Component::ForEachComponentTypeInVector([&mapFile](const auto& object)
			{ mapFile << GT::Serializer::GetTypeName(object) << GT::Serializer::SerializeComponents(object.GetPositional(), object.GetDirectional()); },
			m_MovablePlatforms, m_Spikes, m_Projectiles);
	}

}