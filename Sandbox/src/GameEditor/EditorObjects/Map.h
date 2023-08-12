#pragma once

#include <GT.h>

#include "GameEditor/EditorObjects/SerializedGameObjects.h"

namespace GameEditorLayer {

	/*
	Player:
	Position, size

	EndFlag:
	Position, Size

	Platforms:
	Position, size

	MovablePlatforms:
	Position, size, speed

	Spikes:
	Position, size

	Projectiles:
	Position, size, speed

	JumpOrbs:
	Position, size
	*/

	class Map
	{
	public:
		enum TileType : uint32_t
		{
			None_TT = 0, Player_TT, EndFlag_TT, Platform_TT, MovablePlatform_TT, 
			Spike_TT, JumpOrb_TT, Projectile_TT
		};

		static constexpr uint32_t DEFAULT_TILE_LENGTH = 60;
		static constexpr uint32_t MAX_MAP_MEASUREMENT = 960 * 3 / DEFAULT_TILE_LENGTH;
	public:
		Map() = default;
		void Init();
		static void InitObjects();

		void OnRender();

		void OnImGuiRender();
		void SerializeMap(const std::string& levelName);

		void HandleTileClick(GT::Vector2<uint32_t> tileClicked);
		void SetCurrentTileType(TileType tileType) 
		{ 
			m_CurrentTileType = tileType; 
		}
		GT::Vector2<float> ToMapCoordinates(GT::Vector2<uint32_t> position) const
		{
			return { static_cast<float>(position.x * m_TileLength), static_cast<float>(position.y * m_TileLength) };
		}
		GT::Vector2<uint32_t> ToTileCoordinates(GT::Vector2<float> position) const 
		{
			return { static_cast<uint32_t>(position.x / m_TileLength), static_cast<uint32_t>(position.y / m_TileLength) };
		}
		GT::Vector2<float> GetTileSize() const
		{
			return ToMapCoordinates({ 1, 1 });
		}
	private:
		void SetTile(GT::Component::Positional& object, GT::Vector2<uint32_t> tileClicked)
		{
			const GT::Vector2<uint32_t> previousTilePosition = ToTileCoordinates(object.GetPosition());
			m_OccupiedTiles[previousTilePosition.x][previousTilePosition.y] = TileType::None_TT;
			object.InitPositional(ToMapCoordinates(tileClicked), GetTileSize());
		}
		void InvalidateTile(GT::Component::Positional& object)
		{
			object.InitPositional({ -1.0f, -1.0f }, { 0.0f, 0.0f });
		}
		void InvalidateIfOutsideMap(GT::Component::Positional& object)
		{
			if (ObjectIsOutsideMap(object))
				InvalidateTile(object);
		}

		template<typename PositionalType> void AddTileToVector(std::vector<PositionalType>& objects, GT::Vector2<uint32_t> clickedTile)
		{
			GT::Component::Positional& object = objects.emplace_back();
			object.InitPositional(ToMapCoordinates(clickedTile), GetTileSize());
		}
		template<typename PositionalType> void DeleteTileFromVector(std::vector<PositionalType>& objects, GT::Vector2<uint32_t> clickedTile)
		{
			for (size_t currentObjectIndex = 0; currentObjectIndex < objects.size(); currentObjectIndex++)
			{
				const GT::Component::Positional& currentObject = objects[currentObjectIndex];

				if (currentObject.GetPosition() == ToMapCoordinates(clickedTile))
				{
					objects.erase(objects.begin() + currentObjectIndex);
					return;
				}
			}
		}

		void DeleteTile(GT::Vector2<uint32_t> tileClicked)
		{
			const TileType clickedTileType = m_OccupiedTiles[tileClicked.x][tileClicked.y];

			switch (clickedTileType)
			{
			case TileType::Player_TT:
				InvalidateTile(m_Player);
				break;

			case TileType::EndFlag_TT:
				InvalidateTile(m_EndFlag);
				break;

			case TileType::Platform_TT:
				DeleteTileFromVector(m_Platforms, tileClicked);
				break;

			case TileType::MovablePlatform_TT:
				DeleteTileFromVector(m_MovablePlatforms, tileClicked);
				break;

			case TileType::Spike_TT:
				DeleteTileFromVector(m_Spikes, tileClicked);
				break;

			case TileType::Projectile_TT:
				DeleteTileFromVector(m_Projectiles, tileClicked);
				break;

			case TileType::JumpOrb_TT:
				DeleteTileFromVector(m_JumpOrbs, tileClicked);
				break;

			case TileType::None_TT:
				break;

			default:
				GT::Assert(false, "Unknown TileType! :{0}", static_cast<uint32_t>(m_CurrentTileType));
			}
		}
		bool ObjectIsOutsideMap(GT::Component::Positional& object) const
		{  
			const GT::Vector2<float> mapSize = { (float)GT::GlobalData::GetMapWidth(), (float)GT::GlobalData::GetMapHeight() };
			const GT::Vector2<float> objectPosition = object.GetPosition();

			return objectPosition.x >= mapSize.x || objectPosition.y >= mapSize.y;
		}

		void OnMapResize();
	private:
		uint32_t m_TileLength = DEFAULT_TILE_LENGTH;
		GT::Vector2<uint32_t> m_MapMeasurementsInTiles = { 0, 0 };

		TileType m_CurrentTileType = TileType::Platform_TT;
		GT::Vector2<uint32_t> m_CurrentClickedTile = { 0, 0 };

		std::vector<std::vector<TileType>> m_OccupiedTiles;
		Player m_Player;
		EndFlag m_EndFlag;
		std::vector<Platform> m_Platforms;
		std::vector<MovablePlatform> m_MovablePlatforms;
		std::vector<Spike> m_Spikes;
		std::vector<Projectile> m_Projectiles;
		std::vector<JumpOrb> m_JumpOrbs;

		GT::Component::Renderable m_TileSpriteSheet;
		char m_LevelName[25] = {};
	};

}