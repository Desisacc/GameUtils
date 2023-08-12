#pragma once

#include <tuple>

#include "GT/Components.h"
#include "GT/SpriteSheet.h"

namespace GT {

	/*class Base
	{
	public:
		template<typename Ts>
		std::vector<Ts>& Get();
	};*/

	template<typename T>
	class Derived /*: virtual public Base*/
	{
	private:
		template<typename Ts>
		std::vector<Ts>& Get();
	public:
		template<>
		std::vector<T>& Get()
		{
			static std::vector<T> s_ComponentVector;
			return s_ComponentVector;
		}
	};

	/*template<>
	class Derived<GT::Component::Positional> : virtual public Base
	{
	public:
		template<typename Ts>
		std::vector<Ts>& Get();

		template<>
		std::vector<GT::Component::Positional>& Get()
		{
			static std::vector<GT::Component::Positional> s_ComponentVector;
			return s_ComponentVector;
		}
	};
	template<>
	class Derived<int> : virtual public Base
	{
	public:
		template<typename Ts>
		std::vector<Ts>& Get();

		template<>
		std::vector<int>& Get()
		{
			static std::vector<int> s_ComponentVector;
			return s_ComponentVector;
		}
	};*/

	template<typename ... Args>
	class ComponentGroup : public Derived<Args>...
	{
	public:
		SpriteSheet& GetSpriteSheet() { return m_SpriteSheet; }
	private:
		SpriteSheet m_SpriteSheet;
	};

	/*template<typename ... Args>
	class CustomComponent : public Args... {};

	template<typename ... Args>
	class ComponentGroup
	{
	public:
		template<typename T> 
		std::vector<T>& Get() 
		{ 
			static_cast<T>(CustomComponent<Args...>());
			return (std::vector<T>)m_Component;
		}
		SpriteSheet& GetSpriteSheet() { return m_SpriteSheet; }
	private:
		std::vector<CustomComponent<Args...>> m_Component;

		SpriteSheet m_SpriteSheet;
	};*/

	/*template<typename ... Args>
	class CustomComponent : public Args... {};

	template<typename ... T>
	class ComponentGroup
	{
	public:
		ComponentGroup() = default;
		
		
	private:
		std::vector<T> m_Components;
	};*/

	/*template<typename ... Args>
	class ComponentGroup
	{
	public:
		ComponentGroup() = default;

		template<size_t index>
		auto& GetTypeVector()
		{
			return std::get<index>(m_Vectors);
		}

		void OnRender(const Component::Positional& positional)
		{
			m_SpriteSheet.OnRender(positional);
		}

		SpriteSheet& GetSpriteSheet() { return m_SpriteSheet; }
	private:
		std::tuple<std::vector<Args>...> m_Vectors;

		SpriteSheet m_SpriteSheet;
	};*/

	/*template<typename ... Args>
	class ComponentGroup
	{
	public:
		ComponentGroup() noexcept
		{
			AddToTypes<Args ...>(0, Args() ...);
		}

		//template<typename T>
		//std::vector<T>& GetTypeVector()
		//{
		//	auto typeIt = m_TypeMap.find(typeid(T).hash_code());
		//	Assert(typeIt != m_TypeMap.end(), "Type {0} does not exist in component group", typeid(T).name());
		//	const size_t index = typeIt->second;
		//	return std::get<index>(m_Vectors);
		//}

		template<typename T, size_t index>
		std::vector<T>& GetTypeVector()
		{
			return std::get<index>(m_Vectors);
		}

		void OnRender(const Component::Positional& positional)
		{
			m_SpriteSheet.OnRender(positional);
		}

		SpriteSheet& GetSpriteSheet() { return m_SpriteSheet; }
	private:
		template<typename ... Ts>
		void AddToTypes(size_t currentIndex, Ts ... args);

		template<typename T, typename ... Ts>
		void AddToTypes(size_t currentIndex, T t, Ts ... args)
		{
			m_TypeMap[typeid(T).hash_code()] = currentIndex;
			AddToTypes<Ts ...>(currentIndex + 1, Ts() ...);
		}

		template<>
		void AddToTypes(size_t currentIndex) {}
	private:
		std::tuple<std::vector<Args>...> m_Vectors;
		std::unordered_map<size_t, size_t> m_TypeMap;

		SpriteSheet m_SpriteSheet;
	};*/

	/*class ComponentGroup
	{
	public:
		ComponentGroup() = default;

		template<typename T>
		std::vector<T>& AddComponentType()
		{
			const size_t typeHashCode = typeid(T).hash_code();
			auto componentIt = m_ComponentTypes.find(typeHashCode);
			Assert(componentIt != m_ComponentTypes.end(), "Type has already been added! :{0}", typeid(T).name());

			std::vector<T>& components = GetComponents<T>();
			m_ComponentTypes[typeHashCode] = &components;
			return components;
		}
		template<typename T>
		const std::vector<T>& GetComponents() const
		{
			std::vector<T>& components = GetComponents<T>();
			return components;
		}
	private:
		template<typename T>
		std::vector<T>& GetComponents()
		{
			static std::vector<T> s_Component;
			return s_Component;
		}
	private:
		std::unordered_map<size_t, void*> m_ComponentTypes;
		SpriteSheet m_SpriteSheet;
	};*/

}