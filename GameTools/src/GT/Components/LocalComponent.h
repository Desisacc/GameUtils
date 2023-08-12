#pragma once

#include <vector>

#include "GT/Utils/Assert.h"
#include "GT/Components/ComponentBasics.h"

namespace GT {

	namespace Component {

		/*

		template<typename NameOfTheClass, typename T>
		class LocalComponentVector
		{
		protected:
			static void AddComponent()
			{
				s_Components.emplace_back();
			}

			static void DeleteComponent(IdInComponentSystem<NameOfTheClass>& componentIdToErase)
			{
				s_Components.erase(s_Components.begin() + componentIdToErase);
			}

			static void CopyComponent(IdInComponentSystem<NameOfTheClass>& componentId, const IdInComponentSystem<NameOfTheClass>& componentIdToCopy)
			{
				Assert(componentId.IsInitialized(), "ComponentId {0} is not initialized!", static_cast<size_t>(componentId));

				s_Components[componentId] = s_Components[componentIdToCopy];
			}

			static T& GetComponent(IdInComponentSystem<NameOfTheClass>& componentId)
			{
				return s_Components[componentId];
			}
		private:
			static std::vector<T> s_Components;
		};
		template<typename NameOfTheClass, typename T> std::vector<T> LocalComponentVector<NameOfTheClass, T>::s_Components;

		template<typename NameOfTheClass, typename ... Classes>
		class GroupedLocalComponentVector
		{
		public:
			template<typename T>
			T& Get()
			{
				return m_HelperInitializer.GetImpl<T>();
			}
		protected:
			template<typename T>
			void CopyComponents(const T& other)
			{
				m_HelperInitializer = other.m_HelperInitializer;
			}

			template<typename T>
			void MoveComponents(T&& other)
			{
				m_HelperInitializer = std::move(other.m_HelperInitializer);
			}
		private:
			class HelperInitializer : public LocalComponentVector<NameOfTheClass, Classes>...
			{
			public:
				template<typename T>
				T& GetImpl()
				{
					return LocalComponentVector<NameOfTheClass, T>::GetComponent(m_IdOfInstance);
				}

				HelperInitializer() noexcept
				{
					m_IdOfInstance = static_cast<size_t>(s_IdsInVector.emplace_back(s_IdsInVector.size()));
					AddAllComponents<Classes...>(HelperStruct<Classes...>());
				}
				~HelperInitializer()
				{
					if (!m_IdOfInstance.IsInitialized())
						return;

					for (size_t currentComponentIdIndex = m_IdOfInstance + 1; currentComponentIdIndex < s_IdsInVector.size(); currentComponentIdIndex++)
					{
						size_t& currentComponentId = s_IdsInVector[currentComponentIdIndex];
						currentComponentId--;
					}

					DeleteAllComponents<Classes...>(HelperStruct<Classes...>());
				}

				HelperInitializer(const HelperInitializer& other) noexcept
				{
					m_IdOfInstance = static_cast<size_t>(s_IdsInVector.emplace_back(s_IdsInVector.size()));
					AddAllComponents<Classes...>(HelperStruct<Classes...>());

					CopyAllComponents(HelperStruct<Classes...>(), other);
				}
				HelperInitializer& operator=(const HelperInitializer& other) noexcept
				{
					if (this != &other)
					{
						Assert(componentId.IsInitialized(), "ComponentIdToCopy {0} is not initialized!", static_cast<size_t>(componentId));

						if (!m_IdOfInstance.IsInitialized())
						{
							m_IdOfInstance = static_cast<size_t>(s_IdsInVector.emplace_back(s_IdsInVector.size()));
							AddAllComponents<Classes...>(HelperStruct<Classes...>());
						}

						CopyAllComponents(HelperStruct<Classes...>(), other);
					}

					return *this;
				}

				HelperInitializer(HelperInitializer&& other) noexcept
				{
					m_IdOfInstance = other.m_IdOfInstance;
					other.m_IdOfInstance.Invalidate();
					//MoveAllComponents(HelperStruct<Classes...>(), std::move(other));
				}
				HelperInitializer& operator=(HelperInitializer&& other) noexcept
				{
					m_IdOfInstance = other.m_IdOfInstance;
					other.m_IdOfInstance.Invalidate();
					return *this;

					//MoveAllComponents(HelperStruct<Classes...>(), std::move(other));
				}
			private:
				template<typename Component, typename ... Components>
				void AddAllComponents(HelperStruct<Component, Components...> disposable)
				{
					LocalComponentVector<NameOfTheClass, Component>::AddComponent();
					AddAllComponents(HelperStruct<Components...>());
				}
				void AddAllComponents(HelperStruct<> disposable) {}

				template<typename Component, typename ... Components>
				void DeleteAllComponents(HelperStruct<Component, Components...> disposable)
				{
					LocalComponentVector<NameOfTheClass, Component>::DeleteComponent(m_IdOfInstance);
					DeleteAllComponents(HelperStruct<Components...>());
				}
				void DeleteAllComponents(HelperStruct<> disposable) {}

				template<typename Component, typename ... Components>
				void CopyAllComponents(HelperStruct<Component, Components...> disposable, const HelperInitializer& other)
				{
					LocalComponentVector<NameOfTheClass, Component>::CopyComponent(m_IdOfInstance, other.m_IdOfInstance);
					CopyAllComponents(HelperStruct<Components...>(), other);
				}
				void CopyAllComponents(HelperStruct<> disposable, const HelperInitializer& other) {}
			private:
				IdInComponentSystem<NameOfTheClass> m_IdOfInstance;

				static std::vector<IdInComponentSystem<NameOfTheClass>> s_IdsInVector;
			};
			HelperInitializer m_HelperInitializer;
		};
		template<typename NameOfTheClass, typename ... Classes> std::vector<IdInComponentSystem<NameOfTheClass>> GroupedLocalComponentVector<NameOfTheClass, Classes...>::HelperInitializer::s_IdsInVector;

		*/

