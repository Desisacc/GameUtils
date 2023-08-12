#include "Entity.h"

Entity::Entity(EntityHolder* parent) noexcept
	: m_Parent(parent) {}