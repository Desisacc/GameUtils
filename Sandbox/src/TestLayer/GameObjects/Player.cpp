#include "TestLayer/GameObjects/Player.h"

#include <GT.h>

#include "TestLayer/GameObjects/GlobalObjects.h"
#include "TestLayer/GameObjects/Platform.h"
#include "TestLayer/GameObjects/JumpOrb.h"
#include "TestLayer/GameObjects/Projectile.h"
#include "TestLayer/GameObjects/Spike.h"
#include "TestLayer/GameObjects/EndFlag.h"

#include "TestLayer/LevelLoader.h"

namespace TestLayer {

	const GT::Vector2<float> Player::PLAYER_SIZE = { PLAYER_LENGTH, PLAYER_LENGTH };

	void Player::Init(GT::Vector2<float> position, GT::Vector2<float> size, float depth)
	{
		InitPositional(position, size, depth);
		SpriteSheetViewOfObject.DefaultInit(&SpriteSheetOfClass);
	}
	
	void Player::InitPlayer()
	{
		SpriteSheetOfClass.Init("assets/textures/StolenSheet.png", { 64.0f, 64.0f }, 0.1f);
		SpriteSheetOfClass.AddAnimation("Default", 6);
	}

	void Player::UpdateMovement(Hazel::Timestep ts)
	{
		GT::Vector2<float> position = GetPosition();
		GT::Vector2<float> speed = GetSpeed();

		position.x = speed.x * ts;
		position.y = speed.y * ts;

		// Gather user key input
		m_PlayerInput.GatherInput();

		// ~~~ Vertical Speed ~~~ // 

		// Applying gravity and limiting the fall speed
		speed.y += -GRAVITY * ts;
		speed.y = std::max(speed.y, MAX_FALL_SPEED);

		// ~~~ Lateral Speed ~~~ //

		// Regular movement
		if (!m_IsInWallJump)
		{
			speed.x = 0.0f;

			if (m_PlayerInput.KeyLeft())
				speed.x = -HORIZONTAL_SPEED;
			else if (m_PlayerInput.KeyRight())
				speed.x = HORIZONTAL_SPEED;

			if (m_PlayerInput.KeyShift())
				speed.x /= 2.0f;
		}
		// Acceleration while wall jumping
		else
		{
			if (m_PlayerInput.KeyLeft())
			{
				speed.x += -WALL_JUMP_HORIZONTAL_ACCELERATION * ts;
				speed.x = std::max(speed.x, -MAX_WALL_JUMP_HORIZONTAL_SPEED);
			}
			else if (m_PlayerInput.KeyRight())
			{
				speed.x += WALL_JUMP_HORIZONTAL_ACCELERATION * ts;
				speed.x = std::min(speed.x, MAX_WALL_JUMP_HORIZONTAL_SPEED);
			}
		}

		SetPosition(position);
		SetSpeed(speed);
	}

	void Player::HandleBorderCollisions(GT::Collider::BorderCollision borderCollision)
	{
		GT::Vector2<float> speed = GetSpeed();

		switch (borderCollision)
		{
		case GT::Collider::BorderCollision::LeftBorder_BC:
		case GT::Collider::BorderCollision::RightBorder_BC:
		{
			speed.x = 0.0f;

			AttemptWallJump();
			break;
		}
		case GT::Collider::BorderCollision::BottomBorder_BC:
		{
			speed.y = MIN_FALL_SPEED;

			ResetJump();
			AttemptJump();
			break;
		}
		case GT::Collider::BorderCollision::TopBorder_BC:
		{
			speed.y = MIN_FALL_SPEED;
			break;
		}
		default:
			GT::Assert(false, "Unknown BorderCollision! :{0}", static_cast<uint32_t>(borderCollision));
		}

		SetSpeed(speed);

		/*
		// Side Borders
		if (position.x < 0.0f)
		{
			position.x = 0.0f;
			speed.x = 0.0f;
			AttemptWallJump();
			
		}
		else if (position.x + size.x > (float)GT::GlobalData::GetMapWidth())
		{
			position.x = (float)GT::GlobalData::GetMapWidth() - size.x;
			speed.x = 0.0f;
			AttemptWallJump();
		}

		// Top and bottom borders
		if (position.y < 0.0f)
		{
			position.y = 0.0f;
			speed.y = 0.0f;
			ResetJump();
			AttemptJump();
			
		}
		else if (position.y + size.y > (float)GT::GlobalData::GetMapHeight() && speed.y > 0.0f)
		{
			position.y = (float)GT::GlobalData::GetMapHeight() - size.y;
			speed.y = 0.0f;
		}*/
	}

