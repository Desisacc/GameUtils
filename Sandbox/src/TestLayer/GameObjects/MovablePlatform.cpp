#include "TestLayer/GameObjects/MovablePlatform.h"

#include "TestLayer/GameObjects/GlobalObjects.h"

namespace TestLayer {

	void MovablePlatform::Init(GT::Vector2<float> position, GT::Vector2<float> size, GT::Vector2<float> speed, float depth)
	{
		InitPositional(position, size, depth);
		SetDirectional(speed);
		SpriteSheetViewOfObject.DefaultInit(&SpriteSheetOfClass);
	}

	void MovablePlatform::InitMovablePlatforms()
	{
		SpriteSheetOfClass.Init("assets/textures/Platform.png", { 11.0f, 11.0f }, 0.0f);
		SpriteSheetOfClass.AddAnimation("Default", 1, 1);		
	}

	void MovablePlatform::OnUpdate(Hazel::Timestep ts)
	{
		UpdateComponents(ts);

		MoveHorizontally(GetSpeed().x * ts);
		MoveVertically(GetSpeed().y * ts);

		GT::Collider::HandleBorderCollisions(GetDirectional(), [this](GT::Collider::BorderCollision borderCollision) 
		{ 
			borderCollision & GT::Collider::BorderCollision::AxisX_BC ? GetSpeed().x *= -1.0f : GetSpeed().y *= -1.0f;
		});

		GT::Collider::HandleCollisions(GetPositional(), GlobalObjects::GetPlatforms(), [this](const GT::Component::Positional& otherPositional) 
		{
			if (GetSpeed().x)
			{
				const float positionAfterCollision = GT::Collider::HandleAxisCollisionBasedOnSpeed(GetRectangle().GetHorizontalLine(), GetSpeed().x, otherPositional.GetRectangle().GetHorizontalLine());
				SetHorizontally(positionAfterCollision);
				SetSpeedHorizontally(GetSpeed().x * -1.0f);
			}
			else
			{
				const float positionAfterCollision = GT::Collider::HandleAxisCollisionBasedOnSpeed(GetRectangle().GetVerticalLine(), GetSpeed().y, otherPositional.GetRectangle().GetVerticalLine());
				GetRectangle().Position.y = positionAfterCollision;
				SetSpeedVertically(GetSpeed().y * -1.0f);
			}
		});
	}

}