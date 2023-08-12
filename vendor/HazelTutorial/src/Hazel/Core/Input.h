#pragma once

#include <utility>

#include <glm/glm.hpp>

#include "Hazel/Core/KeyCodes.h"
#include "Hazel/Core/MouseCodes.h"

namespace Hazel {

	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode keycode);

		static bool IsMouseButtonPressed(MouseCode button);
		static glm::vec2 GetMousePosition();
		// From right to left
		static float GetMouseX();
		// From top to bottom
		static float GetMouseY();
	};

}