#include "MouseGame/MouseGameObjects/Item.h"

#include "MouseGame/MouseGameObjects/GlobalMouseGameObjects.h"
#include "MouseGame/MouseGameObjects/Inventory.h"

namespace MouseGameLayer {

	void Item::InitItems()
	{
		// Hammer
		{
			GT::SpriteSheet::InitializerForSpriteSheet hammerSpriteSheetData;
			hammerSpriteSheetData.Filepath = "assets/textures/Hammer.png";
			hammerSpriteSheetData.AnimationsInfo.emplace_back("Default", 0);
			GT::LoadingSystem<GT::SpriteSheet>::AddObjectToMap(GlobalMouseGameObjects::SpriteSheetIds::Hammer_SSI, hammerSpriteSheetData);

			//GT::Component::Positional::InitializerData hammerPositionalData;
			//hammerPositionalData.Size = { 50.0f, 50.0f };
			GT::Component::ObjectRenderable::InitializerData hammerViewData;
			hammerViewData.SpriteSheetId = GlobalMouseGameObjects::SpriteSheetIds::Hammer_SSI;
			hammerViewData.DefaultAnimationName = "Default";

			GT::Component::Positional::InitializerData hammerPositionalData;
			hammerPositionalData.Position = { 10.0f, 10.0f };
			hammerPositionalData.Size = { 50.0f, 50.0f };

			GT::LoadingSystem<Item>::AddObjectToMap(ItemIds::Hammer_II, hammerViewData, hammerPositionalData);
			GT::LoadingSystem<Item>::LoadObjectNoRender(ItemIds::Hammer_II);
		}

		// Master Key
		{
			GT::SpriteSheet::InitializerForSpriteSheet masterKeySpriteSheetData;
			masterKeySpriteSheetData.Filepath = "assets/textures/MasterKey.png";
			masterKeySpriteSheetData.AnimationsInfo.emplace_back("Default", 0);
			GT::LoadingSystem<GT::SpriteSheet>::AddObjectToMap(GlobalMouseGameObjects::SpriteSheetIds::MasterKey_SSI, masterKeySpriteSheetData);

			//GT::Component::Positional::InitializerData masterKeyPositionalData;
			//masterKeyPositionalData.Size = { 50.0f, 50.0f };
			GT::Component::ObjectRenderable::InitializerData masterKeyViewData;
			masterKeyViewData.SpriteSheetId = GlobalMouseGameObjects::SpriteSheetIds::MasterKey_SSI;
			masterKeyViewData.DefaultAnimationName = "Default";

			GT::Component::Positional::InitializerData masterKeyPositionalData;
			masterKeyPositionalData.Position = { 10.0f, 10.0f };
			masterKeyPositionalData.Size = { 0.0f, 0.0f };

			GT::LoadingSystem<Item>::AddObjectToMap(ItemIds::MasterKey_II, masterKeyViewData, masterKeyPositionalData);
			GT::LoadingSystem<Item>::LoadObjectNoRender(ItemIds::MasterKey_II);
		}
	}

	void Item::OnUpdate(Hazel::Timestep ts)
	{
		auto& positional = Get<GT::Component::Positional>();
		auto& viewData = Get<GT::Component::ObjectRenderable>();
		const size_t itemId = Get<GT::ObjectInSystemComponent>().GetObjectId();
		auto& dragableObject = Get<DragableObject>();

		dragableObject.OnUpdateDragableObject(Get<GT::Component::Positional>());

		if (m_IsInInventory)
		{
			if (!Inventory::InventoryIsOpen())
				viewData.SetIsRendered(false);
			else
				viewData.SetIsRendered(true);

			if (dragableObject.IsBeingClicked())
			{
				Inventory::RemoveItem(itemId);
				Map::GetCurrentRoom().AddItem(itemId);
				m_IsInInventory = false;
			}
		}
		else
		{
			if (!dragableObject.IsBeingClicked() && Inventory::CheckIfItemShouldBeInInventory(positional))
			{
				Inventory::AddItem(itemId);
				Map::GetCurrentRoom().RemoveItem(itemId);
				m_IsInInventory = true;
				viewData.SetIsRendered(false);
			}
		}

		Get<GT::Component::ObjectRenderable>().OnUpdate(ts);
	}

	void Item::OnRender()
	{
		Get<GT::Component::ObjectRenderable>().OnRender(Get<GT::Component::Positional>());
	}

}