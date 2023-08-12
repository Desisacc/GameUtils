#include "gtpch.h"
#include "GT/ObjectSystems/SpriteSheetSystem.h"

namespace GT {

	std::unordered_map<size_t, GT::SpriteSheet::InitializerForSpriteSheet> LoadingSystem<SpriteSheet>::m_AllSpriteSheets = {};
	std::vector<GT::SpriteSheet> LoadingSystem<SpriteSheet>::m_LoadedSpriteSheets = {};

}