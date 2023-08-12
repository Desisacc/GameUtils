#include "gtpch.h"
#include "GT/Input/InputKey.h"

namespace GT {

	namespace Input {

		InputKey::InputKey(Hazel::KeyCode keyCode) noexcept
			: m_KeyCode(keyCode) {}

		void InputKey::GatherInput()
		{
			m_WasClickedLastTurn = m_WasClicked;
			m_WasClicked = Hazel::Input::IsKeyPressed(m_KeyCode);
		}

		bool InputKey::IsKeyPressed(uint32_t pressType)
		{
			const bool wasPressed = Hazel::Input::IsKeyPressed(m_KeyCode) && !m_WasClickedLastTurn;
			const bool wasRepeated = Hazel::Input::IsKeyPressed(m_KeyCode) && m_WasClickedLastTurn;

			bool result = false;
			if (pressType & PressType::Press)
				result |= wasPressed;
			if (pressType & PressType::Repeat)
				result |= wasRepeated;

			return result;
		}

	}

}