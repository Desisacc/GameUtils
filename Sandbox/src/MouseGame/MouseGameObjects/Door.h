#pragma once

#include <GT.h>

#include "MouseGame/MouseGameObjects/ToAddFeatures/ClickableObject.h"

namespace MouseGameLayer {

	class Room;

	class Door : public ClickableObject, public GT::Component::ElementInContainer<Door, GT::Component::Positional, GT::ObjectInSystemComponent>
	{
	public:
		enum DoorPosition : uint32_t
		{
			None_DP = 0, Right_DP, Left_DP, Up_DP, Down_DP
		};
	public:
		Door(GT::ObjectInSystem<Room> roomIdDirectedTo, DoorPosition doorPosition) noexcept
			: m_RoomIdDirectedTo(roomIdDirectedTo), m_DoorPosition(doorPosition) {}

		void OnUpdate(Hazel::Timestep ts);

		DoorPosition GetDoorPosition() const
		{
			return m_DoorPosition;
		}
		void SetDoorPositon(DoorPosition doorPosition)
		{
			m_DoorPosition = doorPosition;
		}
	private:
		GT::ObjectInSystem<Room> m_RoomIdDirectedTo = GT::ObjectInSystemComponent::INVALID_ID;
		DoorPosition m_DoorPosition = None_DP;
	};

}