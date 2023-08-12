#pragma once

#include <GT.h>

namespace GameEditorLayer {

	/*struct PositionObject
	{
		GT::Vector2<uint32_t> PositionInTiles = { std::numeric_limits<uint32_t>::max(), std::numeric_limits<uint32_t>::max() };
		GT::Vector2<uint32_t> Size = { 0, 0 };

		void InitPositionObject(GT::Vector2<uint32_t> position, GT::Vector2<uint32_t> size)
		{
			PositionInTiles = position;
			Size = size;
		}
		void Invalidate()
		{
			PositionInTiles = { std::numeric_limits<uint32_t>::max(), std::numeric_limits<uint32_t>::max() };
		}
	};*/

	/*struct SpeedObject
	{
		GT::Vector2<uint32_t> Speed;

		void InitSpeedObject(GT::Vector2<uint32_t> speed)
		{
			Speed = speed;
		}
	};*/

	struct Player : public GT::Component::GroupedComponent<GT::Component::ClassRenderable<Player>>
	{
		Player() noexcept
		{
			SpriteSheetViewOfObject.Init(&SpriteSheetOfClass, 0.1f);
			SpriteSheetViewOfObject.SetAnimation("Default");
		}
		static void InitPlayer()
		{
			SpriteSheetOfClass.Init("assets/textures/StolenSheet.png", { 64.0f, 64.0f }, 0.0f);
			SpriteSheetOfClass.AddAnimation("Default", 3);
		}
		static const GT::Vector2<float> PLAYER_SIZE_RANGE;
	};

	struct EndFlag : public GT::Component::GroupedComponent<GT::Component::ClassRenderable<EndFlag>>
	{
		EndFlag() noexcept
		{
			SpriteSheetViewOfObject.DefaultInit(&SpriteSheetOfClass);
		}
		static void InitEndFlag()
		{
			SpriteSheetOfClass.DefaultInit("assets/textures/EndFlag.png");
		}
	};

	struct Platform : public GT::Component::GroupedComponent<GT::Component::ClassRenderable<Platform>>
	{
		struct Platform() noexcept
		{
			SpriteSheetViewOfObject.DefaultInit(&SpriteSheetOfClass);
		}
		static void InitPlatforms()
		{
			SpriteSheetOfClass.Init("assets/textures/Platform.png", { 11.0f, 11.0f }, 0.0f);
			SpriteSheetOfClass.AddAnimation("Default", 1, 1);
		}
	};

	struct MovablePlatform : public GT::Component::GroupedComponent<GT::Component::ClassRenderable<MovablePlatform>, GT::Component::Directional>
	{
		struct MovablePlatform() noexcept
		{
			SpriteSheetViewOfObject.DefaultInit(&SpriteSheetOfClass);
		}
		static void InitMovablePlatforms()
		{
			SpriteSheetOfClass.Init("assets/textures/Platform.png", { 11.0f, 11.0f }, { 0.2f });
			SpriteSheetOfClass.AddAnimation("Default", 1, 1);
		}
		static const GT::Vector2<float> PLATFORM_SPEED_RANGE;
	};

	struct Spike : public GT::Component::GroupedComponent<GT::Component::ClassRenderable<Spike>, GT::Component::Directional>
	{
		Spike() noexcept
		{
			SpriteSheetViewOfObject.DefaultInit(&SpriteSheetOfClass);
		}
		static void InitSpikes()
		{
			SpriteSheetOfClass.DefaultInit("assets/textures/Spike.png");
		}
		static const GT::Vector2<float> SPIKE_SPEED_RANGE;
	};

	struct Projectile : public GT::Component::GroupedComponent<GT::Component::ClassRenderable<Projectile>, GT::Component::Directional>
	{
		Projectile() noexcept
		{
			SpriteSheetViewOfObject.DefaultInit(&SpriteSheetOfClass);
		}
		static void InitProjectiles()
		{
			SpriteSheetOfClass.Init("assets/textures/Projectile.png", { 20.0f, 20.0f }, 0.2f);
			SpriteSheetOfClass.AddAnimation("Default", 0);
		}
		static const GT::Vector2<float> PROJECTILE_SIZE_RANGE;
		static const GT::Vector2<float> PROJECTILE_SPEED_RANGE;
	};

	struct JumpOrb : public GT::Component::GroupedComponent<GT::Component::ClassRenderable<JumpOrb>>
	{
		JumpOrb() noexcept
		{
			SpriteSheetViewOfObject.DefaultInit(&SpriteSheetOfClass);
		}
		static void InitJumpOrbs()
		{
			SpriteSheetOfClass.DefaultInit("assets/textures/JumpOrb.png");
		}
		static const GT::Vector2<float> JUMP_ORB_SIZE_RANGE;
	};

}