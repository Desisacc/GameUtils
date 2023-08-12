#pragma once

#include <GT.h>

#include "MouseGame/MouseGameObjects/ToAddFeatures/ClickableObject.h"

namespace MouseGameLayer {

	class DragableObject
	{
	public:
		DragableObject() = default;

		void OnUpdateDragableObject(GT::Component::Positional& positional);
		
		bool IsBeingClicked() const
		{
			return m_IsClicked;
		}
		void DeactivateClick()
		{
			m_IsClicked = false;
		}
	public:
		bool m_IsClicked = false;
		bool m_CanBeDragged = true;
	};

}