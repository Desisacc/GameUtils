#pragma once

#include <GT.h>

#include "MouseGame/MouseGameObjects/Item.h"

namespace MouseGameLayer {

	class Inventory
	{
	public:
		static constexpr size_t MAX_ITEMS = 5;
	public:
		Inventory() = delete;
		static void Init();

		static void AddItem(GT::ObjectInSystem<Item> itemToAdd);
		static void RemoveItem(GT::ObjectInSystem<Item> itemToDelete);

		static void OnUpdate(Hazel::Timestep ts);
		static void OnRender();

		static bool CheckIfItemShouldBeInInventory(const GT::Component::Positional& itemPositional);

		static bool InventoryIsOpen()
		{
			return s_IsOpen;
		}
	private:
		class InventoryIcon : public ClickableObject
		{
		public:
			void Init(GT::Vector2<float> size, float depth)
			{
				auto& positional = m_Positional;
				positional.SetSize(size);
				positional.SetDepth(depth);
			}

			void OnUpdate(Hazel::Timestep ts)
			{
				auto& positional = m_Positional;

				OnUpdateClickableObject(positional);

				constexpr float PADDING = 25.0f;
				GT::Vector2<float> position = { 0.0f, 0.0f };
				position.x = (float)GT::GlobalData::GetWindowWidth() - positional.GetSize().x - PADDING;
				position.y = PADDING;
				positional.SetPosition(position);

				m_ObjectRenderable.OnUpdate(ts);
			}

			void OnRender()
			{
				m_ObjectRenderable.OnRender(m_Positional);
			}
		public:
			GT::Component::Positional m_Positional;
			GT::Component::ObjectRenderable m_ObjectRenderable;
		};
		class InventoryBackground
		{
		public:
			void OnUpdate(Hazel::Timestep ts)
			{
				GT::Component::Positional::InitializerData positionalData;

				positionalData.Position = { 0.0f, 0.0f };
				positionalData.Depth = -0.1f;

				constexpr float PADDING = 25.0f;
				constexpr float ITEM_HEIGHT = 50.0f;
				positionalData.Size = { (float)GT::GlobalData::GetWindowWidth(), ITEM_HEIGHT + PADDING * 2.0f };

				m_Positional.SetPositional(positionalData);

				m_ObjectRenderable.OnUpdate(ts);
			}

			void OnRender()
			{
				m_ObjectRenderable.OnRender(m_Positional);
			}
		public:
			GT::Component::Positional m_Positional;
			GT::Component::ObjectRenderable m_ObjectRenderable;
		};
	private:
		static std::vector<GT::ObjectInSystem<Item>> s_ItemsInInventory;
		static InventoryIcon s_InventoryIcon;
		static InventoryBackground s_InventoryBackground;
		static bool s_IsOpen;
	};

}