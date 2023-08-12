#include "MouseGame/MouseGameObjects/Room.h"

#include "MouseGame/MouseGameObjects/GlobalMouseGameObjects.h"

namespace MouseGameLayer {

	void Room::InitRooms()
	{
		// Main Room
		{
			GT::SpriteSheet::InitializerForSpriteSheet mainRoomSpriteSheetData;
			mainRoomSpriteSheetData.Filepath = "assets/textures/MainRoom.png";
			mainRoomSpriteSheetData.AnimationsInfo.emplace_back("Default", 0);
			GT::LoadingSystem<GT::SpriteSheet>::AddObjectToMap(GlobalMouseGameObjects::SpriteSheetIds::MainRoom_SSI, mainRoomSpriteSheetData);

			GT::Component::ObjectRenderable::InitializerData mainRoomSpriteSheetViewData;
			mainRoomSpriteSheetViewData.SpriteSheetId = GlobalMouseGameObjects::SpriteSheetIds::MainRoom_SSI;
			mainRoomSpriteSheetViewData.DefaultAnimationName = "Default";

			GT::LoadingSystem<Room>::AddObjectToMap(RoomIds::MainRoom_RI, mainRoomSpriteSheetViewData);
			GT::LoadingSystem<Room>::LoadObjectNoRender(RoomIds::MainRoom_RI);
		}

		// Living Room
		{
			GT::SpriteSheet::InitializerForSpriteSheet livingRoomSpriteSheetData;
			livingRoomSpriteSheetData.Filepath = "assets/textures/LivingRoom.png";
			livingRoomSpriteSheetData.AnimationsInfo.emplace_back("Default", 0);
			GT::LoadingSystem<GT::SpriteSheet>::AddObjectToMap(GlobalMouseGameObjects::SpriteSheetIds::LivingRoom_SSI, livingRoomSpriteSheetData);

			GT::Component::ObjectRenderable::InitializerData livingRoomSpriteSheetViewData;
			livingRoomSpriteSheetViewData.SpriteSheetId = GlobalMouseGameObjects::SpriteSheetIds::LivingRoom_SSI;
			livingRoomSpriteSheetViewData.DefaultAnimationName = "Default";

			GT::LoadingSystem<Room>::AddObjectToMap(RoomIds::LivingRoom_RI, livingRoomSpriteSheetViewData);
			GT::LoadingSystem<Room>::LoadObjectNoRender(RoomIds::LivingRoom_RI);
		}

		// Kitchen
		{
			GT::SpriteSheet::InitializerForSpriteSheet kitchenSpriteSheetData;
			kitchenSpriteSheetData.Filepath = "assets/textures/Kitchen.png";
			kitchenSpriteSheetData.AnimationsInfo.emplace_back("Default", 0);
			GT::LoadingSystem<GT::SpriteSheet>::AddObjectToMap(GlobalMouseGameObjects::SpriteSheetIds::Kitchen_SSI, kitchenSpriteSheetData);

			GT::Component::ObjectRenderable::InitializerData kitchenSpriteSheetViewData;
			kitchenSpriteSheetViewData.SpriteSheetId = GlobalMouseGameObjects::SpriteSheetIds::Kitchen_SSI;
			kitchenSpriteSheetViewData.DefaultAnimationName = "Default";

			GT::LoadingSystem<Room>::AddObjectToMap(RoomIds::Kitchen_RI, kitchenSpriteSheetViewData);
			GT::LoadingSystem<Room>::LoadObjectNoRender(RoomIds::Kitchen_RI);
		}
	}

	void Room::Init(const GT::Component::ObjectRenderable::InitializerData& spriteSheetViewData)
	{
		Get<GT::Component::Positional>().SetPosition({ 0.0f, 0.0f });
		Get<GT::Component::ObjectRenderable>().InitRenderable(spriteSheetViewData);
	}

	void Room::OnUpdate(Hazel::Timestep ts)
	{
		for (Door& door : m_Doors)
			door.OnUpdate(ts);

		Get<GT::Component::ObjectRenderable>().OnUpdate(ts);
	}

	void Room::OnRender()
	{
		// Rooms don't have positionals but they do need to be the size of the screen
		auto& positional = Get<GT::Component::Positional>();
		positional.SetSize({ (float)GT::GlobalData::GetWindowWidth(), (float)GT::GlobalData::GetWindowHeight() });
		positional.SetDepth(-0.2f);
		Get<GT::Component::ObjectRenderable>().OnRender(positional);
	}

	void Room::Load()
	{
		for (GT::ObjectInSystem<Item> itemId : m_Items)
			GT::LoadingSystem<Item>::LoadObject(itemId);

		for (GT::ObjectInSystem<Interactable> interactableId : m_Interactables)
			GT::LoadingSystem<Interactable>::LoadObject(interactableId);
	}

	void Room::Unload()
	{
		for (GT::ObjectInSystem<Item> itemId : m_Items)
			GT::LoadingSystem<Item>::LoadObjectNoRender(itemId);

		for (GT::ObjectInSystem<Interactable> interactableId : m_Interactables)
			GT::LoadingSystem<Interactable>::LoadObjectNoRender(interactableId);
	}

}