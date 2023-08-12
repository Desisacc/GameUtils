#pragma once

#include <GT.h>

#include "MouseGame/MouseGameObjects/Item.h"

namespace MouseGameLayer {

	struct ItemInfo
	{
		GT::Component::Positional::InitializerData PositionalData;
		GT::SpriteSheet::InitializerForSpriteSheet SpriteSheetData;
	};

	class ItemSystem
	{
	public:
		ItemSystem() = delete;

		static void AddItemToMap(size_t id, const GT::Component::Positional::InitializerData& positionalData, const GT::SpriteSheet::InitializerForSpriteSheet& spriteSheetData)
		{
			ItemInfo& itemInfo = m_AllItems[id];
			itemInfo.PositionalData = positionalData;
			itemInfo.SpriteSheetData = spriteSheetData;
		}

		static void LoadItem(size_t id)
		{
			auto itemInfoIt = m_AllItems.find(id);
			GT::Assert(itemInfoIt != m_AllItems.end(), "Item with id: {0} does not exist!", id);
			const ItemInfo& itemInfo = itemInfoIt->second;

			Item& item = m_LoadedItems.emplace_back(id);
			item.Init(itemInfo.PositionalData, itemInfo.SpriteSheetData);
		}

		static void UnloadItems()
		{
			for (Item& item : m_LoadedItems)
			{
				auto& itemPositional = item.Get<GT::Component::Positional>();

				ItemInfo& itemInfo = m_AllItems[item.GetItemId()];
				itemInfo.PositionalData.Position = itemPositional.GetPosition();
				itemInfo.PositionalData.Size = itemPositional.GetSize();
				itemInfo.PositionalData.Depth = itemPositional.GetDepth();
			}

			m_LoadedItems.clear();
		}

		static void UpdateLoadedItems(Hazel::Timestep ts)
		{
			for (Item& item : m_LoadedItems)
				item.OnUpdate(ts);
		}
		static void OnRenderLoadedItems()
		{
			for (Item& item : m_LoadedItems)
				item.OnRender();
		}
	private:
		static std::unordered_map<size_t, ItemInfo> m_AllItems;
		static std::vector<Item> m_LoadedItems;
	};

	class Asset : public ObjectInSystem, public GT::Component::ElementInContainer<GT::Component::Positional, GT::Component::ObjectRenderable>
	{
	public:
		enum AssetIds : size_t
		{
			None = 0, One, Two, Three
		};
		void SetAssetValue(int value)
		{
			m_AssetValue = value;
		}

	private:
		int m_AssetValue = 0;
	};

	inline void Test()
	{
		GT::Component::Positional::InitializerData onePositionalData;
		onePositionalData.Position = { 10.0f, 10.0f };
		onePositionalData.Size = { 20.0f, 20.0f };
		GT::SpriteSheet::InitializerForSpriteSheet oneSpriteSheetData;
		LoadingSystem<Asset>::AddObjectToMap(Asset::AssetIds::One, onePositionalData, oneSpriteSheetData);

		int someValue = 40;
		LoadingSystem<Asset>::LoadObject(Asset::AssetIds::One, [someValue](Asset& asset)
		{
			asset.SetAssetValue(someValue);
		});

		LoadingSystem<Asset>::LoadObject(Asset::AssetIds::Two);
	}

}