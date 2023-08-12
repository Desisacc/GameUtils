#include "TestLayer/EntSys/EntityHolder.h"

#include "TestLayer/EntSys/Entity.h"

#include "GT/Utils.h"

Entity& EntityHolder::AddEntity(const std::string& name)
{
	Entity& entityToReturn = m_Entities.emplace(name, this).first->second;
	return entityToReturn;
}

Entity& EntityHolder::GetEntity(const std::string& name)
{
	auto entityIt = m_Entities.find(name);
	GT::Assert(entityIt != m_Entities.end(), "Entity {0} could not be found!", name.c_str());
	return entityIt->second;
}