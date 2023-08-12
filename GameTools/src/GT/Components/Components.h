#pragma once

#include "GT/Utils/Vectors.h"
#include "GT/Utils/Geometry.h"

#include "GT/Components/GlobalComponent.h"
#include "GT/Components/LocalComponent.h"
#include "GT/Components/Positional.h"
#include "GT/Components/Directional.h"
#include "GT/Components/Hitbox.h"
#include "GT/Components/Rotational.h"
#include "GT/Components/Renderables.h"

namespace GT {

	namespace Component {

		// Get OnUpdate Functions

		/*template<typename Component> void GetUpdateFunctions(Component& component, std::vector<std::function<void(Hazel::Timestep)>>& funcs, HelperStruct<> helper) {}
		template<typename Component, typename First, typename ... classes> void GetUpdateFunctions(Component& component, std::vector<std::function<void(Hazel::Timestep)>>& funcs, HelperStruct<First, classes...> helper)
		{
			funcs.emplace_back([&component](Hazel::Timestep ts) { First::OnUpdate(ts, component); });
			GetUpdateFunctions(component, funcs, HelperStruct<classes...>());
		}*/

		// ~~ Components ~~ //

		/*template<typename ... Components>
		class GroupedComponent : public Components...
		{
		public:
			GroupedComponent()
			{
				GetUpdateFunctions(*this, m_OnUpdateFunctions, HelperStruct<Components...>());
			}

			void UpdateComponents(Hazel::Timestep ts)
			{
				for (auto& func : m_OnUpdateFunctions)
					func(ts);
			}
		private:
			std::vector<std::function<void(Hazel::Timestep)>> m_OnUpdateFunctions;
		};*/

		// ~~ Components ~~ //

		// ~~ For-loops ~~ //

		// Takes component in lambda
		template<typename Func, typename ... ComponentType> void ForEachComponentTypeInVector(Func func, std::vector<ComponentType>&... vectors);
		template<typename Func, typename ... ComponentType> void ForEachComponentTypeInVector(Func func) {}
		template<typename Func, typename First, typename ... ComponentType> void ForEachComponentTypeInVector(Func func, std::vector<First>& firstVector, std::vector<ComponentType>&... vectors)
		{
			for (First& component : firstVector)
				func(component);

			ForEachComponentTypeInVector(func, vectors...);
		}

		// Takes vector in lambda
		template<typename Func, typename ... ComponentType> void ForEachComponentVector(Func func, std::vector<ComponentType>&... vectors);
		template<typename Func, typename ... ComponentType> void ForEachComponentVector(Func func) {}
		template<typename Func, typename First, typename ... ComponentType> void ForEachComponentVector(Func func, std::vector<First>& firstVector, std::vector<ComponentType>&... vectors)
		{
			func(firstVector);

			ForEachComponentVector(func, vectors...);
		}

		// Takes component in lambda
		template<typename Func, typename ... ComponentType> void ForEachComponentType(Func func, ComponentType&&... components);
		template<typename Func, typename ... ComponentType> void ForEachComponentType(Func func) {}
		template<typename Func, typename First, typename ... ComponentType> void ForEachComponentType(Func func, First&& firstComponent, ComponentType&&... components)
		{
			func(std::forward<First>(firstComponent));

			ForEachComponentType(func, std::forward<ComponentType>(components)...);
		}

		// ~~ For-loops ~~ //

	}

}