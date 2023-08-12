#include "MouseGame/MouseGameObjects/ItemSystem.h"

namespace MouseGameLayer {

	std::unordered_map<size_t, ItemInfo> ItemSystem::m_AllItems = {};
	std::vector<Item> ItemSystem::m_LoadedItems = {};

}