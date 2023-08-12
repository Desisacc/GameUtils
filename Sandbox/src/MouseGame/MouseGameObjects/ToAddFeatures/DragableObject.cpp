#include "MouseGame/MouseGameObjects/ToAddFeatures/DragableObject.h"

namespace MouseGameLayer {

	void DragableObject::OnUpdateDragableObject(GT::Component::Positional& positional)
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
		else if (bool isStillClicked = GT::Input::IsMouseButtonPressed(GT::Input::MouseButton::Left_MB); !isStillClicked)
		{
			m_IsClicked = false;
		}

		if (m_IsClicked)
		{
			positional.SetHorizontally(GT::Input::GetMousePosition().x - positional.GetSize().x / 2.0f);
			positional.SetVertically(GT::Input::GetMousePosition().y - positional.GetSize().y / 2.0f);
		}
	}

}