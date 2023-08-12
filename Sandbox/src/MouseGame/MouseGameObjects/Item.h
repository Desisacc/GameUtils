#pragma once

#include <GT.h>

#include "MouseGame/MouseGameObjects/ToAddFeatures/DragableObject.h"

namespace MouseGameLayer {

	class Item : public GT::Component::ElementInContainer<Item, GT::Component::Positional, GT::Component::ObjectRenderable, GT::ObjectInSystemComponent, DragableObject>
	{
	public:
		static constexpr size_t INVALID_ITEM_ID = std::numeric_limits<size_t>::max();

		enum ItemIds : size_t
		{
			Hammer_II = 1, MasterKey_II = 2
		};
	public:
		static void InitItems();

		void OnUpdate(Hazel::Timestep ts);
		void OnRender();

		bool IsInInventory() const
		{
			return m_IsInInventory;
		}
	private:
		bool m_IsInInventory = false;
	};

}