		template<typename T>
		struct VectorType
		{
		protected:
			template<typename NameOfTheClass>
			static void AddComponent(HelperStruct<T> dispose)
			{
				std::vector<T>& Instance = GetTypeComponent<NameOfTheClass>(HelperStruct<T>());

				Instance.emplace_back();
			}

			template<typename NameOfTheClass>
			static void DeleteComponent(size_t id, HelperStruct<T> dispose)
			{
				std::vector<T>& Instance = GetTypeComponent<NameOfTheClass>(HelperStruct<T>());

				Instance.erase(Instance.begin() + id);
			}

			template<typename NameOfTheClass>
			static void CopyComponent(size_t id, size_t idToCopy, HelperStruct<T> disposable)
			{
				std::vector<T>& Instance = GetTypeComponent<NameOfTheClass>(HelperStruct<T>());

				T& element = Instance[id];
				const T& elementToCopy = Instance[idToCopy];

				element = elementToCopy;
			}

			template<typename NameOfTheClass>
			static T& GetComponent(size_t id, HelperStruct<T> dispose)
			{
				std::vector<T>& Instance = GetTypeComponent<NameOfTheClass>(HelperStruct<T>());

				Assert(id < Instance.size(), "Id does not exist in vector! :{0}", id);
				return Instance[id];
			}
		public:
			template<typename NameOfTheClass>
			static std::vector<T>& GetTypeComponent(HelperStruct<T> dispose)
			{
				static std::vector<T> Instance;
				return Instance;
			}
		};

		template<typename NameOfTheClass, typename ... Classes>
		struct ContainerFor : public VectorType<Classes>...
		{
		protected:
			static size_t CreateElement()
			{
				AddElementComponents<NameOfTheClass, Classes...>(HelperStruct<Classes...>());
				return s_IdCount++;
			}

			static void DeleteElement(size_t id)
			{
				DeleteElementComponents<NameOfTheClass>(id, HelperStruct<Classes...>());
				s_IdCount--;
			}

			static void CopyElement(size_t id, size_t idToCopy)
			{
				CopyElementComponents<NameOfTheClass>(id, idToCopy, HelperStruct<Classes...>());
			}

			template<typename T>
			static T& GetComponentFromElement(size_t id)
			{
				return VectorType<T>::GetComponent<NameOfTheClass>(id, HelperStruct<T>());
			}
		private:
			// Recursive Functions
			template<typename NameOfTheClass, typename First, typename ... Classes> static void AddElementComponents(HelperStruct<First, Classes...> disposable)
			{
				VectorType<First>::AddComponent<NameOfTheClass>(HelperStruct<First>());
				AddElementComponents<NameOfTheClass, Classes...>(HelperStruct<Classes...>());
			}
			template<typename NameOfTheClass> static void AddElementComponents(HelperStruct<> disposable) {}