	void Player::HandlePlatformCollision(const GT::Component::Positional& platformPositional, GT::Collider::CollisionType collisionType)
	{
		GT::Vector2<float> speed = GetSpeed();

		switch (collisionType)
		{
		case GT::Collider::CollisionType::LeftSide_CT:
		case GT::Collider::CollisionType::RightSide_CT:
		{
			speed.x = 0.0f;

			AttemptWallJump();
			break;
		}
		case GT::Collider::CollisionType::BottomSide_CT:
		{
			speed.y = MIN_FALL_SPEED;
			break;
		}
		case GT::Collider::CollisionType::TopSide_CT:
		{
			speed.y = MIN_FALL_SPEED;

			ResetJump();
			AttemptJump();
			break;
		}
		default:
			GT::Assert(false, "Unknown BorderCollision! :{0}", static_cast<uint32_t>(collisionType));
		}

		SetSpeed(speed);

		/*switch (collisionType)
		{
		case GT::Collider::CollisionType::AxisX_CT:
		{
			c_Speed.x = 0.0f;
			AttemptWallJump();
			break;
		}
		case GT::Collider::CollisionType::AxisY_CT:
		{
			if (c_PreviousSpeed.y < 0.0f)
				ResetJump();

			c_Speed.y = MIN_FALL_SPEED;
			AttemptJump();
			break;
		}
		}*/
	}

	void Player::HandleMovablePlatformCollision(const GT::Component::Directional& movablePlatformDirectional, GT::Collider::CollisionType collisionType)
	{
		GT::Vector2<float> speed = GetSpeed();

		switch (collisionType)
		{
		case GT::Collider::CollisionType::LeftSide_CT:
		case GT::Collider::CollisionType::RightSide_CT:
		{
			speed.x = 0.0f;

			AttemptWallJump();
			break;
		}
		case GT::Collider::CollisionType::BottomSide_CT:
		{
			speed.y = std::min(MIN_FALL_SPEED, movablePlatformDirectional.GetSpeedFromLastUpdate().y);
			break;
		}
		case GT::Collider::CollisionType::TopSide_CT:
		{
			speed.y = MIN_FALL_SPEED;

			speed.x += movablePlatformDirectional.GetSpeedFromLastUpdate().x;
			ResetJump();
			AttemptJump();
			break;
		}
		default:
			GT::Assert(false, "Unknown BorderCollision! :{0}", static_cast<uint32_t>(collisionType));
		}

		SetSpeed(speed);

		/*switch (collisionType)
		{
		case GT::Collider::CollisionType::AxisX_CT:
		{
			c_Speed.x = 0.0f;
			AttemptWallJump();
			break;
		}
		case GT::Collider::CollisionType::AxisY_CT:
		{
			if (c_PreviousSpeed.y <= 0.0f)
			{
				c_Speed.x += platformDirectional.c_PreviousSpeed.x;
				ResetJump();
			}

			MoveVertically(platformPositional.GetTraveledDistance().y);
			c_Speed.y = MIN_FALL_SPEED;
			AttemptJump();
			break;
		}
		}*/
	}

