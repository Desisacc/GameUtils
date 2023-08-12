#include "GameEditor/EditorObjects/SerializedGameObjects.h"

#include "TestLayer/GameObjects/Player.h"
#include "TestLayer/GameObjects/MovablePlatform.h"
#include "TestLayer/GameObjects/Spike.h"
#include "TestLayer/GameObjects/Projectile.h"
#include "TestLayer/GameObjects/JumpOrb.h"

namespace GameEditorLayer {

	const GT::Vector2<float> Player::PLAYER_SIZE_RANGE = { TestLayer::Player::PLAYER_LENGTH * 0.5f, TestLayer::Player::PLAYER_LENGTH * 1.5f };

	const GT::Vector2<float> MovablePlatform::PLATFORM_SPEED_RANGE = { -TestLayer::MovablePlatform::PLATFORM_SPEED, TestLayer::MovablePlatform::PLATFORM_SPEED };

	const GT::Vector2<float> Spike::SPIKE_SPEED_RANGE = { -TestLayer::Spike::SPIKE_SPEED, TestLayer::Spike::SPIKE_SPEED };

	const GT::Vector2<float> Projectile::PROJECTILE_SIZE_RANGE = { TestLayer::Projectile::PROJECTILE_LENGTH * 0.5f, TestLayer::Projectile::PROJECTILE_LENGTH * 1.5f };
	const GT::Vector2<float> Projectile::PROJECTILE_SPEED_RANGE = { TestLayer::Projectile::PROJECTILE_SPEED * 0.5f, TestLayer::Projectile::PROJECTILE_SPEED * 1.5f };

	const GT::Vector2<float> JumpOrb::JUMP_ORB_SIZE_RANGE = { TestLayer::JumpOrb::JUMP_ORB_LENGTH * 0.5f, TestLayer::JumpOrb::JUMP_ORB_LENGTH * 1.5f };

}