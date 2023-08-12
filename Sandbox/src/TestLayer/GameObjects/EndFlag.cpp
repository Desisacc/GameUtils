#include "TestLayer/GameObjects/EndFlag.h"

namespace TestLayer {

	void EndFlag::Init(GT::Vector2<float> position, GT::Vector2<float> size, float depth)
	{
		InitPositional(position, size, depth);
		SpriteSheetViewOfObject.DefaultInit(&SpriteSheetOfClass);
	}

	void EndFlag::InitEndFlag()
	{
		SpriteSheetOfClass.DefaultInit("assets/textures/EndFlag.png");
	}

}