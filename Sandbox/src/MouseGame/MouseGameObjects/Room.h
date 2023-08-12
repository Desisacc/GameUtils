#pragma once

#include <GT.h>

#include "MouseGame/MouseGameObjects/Item.h"
#include "MouseGame/MouseGameObjects/Interactable.h"
#include "MouseGame/MouseGameObjects/Door.h"

namespace MouseGameLayer {

	class Room : public GT::Component::ElementInContainer<Room, GT::Component::Positional, GT::Component::ObjectRenderable, GT::ObjectInSystemComponent>
	{
	public:
		enum RoomIds : size_t
		{
			MainRoom_RI = 1, LivingRoom_RI, Kitchen_RI
		};
	public:
		Room() = default;
		static void InitRooms();
		void Init(const GT::Component::ObjectRenderable::InitializerData& spriteSheetViewData);

		void AddItem(GT::ObjectInSystem<Item> item)
		{
			m_Items.push_back(item);
		}
		void RemoveItem(GT::ObjectInSystem<Item> item)
		{
			size_t itemIndex = 0;
			for (itemIndex; itemIndex < m_Items.size(); itemIndex++)
			{
				GT::ObjectInSystem<Item>& currentItem = m_Items[itemIndex];
				if (currentItem.GetObjectId() == item.GetObjectId())
					break;
			}
			GT::Assert(itemIndex != m_Items.size(), "Item with id {0} doesn't exist!", item.GetObjectId());

			m_Items.erase(m_Items.begin() + itemIndex);
		}
		void AddInteractable(GT::ObjectInSystem<Interactable> interactable)
		{
			m_Interactables.push_back(interactable);
		}
		void AddDoor(GT::ObjectInSystem<Room> roomIdDirectedTo, Door::DoorPosition doorPosition)
		{
			m_Doors.emplace_back(roomIdDirectedTo, doorPosition);
		}

		void OnUpdate(Hazel::Timestep ts);
		void OnRender();

		void Load();
		void Unload();
	private:
		std::vector<GT::ObjectInSystem<Item>> m_Items;
		std::vector<GT::ObjectInSystem<Interactable>> m_Interactables;
		std::vector<Door> m_Doors;
	};

}