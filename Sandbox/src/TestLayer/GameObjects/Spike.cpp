#include "TestLayer/GameObjects/Spike.h"

#include "TestLayer/GameObjects/GlobalObjects.h"

namespace TestLayer {

	void Spike::Init(GT::Vector2<float> position, GT::Vector2<float> size, float depth)
	{
		InitPositional(position, size, depth);
		SpriteSheetViewOfObject.DefaultInit(&SpriteSheetOfClass);

	}

	void Spike::InitSpikes()
	{
		SpriteSheetOfClass.DefaultInit("assets/textures/Spike.png");
	}

	void Spike::OnUpdate(Hazel::Timestep ts)
	{
		UpdateComponents(ts);

		GT::Vector2<float> speed = GetSpeed();

		MoveHorizontally(speed.x * ts);
		MoveVertically(speed.y * ts);

		GT::Collider::HandleBorderCollisions(GetDirectional(), [this, speed](GT::Collider::BorderCollision borderCollision)
		{
			borderCollision & GT::Collider::BorderCollision::AxisX_BC ? speed.x *= -1.0f : speed.y *= -1.0f;
		});

		GT::Collider::HandleCollisions(GetPositional(), GlobalObjects::GetPlatforms(), [this, speed](const GT::Component::Positional& otherPositional)
		{
			if (speed.x)
			{
				const float positionAfterCollision = GT::Collider::HandleAxisCollisionBasedOnSpeed(GetRectangle().GetHorizontalLine(), speed.x, otherPositional.GetRectangle().GetHorizontalLine());
				SetHorizontally(positionAfterCollision);
				speed.x *= -1.0f;
			}
			else
			{
				const float positionAfterCollision = GT::Collider::HandleAxisCollisionBasedOnSpeed(GetRectangle().GetVerticalLine(), speed.y, otherPositional.GetRectangle().GetVerticalLine());
				GetRectangle().Position.y = positionAfterCollision;
				speed.y *= -1.0f;
			}
		});

		SetSpeed(speed);
	}

}