#pragma once

#include <string>
#include <unordered_map>

class Entity;

class EntityHolder
{
public:
	EntityHolder() = default;
	
	Entity& AddEntity(const std::string& name);
	Entity& GetEntity(const std::string& name);

	template<typename T>
	std::vector<T>& GetComponentType()
	{
		static std::vector<T> s_Components;
		return s_Components;
	}

	template<typename T, typename ... Args>
	T& AddComponent(size_t& componentID, Args&& ... args)
	{
		std::vector<T>& components = GetComponentType<T>();
		componentID = components.size();
		return components.emplace_back(std::forward<Args>(args)...);
	}

	template<typename T>
	T* GetComponent(size_t componentID)
	{
		std::vector<T>& components = GetComponentType<T>();
		return components[componentID];
	}
private:
	std::unordered_map<std::string, Entity> m_Entities;
};
