#pragma once

#include "GT/ObjectSystems/ObjectSystem.h"

namespace GT {

	template<>
	class LoadingSystem<GT::SpriteSheet>
	{
	public:
		LoadingSystem() = delete;

		static void AddObjectToMap(size_t id, const GT::SpriteSheet::InitializerForSpriteSheet& spriteSheetData)
		{
			GT::SpriteSheet::InitializerForSpriteSheet& spriteSheetInfo = m_AllSpriteSheets[id];
			spriteSheetInfo = spriteSheetData;
		}

		static void LoadObject(size_t id)
		{
			LoadObject(id, [](GT::SpriteSheet& object) {});
		}
		template<typename Func> static void LoadObject(size_t id, Func intializerFunction)
		{
			auto spriteSheetInfoIt = m_AllSpriteSheets.find(id);
			GT::Assert(spriteSheetInfoIt != m_AllSpriteSheets.end(), "SpriteSheet with id: {0} does not exist!", id);
			const GT::SpriteSheet::InitializerForSpriteSheet& spriteSheetInfo = spriteSheetInfoIt->second;

			for (GT::SpriteSheet& spriteSheet : m_LoadedSpriteSheets)
			{
				if (spriteSheet.Get<ObjectInSystemComponent>().GetObjectId() == id)
					return;
			}

			/*if (!m_LoadedSpriteSheets.empty())
			{
				auto& a = m_LoadedSpriteSheets.front().GetTypeComponent<SpriteSheet>(Component::HelperStruct<ObjectInSystemComponent>());
				HZ_INFO("");
			}*/

			GT::SpriteSheet& spriteSheet = m_LoadedSpriteSheets.emplace_back();
			spriteSheet.Get<ObjectInSystemComponent>().InitObjectId(id);

			spriteSheet.Init(spriteSheetInfo);

			intializerFunction(spriteSheet);
		}

		static void UnloadObject(size_t id)
		{
			// Find spriteSheet
			GT::SpriteSheet* spriteSheetToUnload = nullptr;
			size_t spriteSheetIndex = 0;
			for (spriteSheetIndex; spriteSheetIndex < m_LoadedSpriteSheets.size(); spriteSheetIndex++)
			{
				GT::SpriteSheet& spriteSheet = m_LoadedSpriteSheets[spriteSheetIndex];

				if (spriteSheet.Get<ObjectInSystemComponent>().GetObjectId() == id)
				{
					spriteSheetToUnload = &spriteSheet;
					break;
				}
			}
			GT::Assert(spriteSheetToUnload, "Object with id: {0} could not be founded!", id);

			m_LoadedSpriteSheets.erase(m_LoadedSpriteSheets.begin() + spriteSheetIndex);
		}
		static void UnloadObjects()
		{
			m_LoadedSpriteSheets.clear();
		}

		static SpriteSheet::InitializerForSpriteSheet& GetUnloadedObject(size_t id)
		{
			auto spriteSheetIt = m_AllSpriteSheets.find(id);
			GT::Assert(spriteSheetIt != m_AllSpriteSheets.end(), "Object with id: {0} does not exist!", id);
			return spriteSheetIt->second;
		}
		static GT::SpriteSheet& GetLoadedObject(size_t id)
		{
			GT::SpriteSheet* objectToGet = nullptr;
			size_t spriteSheetIndex = 0;
			for (spriteSheetIndex; spriteSheetIndex < m_LoadedSpriteSheets.size(); spriteSheetIndex++)
			{
				GT::SpriteSheet& object = m_LoadedSpriteSheets[spriteSheetIndex];

				if (object.Get<ObjectInSystemComponent>().GetObjectId() == id)
					objectToGet = &object;
			}
			GT::Assert(objectToGet, "Object with id: {0} could not be founded!", id);

			return *objectToGet;
		}

		/*static void UpdateLoadedObjects(Hazel::Timestep ts)
		{
			for (GT::SpriteSheet& spriteSheet : m_LoadedSpriteSheets)
				spriteSheet.OnUpdate(ts);
		}
		static void OnRenderLoadedObjects()
		{
			for (Object& object : m_LoadedObject)
				object.OnRender();
		}*/
	private:
		static std::unordered_map<size_t, GT::SpriteSheet::InitializerForSpriteSheet> m_AllSpriteSheets;
		static std::vector<GT::SpriteSheet> m_LoadedSpriteSheets;
	};

}