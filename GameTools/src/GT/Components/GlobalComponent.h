#pragma once

#include <vector>

#include "GT/Utils/Assert.h"
#include "GT/Components/ComponentBasics.h"

namespace GT {

	namespace Component {

		template<typename T>
		class GlobalComponentVector
		{
		protected:
			static void AddComponent(IdInComponentSystem<T>& componentId)
			{
				s_IdsInVector.emplace_back(s_Components.size());
				s_Components.emplace_back();
				componentId = s_IdsInVector.back();
			}

			static void DeleteComponent(IdInComponentSystem<T>& componentId)
			{
				if (!componentId.IsInitialized())
					return;

				for (size_t indexOfComponent = componentId + 1; indexOfComponent < s_IdsInVector.size(); indexOfComponent++)
				{
					size_t& idOfComponent = s_IdsInVector[indexOfComponent];
					idOfComponent--;
				}

				s_IdsInVector.erase(s_IdsInVector.begin() + componentId);
				s_Components.erase(s_Components.begin() + componentId);
				componentId.Invalidate();
			}

			void CopyComponent(const IdInComponentSystem<T>& componentIdToCopy)
			{
				Assert(componentIdToCopy.IsInitialized(), "ComponentId: {0} is uninitialized!", static_cast<size_t>(componentIdToCopy));

				if (!m_IdOfComponent.IsInitialized())
				{
					m_IdOfComponent = s_IdsInVector.emplace_back(s_Components.size());
					s_Components.emplace_back();
				}

				T& newComponent = s_Components[m_IdOfComponent];
				newComponent = s_Components[componentIdToCopy];
			}

			void MoveComponent(IdInComponentSystem<T>&& componentIdToMove)
			{
				Assert(componentIdToMove.IsInitialized(), "ComponentId: {0} is uninitialized!", static_cast<size_t>(componentIdToMove));

				if (m_IdOfComponent.IsInitialized())
					DeleteComponent(m_IdOfComponent);

				// Moving a smart pointer also sets it to null
				m_IdOfComponent = std::move(componentIdToMove);
			}

			T& GetComponent()
			{
				return s_Components[m_IdOfComponent];
			}

			static std::vector<T>& GetComponentVector()
			{
				return s_Components;
			}

			IdInComponentSystem<T>& GetIdComponent()
			{
				return m_IdOfComponent;
			}
			const IdInComponentSystem<T>& GetIdComponent() const
			{
				return m_IdOfComponent;
			}
		public:
			template<typename Func>
			static void UpdateComponentVector(Func func)
			{
				for (T& component : s_Components)
					func(component);
			}			
		private:
			IdInComponentSystem<T> m_IdOfComponent;

			static std::vector<T> s_Components;
			static std::vector<IdInComponentSystem<T>> s_IdsInVector;
		};
		template<typename T> std::vector<T> GlobalComponentVector<T>::s_Components;
		template<typename T> std::vector<IdInComponentSystem<T>> GlobalComponentVector<T>::s_IdsInVector;

		template<typename ... Classes>
		struct GroupedGlobalComponentVector
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
			class HelperInitializer : public GlobalComponentVector<Classes>...
			{
			public:
				template<typename T>
				T& GetImpl()
				{
					return GlobalComponentVector<T>::GetComponent();
				}

				HelperInitializer() noexcept
				{
					AddAllComponents<Classes...>(HelperStruct<Classes...>());
				}
				~HelperInitializer()
				{
					DeleteAllComponents<Classes...>(HelperStruct<Classes...>());
				}

				HelperInitializer(const HelperInitializer& other) noexcept
				{
					CopyAllComponents(HelperStruct<Classes...>(), other);
				}
				HelperInitializer& operator=(const HelperInitializer& other) noexcept
				{
					if (this != &other)
						CopyAllComponents(HelperStruct<Classes...>(), other);

					return *this;
				}

				HelperInitializer(HelperInitializer&& other) noexcept
				{
					MoveAllComponents(HelperStruct<Classes...>(), std::move(other));
				}
				HelperInitializer& operator=(HelperInitializer&& other) noexcept
				{
					MoveAllComponents(HelperStruct<Classes...>(), std::move(other));
					return *this;
				}
			private:
				template<typename Component, typename ... Components>
				void AddAllComponents(HelperStruct<Component, Components...> disposable)
				{
					GlobalComponentVector<Component>::AddComponent(GlobalComponentVector<Component>::GetIdComponent());
					AddAllComponents(HelperStruct<Components...>());
				}
				void AddAllComponents(HelperStruct<> disposable) {}

				template<typename Component, typename ... Components>
				void DeleteAllComponents(HelperStruct<Component, Components...> disposable)
				{
					GlobalComponentVector<Component>::DeleteComponent(GlobalComponentVector<Component>::GetIdComponent());
					DeleteAllComponents(HelperStruct<Components...>());
				}
				void DeleteAllComponents(HelperStruct<> disposable) {}

				template<typename Component, typename ... Components>
				void CopyAllComponents(HelperStruct<Component, Components...> disposable, const HelperInitializer& other)
				{
					GlobalComponentVector<Component>::CopyComponent(other.GlobalComponentVector<Component>::GetIdComponent());
					CopyAllComponents(HelperStruct<Components...>(), other);
				}
				void CopyAllComponents(HelperStruct<> disposable, const HelperInitializer& other) {}

				template<typename Component, typename ... Components>
				void MoveAllComponents(HelperStruct<Component, Components...> disposable, HelperInitializer&& other)
				{
					GlobalComponentVector<Component>::MoveComponent(std::move(other.GlobalComponentVector<Component>::GetIdComponent()));
					MoveAllComponents(HelperStruct<Components...>(), std::move(other));
				}
				void MoveAllComponents(HelperStruct<> disposable, HelperInitializer&& other) {}
			};
			HelperInitializer m_HelperInitializer;
		};

	}

}