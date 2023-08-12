#include "MouseGame/MouseGameObjects/Map.h"

#include "MouseGame/MouseGameObjects/GlobalMouseGameObjects.h"
#include "MouseGame/MouseGameObjects/Item.h"
#include "MouseGame/MouseGameObjects/Door.h"
#include "MouseGame/MouseGameObjects/Interactable.h"
#include "MouseGame/MouseGameObjects/Inventory.h"

namespace MouseGameLayer {

	GT::ObjectInSystem<Room> Map::s_CurrentRoom = GT::ObjectInSystemComponent::INVALID_ID;

	void Map::InitMap()
	{
		Item::InitItems();
		Interactable::InitInteractables();
		Room::InitRooms();

		// Main Room
		{
			Room& mainRoom = GT::LoadingSystem<Room>::GetLoadedObject(Room::RoomIds::MainRoom_RI);

			mainRoom.AddDoor(Room::RoomIds::LivingRoom_RI, Door::DoorPosition::Right_DP);
			mainRoom.AddDoor(Room::RoomIds::Kitchen_RI, Door::DoorPosition::Left_DP);
			//mainRoom.AddDoor("Upstairs");
			//mainRoom.AddDoor("Exit");

			SetCurrentRoom(Room::RoomIds::MainRoom_RI);
		}

		// Living Room
		{
			Room& livingRoom = GT::LoadingSystem<Room>::GetLoadedObject(Room::RoomIds::LivingRoom_RI);

			livingRoom.AddDoor(Room::RoomIds::MainRoom_RI, Door::DoorPosition::Left_DP);

			livingRoom.AddItem(Item::ItemIds::MasterKey_II);
			/*Interactable& buttonOne = livingRoom.AddInteractable();
			GT::Component::Positional::InitializerData buttonOnePositional;
			buttonOnePositional.Position = { 100.0f, 100.0f };
			buttonOnePositional.Size = { 50.0f, 50.0f };
			GT::SpriteSheet::InitializerForSpriteSheet buttonOneSpriteSheetData;
			buttonOneSpriteSheetData.Filepath = "assets/textures/ButtonOne.png";
			buttonOneSpriteSheetData.AnimationsInfo.emplace_back("Default", 0);
			buttonOne.Init(buttonOnePositional, buttonOneSpriteSheetData, []()
			{
				GlobalMouseGameObjects::ButtonOneHasBeenPressed = true;
			});*/
		}

		// Kitchen
		{
			Room& kitchen = GT::LoadingSystem<Room>::GetLoadedObject(Room::RoomIds::Kitchen_RI);

			kitchen.AddDoor(Room::RoomIds::MainRoom_RI, Door::DoorPosition::Right_DP);

			kitchen.AddItem(Item::ItemIds::Hammer_II);

			kitchen.AddInteractable(Interactable::InteractableIds::ButtonOne);

			/*Item& hammer = kitchen.AddItem(ItemIds::Hammer);
			GT::Component::Positional::InitializerData hammerPositional;
			hammerPositional.Position = { 0.0f, 0.0f };
			hammerPositional.Size = { 50.0f, 50.0f };
			GT::SpriteSheet::InitializerForSpriteSheet hammerSpriteSheetData;
			hammerSpriteSheetData.Filepath = "assets/textures/Hammer.png";
			hammerSpriteSheetData.AnimationsInfo.emplace_back("Default", 0);
			hammer.Init(hammerPositional, hammerSpriteSheetData);*/
		}
	}

	void Map::UpdateMap(Hazel::Timestep ts)
	{
		GT::LoadingSystem<Room>::UpdateLoadedObjects(ts);
		GT::LoadingSystem<Item>::UpdateLoadedObjects(ts);
		GT::LoadingSystem<Interactable>::UpdateLoadedObjects(ts);
	}

	void Map::RenderMap()
	{
		GT::LoadingSystem<Room>::RenderLoadedObjects();
		GT::LoadingSystem<Item>::RenderLoadedObjects();
		GT::LoadingSystem<Interactable>::RenderLoadedObjects();
	}

	void Map::SetCurrentRoom(GT::ObjectInSystem<Room> roomId)
	{
		if (s_CurrentRoom != GT::ObjectInSystemComponent::INVALID_ID)
			GT::LoadingSystem<Room>::LoadObjectNoRender(s_CurrentRoom, [](Room& room) { room.Unload(); });
	
		GT::LoadingSystem<Room>::LoadObject(roomId, [roomId](Room& room) { room.Load(); });
		s_CurrentRoom = roomId;
	}

	Room& Map::GetCurrentRoom()
	{
		return GT::LoadingSystem<Room>::GetLoadedObject(s_CurrentRoom);
	}

}