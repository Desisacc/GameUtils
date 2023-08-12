#include "MouseGame/MouseGameObjects/Inventory.h"

#include "MouseGame/MouseGameObjects/GlobalMouseGameObjects.h"

namespace MouseGameLayer {

	std::vector<GT::ObjectInSystem<Item>> Inventory::s_ItemsInInventory = {};
	Inventory::InventoryIcon Inventory::s_InventoryIcon;
	Inventory::InventoryBackground Inventory::s_InventoryBackground;
	bool Inventory::s_IsOpen = false;

	void Inventory::Init()
	{
		{
			GT::SpriteSheet::InitializerForSpriteSheet inventoryIconSpriteSheetData;
			inventoryIconSpriteSheetData.Filepath = "assets/textures/Backpack.png";
			inventoryIconSpriteSheetData.AnimationsInfo.emplace_back("Default", 0);
			GT::LoadingSystem<GT::SpriteSheet>::AddObjectToMap(GlobalMouseGameObjects::SpriteSheetIds::InventoryIcon_SSI, inventoryIconSpriteSheetData);
			GT::LoadingSystem<GT::SpriteSheet>::LoadObject(GlobalMouseGameObjects::SpriteSheetIds::InventoryIcon_SSI);

			GT::Component::ObjectRenderable::InitializerData inventoryIconViewData;
			inventoryIconViewData.SpriteSheetId = GlobalMouseGameObjects::SpriteSheetIds::InventoryIcon_SSI;
			inventoryIconViewData.DefaultAnimationName = "Default";
			s_InventoryIcon.m_ObjectRenderable.InitRenderable(inventoryIconViewData);

			s_InventoryIcon.Init({ 50.0f, 50.0f }, 0.1f);
		}

		{
			GT::SpriteSheet::InitializerForSpriteSheet inventoryBackgroundSpriteSheetData;
			inventoryBackgroundSpriteSheetData.Filepath = "assets/textures/InventoryBackground.png";
			inventoryBackgroundSpriteSheetData.AnimationsInfo.emplace_back("Default", 0);
			GT::LoadingSystem<GT::SpriteSheet>::AddObjectToMap(GlobalMouseGameObjects::SpriteSheetIds::InventoryBackground_SSI, inventoryBackgroundSpriteSheetData);
			GT::LoadingSystem<GT::SpriteSheet>::LoadObject(GlobalMouseGameObjects::SpriteSheetIds::InventoryBackground_SSI);

			GT::Component::ObjectRenderable::InitializerData inventoryBackgroundViewData;
			inventoryBackgroundViewData.SpriteSheetId = GlobalMouseGameObjects::SpriteSheetIds::InventoryBackground_SSI;
			inventoryBackgroundViewData.DefaultAnimationName = "Default";
			s_InventoryBackground.m_ObjectRenderable.InitRenderable(inventoryBackgroundViewData);
		}
	}

	void Inventory::AddItem(GT::ObjectInSystem<Item> itemToAdd)
	{
		for (GT::ObjectInSystem<Item> item : s_ItemsInInventory)
		{
			if (item == itemToAdd)
				return;
		}

		s_ItemsInInventory.push_back(itemToAdd);
	}

	void Inventory::RemoveItem(GT::ObjectInSystem<Item> itemIdToDelete)
	{
		size_t indexOfItem = std::numeric_limits<size_t>::max();
		for (size_t itemIndex = 0; itemIndex < s_ItemsInInventory.size(); itemIndex++)
		{
			GT::ObjectInSystem<Item>& itemId = s_ItemsInInventory[itemIndex];

			if (itemId == itemIdToDelete)
			{
				indexOfItem = itemIndex;
				break;
			}
		}
		GT::Assert(indexOfItem != std::numeric_limits<size_t>::max(), "Item {0} could not be found!", itemIdToDelete.GetObjectId());

		Map::GetCurrentRoom().AddItem(itemIdToDelete);
		/*Item& item = GT::LoadingSystem<Item>::GetLoadedObject(itemIdToDelete);
		item.Get<GT::Component::ObjectRenderable>().SetIsRendered(true);*/

		s_ItemsInInventory.erase(s_ItemsInInventory.begin() + indexOfItem);
	}

	void Inventory::OnUpdate(Hazel::Timestep ts)
	{
		s_InventoryIcon.OnUpdate(ts);
		
		if (s_InventoryIcon.IsBeingClicked())
			s_IsOpen = !s_IsOpen;

		if (!s_IsOpen)
			return;

		s_InventoryBackground.OnUpdate(ts);

		constexpr float PADDING = 30.0f;
		for (size_t itemIndex = 0; itemIndex < s_ItemsInInventory.size(); itemIndex++)
		{
			GT::Assert(s_ItemsInInventory.size() < MAX_ITEMS, "There are {0} items in inventory when the max is {1}", s_ItemsInInventory.size(), MAX_ITEMS);

			GT::ObjectInSystem<Item>& itemId = s_ItemsInInventory[itemIndex];
			Item& item = GT::LoadingSystem<Item>::GetLoadedObject(itemId);
			auto& itemPositional = item.Get<GT::Component::Positional>();
			auto& itemViewData = item.Get<GT::Component::ObjectRenderable>();

			itemPositional.SetPosition({ itemPositional.GetSize().x * itemIndex + PADDING, PADDING });
			itemViewData.SetIsRendered(true);
		}

		/*std::vector<Item>& loadedItems = GT::LoadingSystem<Item>::GetLoadedObjects();
		for (Item& loadedItem : loadedItems)
		{
			for (GT::ObjectInSystem<Item> inventoryItem : s_ItemsInInventory)
			{
				if (loadedItem.Get<GT::ObjectInSystemComponent>().GetObjectId() == inventoryItem.GetObjectId())
				{

				}
			}
		}*/
	}

	void Inventory::OnRender()
	{
		s_InventoryIcon.OnRender();

		if (!s_IsOpen)
			return;

		s_InventoryBackground.OnRender();
	}

	bool Inventory::CheckIfItemShouldBeInInventory(const GT::Component::Positional& itemPositional)
	{
		const auto& itemRectangle = itemPositional.GetRectangle();
		const auto& inventoryIconRectangle = s_InventoryIcon.m_Positional.GetRectangle();
		return GT::Collider::RectanglesHaveIntersection(itemRectangle, inventoryIconRectangle);
	}

}