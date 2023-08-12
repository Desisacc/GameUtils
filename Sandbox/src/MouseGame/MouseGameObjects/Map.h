#pragma once

#include <GT.h>

#include "MouseGame/MouseGameObjects/Room.h"

namespace MouseGameLayer {

	class Map
	{
	public:
		Map() = delete;
		static void InitMap();

		static void UpdateMap(Hazel::Timestep ts);
		static void RenderMap();

		static void SetCurrentRoom(GT::ObjectInSystem<Room> roomId);
		static Room& GetCurrentRoom();
		/*Room* GetCurrentRoom() 
		{ 
			return m_CurrentRoom; 
		}*/
	private:
		//std::unordered_map<std::string, Room> m_Rooms;
		static GT::ObjectInSystem<Room> s_CurrentRoom;
	};

}