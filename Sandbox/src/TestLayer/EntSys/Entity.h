#pragma once

#include "TestLayer/EntSys/EntityHolder.h"

class Entity
{
public:
	Entity(EntityHolder* parent) noexcept;

	template<typename T>
	size_t& GetComponentID()
	{
		static size_t componentID = 0;
		return componentID;
	}

	template<typename T, typename ... Args>
	T& Add(Args&& ... args)
	{
		size_t& componentID = GetComponentID<T>();
		return m_Parent->AddComponent<T>(componentID, std::forward<Args>(args)...);
	}

	template<typename T>
	T& Get()
	{
		size_t& componentID = GetComponentID<T>();
		return m_Parent->GetComponent<T>(componentID);
	}
private:
	EntityHolder* m_Parent = nullptr;
};