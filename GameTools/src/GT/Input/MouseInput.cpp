#include "gtpch.h"
#include "GT/Input/MouseInput.h"

#include <Hazel.h>

#include "GT/Utils/GlobalData.h"
#include "GT/Collider.h"

namespace GT {

	namespace Input {

		Vector2<float> GetMousePosition()
		{
			Vector2<float> mousePosition = { Hazel::Input::GetMouseX(), (float)GlobalData::GetWindowHeight() - Hazel::Input::GetMouseY() - 1 };

			// Set mins and max for the mouse position
			mousePosition.x = std::max(0.0f, mousePosition.x);
			mousePosition.x = std::min(mousePosition.x, (float)GlobalData::GetWindowWidth());
			mousePosition.y = std::max(0.0f, mousePosition.y);
			mousePosition.y = std::min(mousePosition.y, (float)GlobalData::GetWindowHeight());

			return mousePosition;
		}

		bool IsMouseButtonPressed(MouseButton mouseButton)
		{
			switch (mouseButton)
			{
			case MouseButton::Left_MB:
				return Hazel::Input::IsMouseButtonPressed(Hazel::Mouse::ButtonLeft);

			case MouseButton::Right_MB:
				return Hazel::Input::IsMouseButtonPressed(Hazel::Mouse::ButtonRight);

			case MouseButton::Middle_MB:
				return Hazel::Input::IsMouseButtonPressed(Hazel::Mouse::ButtonMiddle);
			}

			GT::Assert(false, "Unknown MouseButton! :{0}", static_cast<uint32_t>(mouseButton));
			return false;
		}

		bool IsBeingClicked(const Rectangle& objectRect, MouseButton mouseButton)
		{
			const Vector2<float> mousePosition = GetMousePosition();
			const Rectangle mouseRect = { { mousePosition }, { 1.0f, 1.0f } };

			const bool mouseIsOverObject = Collider::RectanglesHaveIntersection(objectRect, mouseRect);
			const bool buttonIsClicked = IsMouseButtonPressed(mouseButton);

			return mouseIsOverObject && buttonIsClicked;
		}

	}

}