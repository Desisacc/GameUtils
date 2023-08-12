#pragma once

#include <Hazel.h>
#include "GT/Utils/Vectors.h"

namespace GT {

	namespace Input {

		class InputKey
		{
		public:
			enum PressType : uint32_t
			{
				Press = 1, Repeat = 2
			};
			static constexpr uint32_t DEFAULT_PRESS_TYPE = PressType::Press | PressType::Repeat;
		public:
			InputKey(Hazel::KeyCode keyCode) noexcept;

			// Calls Hazel::Input::IsKeyPressed
			void GatherInput();

			// Press type can be "pressed", "repeated" or "pressed & repeated", by default it takes both
			bool IsKeyPressed(uint32_t pressType = DEFAULT_PRESS_TYPE);
		private:
			Hazel::KeyCode m_KeyCode;
			bool m_WasClicked = false;
			bool m_WasClickedLastTurn = false;
		};

	}

}