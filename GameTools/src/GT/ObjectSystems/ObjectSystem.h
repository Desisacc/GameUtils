#pragma once

#include "GT/Components/Components.h"

namespace GT {

	struct UnititializedObjectInfo
	{
		Component::ObjectRenderable::InitializerData SpriteSheetViewData;
		Component::Positional::InitializerData PositionalData;
	};

	template<typename Object>
	class LoadingSystem
	{
	public:
		LoadingSystem() = delete;

		static void AddObjectToMap(size_t id, const Component::ObjectRenderable::InitializerData& spriteSheetViewData, const Component::Positional::InitializerData& positionalData = Component::Positional::InitializerData())
		{
			UnititializedObjectInfo& unititializedObjectInfo = m_ObjectRenderables[id];
			unititializedObjectInfo.SpriteSheetViewData = spriteSheetViewData;
			unititializedObjectInfo.PositionalData = positionalData;
		}

		static void LoadObjectNoRender(size_t id)
		{
			LoadObjectNoRender(id, [](Object& object) {});
		}
		template<typename Func> static void LoadObjectNoRender(size_t id, Func intializerFunction)
		{
			for (Object& object : m_LoadedObjects)
			{
				if (object.Get<ObjectInSystemComponent>().GetObjectId() == id)
				{
					Component::ObjectRenderable& objectRenderable = object.Get<Component::ObjectRenderable>();
					if (objectRenderable.IsRendered())
					{
						LoadingSystem<SpriteSheet>::UnloadObject(objectRenderable.GetSpriteSheetId());
						objectRenderable.SetIsRendered(false);
					}

					intializerFunction(object);
					return;
				}
			}

			Object& object = m_LoadedObjects.emplace_back();
			object.Get<ObjectInSystemComponent>().InitObjectId(id);

			object.Get<Component::ObjectRenderable>().SetIsRendered(false);

			intializerFunction(object);
		}

		static void LoadObject(size_t id)
		{
			LoadObject(id, [](Object& object) {});
		}
		template<typename Func> static void LoadObject(size_t id, Func intializerFunction)
		{
			for (Object& object : m_LoadedObjects)
			{
				ObjectInSystemComponent& objectId = object.Get<ObjectInSystemComponent>();
				UnititializedObjectInfo& unititializedObjectInfo = GetUnloadedObject(objectId.GetObjectId());

				if (objectId.GetObjectId() == id)
				{
					Component::ObjectRenderable& objectRenderable = object.Get<Component::ObjectRenderable>();
					if (!objectRenderable.IsRendered())
					{
						Component::ObjectRenderable::InitializerData& spriteSheetViewData = unititializedObjectInfo.SpriteSheetViewData;
						LoadingSystem<GT::SpriteSheet>::LoadObject(spriteSheetViewData.SpriteSheetId);
						objectRenderable.InitRenderable(spriteSheetViewData);
						objectRenderable.SetIsRendered(true);
					}

					Component::Positional::InitializerData& positionalData = unititializedObjectInfo.PositionalData;
					Component::Positional& objectPositional = object.Get<Component::Positional>();
					objectPositional.SetPositional(positionalData);

					intializerFunction(object);
					return;
				}
			}

			Object& object = m_LoadedObjects.emplace_back();
			ObjectInSystemComponent& objectId = object.Get<ObjectInSystemComponent>();
			objectId.InitObjectId(id);

			UnititializedObjectInfo& unititializedObjectInfo = GetUnloadedObject(objectId.GetObjectId());

			Component::ObjectRenderable::InitializerData& spriteSheetViewData = unititializedObjectInfo.SpriteSheetViewData;
			LoadingSystem<GT::SpriteSheet>::LoadObject(spriteSheetViewData.SpriteSheetId);
			Component::ObjectRenderable& objectSpriteSheetView = object.Get<GT::Component::ObjectRenderable>();
			objectSpriteSheetView.InitRenderable(spriteSheetViewData);
			objectSpriteSheetView.SetIsRendered(true);

			Component::Positional::InitializerData& positionalData = unititializedObjectInfo.PositionalData;
			Component::Positional& objectPositional = object.Get<Component::Positional>();
			objectPositional.SetPositional(positionalData);

			intializerFunction(object);
		}

