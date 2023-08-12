#include "MouseGame/MouseGameObjects/ToAddFeatures/ClickableObject.h"

namespace MouseGameLayer {

	void ClickableObject::OnUpdateClickableObject(const GT::Component::Positional& positional)
	{
		// Set clicked when a click gathered from an event intersects with positional
		if (!m_IsClicked)
		{
			for (GT::Vector2<float> mouseClick : GT::GlobalData::GetMouseClicks())
			{
				const GT::Rectangle mouseRect = { mouseClick, GT::Vector2<float>{ 1.0f, 1.0f } };
				if (GT::Collider::RectanglesHaveIntersection(mouseRect, positional.GetRectangle()))
					m_IsClicked = true;
			}
		}
		// Set not clicked when the left click stops being pressed
		else if (bool isStillClicked = GT::Input::IsMouseButtonPressed(GT::Input::MouseButton::Left_MB); !isStillClicked || (isStillClicked && m_IsClicked))
		{
			m_IsClicked = false;
		}
	}

}