	/*void Player::HandlePlatformCollisions()
	{
		struct PlatformCollision
		{
			const Platform* CollidedPlatform = nullptr;
			GT::Collider::CollisionInfo CollisionInfo;

			PlatformCollision(const Platform* collidedPlatform, const GT::Collider::CollisionInfo& collisionInfo) noexcept
				: CollidedPlatform(collidedPlatform), CollisionInfo(collisionInfo) {}
		};

		// Finded all platforms that collided with the player and handle all collisions, save the postponed collisions
		std::vector<PlatformCollision> collidedPlatforms;
		for (const Platform& platform : GlobalObjects::GetPlatforms())
		{
			// Adds all platforms that collided with the player into a vector
			const GT::Collider::CollisionInfo collisionInfo = 
				GT::Collider::FindIntersectionWithMovement(m_PreviousPositional, GetPositional(), platform.GetPositional());

			if (collisionInfo.CollisionAxis != GT::Collider::CollisionType::None)
				collidedPlatforms.emplace_back(&platform, collisionInfo);
		}

		// Sort collisions in ascending order of collision time
		std::sort(collidedPlatforms.begin(), collidedPlatforms.end(), [](const PlatformCollision& one, const PlatformCollision& two)
		{ return one.CollisionInfo.ratioDistanceSpeed > two.CollisionInfo.ratioDistanceSpeed; });

		// Handle collisions in order, if a platform no longer collides due to the changes made by the previous collisions, ignore it
		for (size_t currentCollidedPlatformIndex = 0; currentCollidedPlatformIndex < collidedPlatforms.size(); currentCollidedPlatformIndex++)
		{
			const PlatformCollision& currentCollidedPlatform = collidedPlatforms[currentCollidedPlatformIndex];

			HandleIndividualPlatformCollision(*currentCollidedPlatform.CollidedPlatform, currentCollidedPlatform.CollisionInfo.CollisionAxis);

			for (currentCollidedPlatformIndex++; currentCollidedPlatformIndex < collidedPlatforms.size(); currentCollidedPlatformIndex++)
			{
				const Platform& platformToCheck = *collidedPlatforms[currentCollidedPlatformIndex].CollidedPlatform;

				if (GT::Collider::RectanglesHaveIntersection(GetPositional(), platformToCheck.GetPositional()))
					break;
			}
		}

		//- Find all collisioned objects
		//Use Collider::RectanglesHaveIntersection
		//
		//- Find the time for collision for each object
		//Use the distance-speed ratio
		//
		//- Handle the collision with the lower time
		//Take the lower distance-speed ratio and change its position and speed in its respective axis
		//
		//- Repeat until there are no collisioned objects
		//Run the algorithm in the remaining collided rectangles
	}*/

	void Player::OnUpdate(Hazel::Timestep ts)
	{
		//---- Lateral Movement ----
		//- Moving right and left
		//
		//---- Vertical Movement ----
		//- Regular jumping
		//- Wall jumps
		//- Orb jumps
		//
		//---- Collisions ----
		//- Platform
		//- Orbs
		//- Projectiles
		//
		//1. Player basic movement
		//- Lateral movement
		//- Jumping
		//- Gravity
		//
		//2. Collisions
		//- Platforms
		//- Orbs
		//- Bullet
		//
		//3. Special movements
		//Wall jumps
		//Orb jumps
		UpdateComponents(ts);

		UpdateMovement(ts);

		// Border collisions
		GT::Collider::HandleBorderCollisions(GetDirectional(), [this](GT::Collider::BorderCollision borderCollision)
			{ HandleBorderCollisions(borderCollision); });

		// Platform collisions
		GT::Collider::HandleMovementCollisions(GetDirectional(), GlobalObjects::GetPlatforms(), [this](const GT::Component::Positional& platformPositional, GT::Collider::CollisionType collisionType)
			{ HandlePlatformCollision(platformPositional, collisionType); });

		// Movable Platform collisions
		GT::Collider::HandleMovementCollisions(GetDirectional(), GlobalObjects::GetMovablePlatforms(), [this](const GT::Component::Directional& movablePlatformDirectional, GT::Collider::CollisionType collisionType)
			{ HandleMovablePlatformCollision(movablePlatformDirectional, collisionType); });

		// Jump Orb collisions
		GT::Collider::HandleCollisions(GetPositional(), GlobalObjects::GetJumpOrbs(), [this](const GT::Component::Positional& positionalToCheck)
			{ AttemptOrbJump(); });

		// End Flag collisions
		if (bool playerCollidedWithEndFlag = GT::Collider::RectanglesHaveIntersection(GetPositional().GetRectangle(), GlobalObjects::GetEndFlag().GetPositional().GetRectangle()); playerCollidedWithEndFlag)
			m_HasCompletedLevel = true;

		// Projectile collisions
		GT::Collider::HandleCollisions(GetPositional(), GlobalObjects::GetProjectiles(), [this](const GT::Component::Positional& positionalToCheck)
			{ LevelLoader::ResetCurrentLevel(); });

		// Spike collisions
		GT::Collider::HandleCollisions(GetPositional(), GlobalObjects::GetSpikes(), [this](const GT::Component::Positional& positionalToCheck)
			{ LevelLoader::ResetCurrentLevel(); });
	}

}