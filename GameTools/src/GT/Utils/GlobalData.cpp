#include "gtpch.h"
#include "GT/Utils/GlobalData.h"

namespace GT {

	uint32_t GlobalData::WindowWidth = 0;
	uint32_t GlobalData::WindowHeight = 0;

	uint32_t GlobalData::MapWidth = 0;
	uint32_t GlobalData::MapHeight = 0;

	std::vector<Vector2<float>> GlobalData::MouseClicks = {};
}