		static void UnloadObject(size_t id)
		{
			Object* objectToUnload = nullptr;
			size_t objectIndex = 0;
			for (objectIndex; objectIndex < m_LoadedObjects.size(); objectIndex++)
			{
				Object& object = m_LoadedObjects[objectIndex];

				if (object.Get<ObjectInSystemComponent>().GetObjectId() == id)
				{
					objectToUnload = &object;
					break;
				}
			}
			GT::Assert(objectToUnload, "Object with id: {0} could not be founded!", id);

			/*if (updateObjectInfo)
			{
				auto& objectPositional = objectToUnload->Get<GT::Component::Positional>();
				UnloadedObjectInfo& objectInfo = m_ObjectRenderables[objectToUnload->Get<ObjectInSystemComponent>().GetObjectId()];

				objectInfo.PositionalData.Position = objectPositional.GetPosition();
				objectInfo.PositionalData.Size = objectPositional.GetSize();
				objectInfo.PositionalData.Depth = objectPositional.GetDepth();
			}*/

			m_LoadedObjects.erase(m_LoadedObjects.begin() + objectIndex);
		}
		static void UnloadObjects()
		{
			/*if (updateObjectInfo)
			{
				for (Object& object : m_LoadedObjects)
				{
					auto& objectPositional = object.Get<GT::Component::Positional>();
					UnloadedObjectInfo& objectInfo = m_ObjectRenderables[object.Get<ObjectInSystemComponent>().GetObjectId()];

					objectInfo.PositionalData.Position = objectPositional.GetPosition();
					objectInfo.PositionalData.Size = objectPositional.GetSize();
					objectInfo.PositionalData.Depth = objectPositional.GetDepth();
				}
			}*/

			m_LoadedObjects.clear();
		}

		static UnititializedObjectInfo& GetUnloadedObject(size_t id)
		{
			auto objectIt = m_ObjectRenderables.find(id);
			GT::Assert(objectIt != m_ObjectRenderables.end(), "Object with id: {0} does not exist!", id);
			return objectIt->second;
		}
		static Object& GetLoadedObject(size_t id)
		{
			Object* objectToGet = nullptr;
			size_t objectIndex = 0;
			for (objectIndex; objectIndex < m_LoadedObjects.size(); objectIndex++)
			{
				Object& object = m_LoadedObjects[objectIndex];

				if (object.Get<ObjectInSystemComponent>().GetObjectId() == id)
					objectToGet = &object;
			}
			GT::Assert(objectToGet, "Object with id: {0} could not be founded!", id);

			return *objectToGet;
		}
		static std::vector<Object>& GetLoadedObjects()
		{
			return m_LoadedObjects;
		}

		static void UpdateLoadedObjects(Hazel::Timestep ts)
		{
			for (Object& object : m_LoadedObjects)
			{
				if (object.Get<Component::ObjectRenderable>().IsRendered())
					object.OnUpdate(ts);
			}
		}
		static void RenderLoadedObjects()
		{
			for (Object& object : m_LoadedObjects)
			{
				if (object.Get<Component::ObjectRenderable>().IsRendered())
					object.OnRender();
			}
		}
private:
		static std::unordered_map<size_t, UnititializedObjectInfo> m_ObjectRenderables;
		static std::vector<Object> m_LoadedObjects;
	};
	template<typename Object> std::unordered_map<size_t, UnititializedObjectInfo> LoadingSystem<Object>::m_ObjectRenderables = {};
	template<typename Object> std::vector<Object> LoadingSystem<Object>::m_LoadedObjects = {};
}