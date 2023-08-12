#include "MouseGame/MouseGameObjects/Door.h"

#include "MouseGame/MouseGameObjects/Map.h"

namespace MouseGameLayer {

	void Door::OnUpdate(Hazel::Timestep ts)
	{
		GT::Vector2<float> size = { 0.0f, 0.0f };
		GT::Vector2<float> position = { 0.0f, 0.0f };
		switch (m_DoorPosition)
		{
		case DoorPosition::Right_DP:
			size = { 100.0f, 300.0f };
			position = { (float)GT::GlobalData::GetWindowWidth() - size.x, (float)GT::GlobalData::GetWindowHeight() / 2.0f - size.y / 2.0f };
			break;
		case DoorPosition::Left_DP:
			size = { 100.0f, 300.0f };
			position = { 0.0f, (float)GT::GlobalData::GetWindowHeight() / 2.0f - size.y / 2.0f };
			break;
		case DoorPosition::Up_DP:
			size = { 300.0f, 100.0f };
			position = { (float)GT::GlobalData::GetWindowWidth() / 2.0f - size.x / 2.0f, (float)GT::GlobalData::GetWindowHeight() - size.y };
			break;
		case DoorPosition::Down_DP:
			size = { 300.0f, 100.0f };
			position = { (float)GT::GlobalData::GetWindowWidth() / 2.0f - size.x / 2.0f, 0.0f };
			break;
		default:
			GT::Assert(false, "Unknown DoorPosition! :{0}", static_cast<uint32_t>(m_DoorPosition));
			break;
		}
		auto& positional = Get<GT::Component::Positional>();
		positional.SetRectangle(position, size);
		OnUpdateClickableObject(positional);

		if (IsBeingClicked())
		{
			Map::SetCurrentRoom(m_RoomIdDirectedTo);
			DeactivateClick();
		}
	}

}