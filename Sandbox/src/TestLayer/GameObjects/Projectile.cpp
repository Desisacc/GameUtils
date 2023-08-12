#include "TestLayer/GameObjects/Projectile.h"

#include "TestLayer/GameObjects/GlobalObjects.h"
#include "TestLayer/GameObjects/Player.h"

namespace TestLayer {
	
	const GT::Vector2<float> Projectile::PROJECTILE_SIZE = { PROJECTILE_LENGTH, PROJECTILE_LENGTH };

	void Projectile::Init(GT::Vector2<float> position, GT::Vector2<float> size, GT::Vector2<float> speed, float depth)
	{
		InitPositional(position, size, depth);
		SetDirectional(speed);
		SpriteSheetViewOfObject.DefaultInit(&SpriteSheetOfClass);
	}

	void Projectile::InitProjectiles()
	{
		SpriteSheetOfClass.Init("assets/textures/Projectile.png", { 20.0f, 20.0f }, 0.2f);
		SpriteSheetOfClass.AddAnimation("Default", 0);
	}

	void Projectile::UpdateMovement(Hazel::Timestep ts)
	{
		float& rotationInDegrees = c_Degrees;

		// Update rotation
		const GT::Vector2<float> projectileCenter = GetCoordinatesOfCenter();
		const GT::Vector2<float> playerCenter = GlobalObjects::GetPlayer().GetCoordinatesOfCenter();

		const GT::Vector2<float> distanceBetweenProjectileAndPlayer // Positions need to be in this order so they are relative to the projectile
			= { playerCenter.x - projectileCenter.x, playerCenter.y - projectileCenter.y };

		const float arcTanInRadians = abs(atan(distanceBetweenProjectileAndPlayer.y / distanceBetweenProjectileAndPlayer.x));
		const float arcTanInDegrees = glm::degrees(arcTanInRadians);

		rotationInDegrees = GT::Collider::TurnAngleIntoAccordingQuadrant(arcTanInDegrees, distanceBetweenProjectileAndPlayer);

		// Update position
		MoveHorizontally(cos(glm::radians(rotationInDegrees)) * GetSpeed().x * ts);
		MoveVertically(sin(glm::radians(rotationInDegrees)) * GetSpeed().y * ts);
	}

	void Projectile::OnUpdate(Hazel::Timestep ts)
	{
		UpdateComponents(ts);

		UpdateMovement(ts);
	}

}