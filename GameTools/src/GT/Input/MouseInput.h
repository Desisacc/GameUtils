#pragma once

#include "GT/Utils/Vectors.h"
#include "GT/Utils/Geometry.h"

namespace GT {

	namespace Input {

		// Gets position relative to the window position
		Vector2<float> GetMousePosition();

		enum MouseButton : uint32_t
		{
			Left_MB = 1, Right_MB = 2, Middle_MB = 4
		};
		bool IsMouseButtonPressed(MouseButton mouseButton);

		bool IsBeingClicked(const Rectangle& objectRect, MouseButton mouseButton = MouseButton::Left_MB);

	}

}