			template<typename NameOfTheClass, typename First, typename ... Classes> static void DeleteElementComponents(size_t id, HelperStruct<First, Classes...> dispoable)
			{
				VectorType<First>::DeleteComponent<NameOfTheClass>(id, HelperStruct<First>());
				DeleteElementComponents<NameOfTheClass>(id, HelperStruct<Classes...>());
			}
			template<typename NameOfTheClass> static void DeleteElementComponents(size_t id, HelperStruct<> disposable) {}

			template<typename NameOfTheClass, typename First, typename ... Classes> static void CopyElementComponents(size_t id, size_t idToCopy, HelperStruct<First, Classes...> disposable)
			{
				VectorType<First>::CopyComponent<NameOfTheClass>(id, idToCopy, HelperStruct<First>());
				CopyElementComponents<NameOfTheClass>(id, idToCopy, HelperStruct<Classes...>());
			}
			template<typename NameOfTheClass> static void CopyElementComponents(size_t id, size_t idToCopy, HelperStruct<> disposable) {}
			// Recursive Functions
		private:
			static size_t s_IdCount;
		};
		template<typename NameOfTheClass, typename ... Classes> size_t ContainerFor<NameOfTheClass, Classes...>::s_IdCount = 0;

		template<typename NameOfTheClass, typename ... Classes>
		struct ElementInContainer : public ContainerFor<NameOfTheClass, Classes...>
		{
		protected:
			struct ElementId
			{
			public:
				std::shared_ptr<size_t> ElementIdView = nullptr;
			public:
				ElementId() noexcept
				{
					Validate();
				}
				~ElementId()
				{
					Invalidate();
				}

				operator size_t() const
				{
					return *ElementIdView;
				}

				void Validate()
				{
					if (ElementIdView)
						return;

					size_t obtainedId = ElementInContainer<NameOfTheClass, Classes...>::CreateElement();
					ElementIdView = ElementInContainer<NameOfTheClass, Classes...>::s_ElementIds.emplace_back(std::make_shared<size_t>(obtainedId));
				}
				void Invalidate()
				{
					if (!ElementIdView)
						return;

					ElementInContainer<NameOfTheClass, Classes...>::s_ElementIds.erase(ElementInContainer<NameOfTheClass, Classes...>::s_ElementIds.begin() + *ElementIdView);
					for (size_t elementIdIndex = *ElementIdView; elementIdIndex < ElementInContainer<NameOfTheClass, Classes...>::s_ElementIds.size(); elementIdIndex++)
					{
						size_t& elementId = *ElementInContainer<NameOfTheClass, Classes...>::s_ElementIds[elementIdIndex];
						elementId--;
					}

					ElementInContainer<NameOfTheClass, Classes...>::DeleteElement(*ElementIdView);
					ElementIdView = nullptr;
				}

				static void CopyIds(ElementId& elementId, const ElementId& elementIdToCopy)
				{
					elementId = elementIdToCopy;
				}

				static void MoveIds(ElementId& elementId, ElementId& elementIdToMove)
				{
					elementId = std::move(elementIdToMove);
				}

				ElementId(const ElementId& other) noexcept
				{
					Validate();
					ElementInContainer<NameOfTheClass, Classes...>::CopyElement(*ElementIdView, *other.ElementIdView);
				}
				ElementId& operator=(const ElementId& other) noexcept
				{
					if (this == &other)
						return *this;

					Validate();
					ElementInContainer<NameOfTheClass, Classes...>::CopyElement(*ElementIdView, *other.ElementIdView);
					return *this;
				}
				ElementId(ElementId&& other) noexcept
				{
					ElementIdView = other.ElementIdView;
					other.ElementIdView = nullptr;
				}
				ElementId& operator=(ElementId&& other) noexcept
				{
					Invalidate();
					ElementIdView = other.ElementIdView;
					other.ElementIdView = nullptr;
					return *this;
				}
			};

			ElementId& GetElementId()
			{
				return m_IdInVector;
			}
			const ElementId& GetElementId() const
			{
				return m_IdInVector;
			}
		public:
			template<typename T> T& Get()
			{
				Assert(m_IdInVector.ElementIdView.get(), "Invalid id!");

				return ElementInContainer<NameOfTheClass, Classes...>::GetComponentFromElement<T>(m_IdInVector);
			}
		private:
			ElementId m_IdInVector;
			static std::vector<std::shared_ptr<size_t>> s_ElementIds;
		};
		template<typename NameOfTheClass, typename ... Classes> std::vector<std::shared_ptr<size_t>> ElementInContainer<NameOfTheClass, Classes...>::s_ElementIds = {};

	}


}