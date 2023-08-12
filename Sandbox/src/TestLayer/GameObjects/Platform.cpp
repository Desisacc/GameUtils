#include "TestLayer/GameObjects/Platform.h"

namespace TestLayer {

	void Platform::Init(GT::Vector2<float> position, GT::Vector2<float> size, float depth)
	{
		InitPositional(position, size, depth);
		SpriteSheetViewOfObject.DefaultInit(&SpriteSheetOfClass);
	}

	void Platform::InitPlatforms()
	{
		SpriteSheetOfClass.Init("assets/textures/Platform.png", { 11.0f, 11.0f }, 0.0f);
		SpriteSheetOfClass.AddAnimation("Default", 1, 1);
	}
}