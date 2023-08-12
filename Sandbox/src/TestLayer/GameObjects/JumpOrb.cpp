#include "TestLayer/GameObjects/JumpOrb.h"

namespace TestLayer {

	void JumpOrb::Init(GT::Vector2<float> position, GT::Vector2<float> size, float depth)
	{
		InitPositional(position, size, depth);
		SpriteSheetViewOfObject.DefaultInit(&SpriteSheetOfClass);
	}

	void JumpOrb::InitJumpOrbs()
	{
		SpriteSheetOfClass.DefaultInit("assets/textures/JumpOrb.png");
	}

}