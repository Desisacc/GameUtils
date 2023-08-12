#pragma once

#include <GT.h>

namespace MouseGameLayer {

	class ClickableObject
	{
	public:
		ClickableObject() = default;

		void OnUpdateClickableObject(const GT::Component::Positional& positional);

		bool IsBeingClicked() const
		{
			return m_IsClicked;
		}
		void DeactivateClick()
		{
			m_IsClicked = false;
		}
	private:
		bool m_IsClicked = false;
	};

}