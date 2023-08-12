#pragma once

#include <GT.h>

namespace TestLayer {

	class Player : public GT::Component::GroupedComponent<GT::Component::ClassRenderable<Player>, GT::Component::Directional>
	{
	public:
		static constexpr float PLAYER_LENGTH = 60.0f;
		static const GT::Vector2<float> PLAYER_SIZE;
	public:
		Player() = default;
		void Init(GT::Vector2<float> position, GT::Vector2<float> size, float depth = 0.0f);
		static void InitPlayer();

		void OnUpdate(Hazel::Timestep ts);

		bool HasCompletedLevel() const { return m_HasCompletedLevel; }
		void ResetCompletedLevelState()
		{
			m_HasCompletedLevel = false;

			m_IsInAir = false;
			m_CanOrbJump = false;
			m_CanWallJump = false;
			m_IsInWallJump = false;

			SetDirectional({ 0.0f, 0.0f });
		}
	private:
		static constexpr float JUMP_SPEED = 800.0f;
		static constexpr float GRAVITY = JUMP_SPEED * 3.0f;
		static constexpr float MIN_FALL_SPEED = -40.0f;
		static constexpr float MAX_FALL_SPEED = -1000.0f;

		static constexpr float HORIZONTAL_SPEED = 400.0f;
		static constexpr float MAX_WALL_JUMP_HORIZONTAL_SPEED = HORIZONTAL_SPEED * 1.2f;
		static constexpr float WALL_JUMP_HORIZONTAL_ACCELERATION = HORIZONTAL_SPEED * 2.2f;

		static constexpr float JUMP_ORB_JUMP_SPEED = JUMP_SPEED * 1.2f;

		struct PlayerInput
		{
			GT::Input::InputKey KeyW;
			GT::Input::InputKey KeyS;
			GT::Input::InputKey KeyA;
			GT::Input::InputKey KeyD;
			GT::Input::InputKey KeyShiftLeft;
			GT::Input::InputKey KeyShiftRight;

			PlayerInput() noexcept
				: KeyW(Hazel::Key::W), KeyS(Hazel::Key::S), KeyA(Hazel::Key::A), KeyD(Hazel::Key::D),
				KeyShiftLeft(Hazel::Key::LeftShift), KeyShiftRight(Hazel::Key::RightShift) {}
			void GatherInput()
			{
				KeyW.GatherInput();
				KeyS.GatherInput();
				KeyA.GatherInput();
				KeyD.GatherInput();
				KeyShiftLeft.GatherInput();
				KeyShiftRight.GatherInput();
			}

			bool KeyUp(uint32_t pressType = GT::Input::InputKey::DEFAULT_PRESS_TYPE)
			{
				return KeyW.IsKeyPressed(pressType) && !KeyS.IsKeyPressed();
			}
			bool KeyDown(uint32_t pressType = GT::Input::InputKey::DEFAULT_PRESS_TYPE)
			{
				return KeyS.IsKeyPressed(pressType) && !KeyA.IsKeyPressed();
			}
			bool KeyLeft(uint32_t pressType = GT::Input::InputKey::DEFAULT_PRESS_TYPE)
			{
				return KeyA.IsKeyPressed(pressType) && !KeyD.IsKeyPressed();
			}
			bool KeyRight(uint32_t pressType = GT::Input::InputKey::DEFAULT_PRESS_TYPE)
			{
				return KeyD.IsKeyPressed(pressType) && !KeyA.IsKeyPressed();
			}
			bool KeyShift(uint32_t pressType = GT::Input::InputKey::DEFAULT_PRESS_TYPE)
			{
				return KeyShiftLeft.IsKeyPressed(pressType) || KeyShiftRight.IsKeyPressed(pressType);
			}
		};
	private:
		void UpdateMovement(Hazel::Timestep ts);

		void HandleBorderCollisions(GT::Collider::BorderCollision borderCollision);
		void HandlePlatformCollision(const GT::Component::Positional& platformPositional, GT::Collider::CollisionType collisionType);
		void HandleMovablePlatformCollision(const GT::Component::Directional& movablePlatformDirectional, GT::Collider::CollisionType collisionType);

		void ResetJump()
		{
			m_IsInAir = false;
			m_IsInWallJump = false;
			m_CanOrbJump = true;
		}
		void Jump(float speed = JUMP_SPEED)
		{
			SetSpeedVertically(speed);
			m_IsInAir = true;
		}
		void WallJump(float speed)
		{
			m_IsInWallJump = true;
			SetSpeedHorizontally(speed);
			Jump();
		}
		void OrbJump()
		{
			m_CanOrbJump = false;
			Jump(JUMP_ORB_JUMP_SPEED);
		}

		void AttemptJump()
		{
			if (m_PlayerInput.KeyUp() && !m_IsInAir)
				Jump();
		}
		void AttemptWallJump()
		{
			if (m_PlayerInput.KeyUp() && m_PlayerInput.KeyShift())
			{
				if (m_PlayerInput.KeyRight() && GetSpeedFromLastUpdate().x > 0.0f)
					WallJump(-MAX_WALL_JUMP_HORIZONTAL_SPEED);
				else if (m_PlayerInput.KeyLeft() && GetSpeedFromLastUpdate().x < 0.0f)
					WallJump(MAX_WALL_JUMP_HORIZONTAL_SPEED);
			}
		}
		void AttemptOrbJump()
		{
			if (m_PlayerInput.KeyUp(GT::Input::InputKey::PressType::Press) && m_CanOrbJump)
				OrbJump();
		}

		/*void Die()
		{
			m_IsInAir = false;
			m_CanOrbJump = false;
			m_CanWallJump = false;
			m_IsInWallJump = false;

			m_Positional = m_StartingPositional;
			m_Directional.InitDirectional({ 0.0f, 0.0f });
		}*/
	private:
		PlayerInput m_PlayerInput;
		bool m_IsInAir = false;
		bool m_CanOrbJump = false;
		bool m_CanWallJump = false;
		bool m_IsInWallJump = false;

		bool m_HasCompletedLevel = false;
	};

	/*for (const JumpOrb& jumpOrb : GlobalObjects::GetJumpOrbs())
	{
		const bool playerIntersectsWithJumpOrb = GT::Collider::RectanglesHaveIntersection(GetPositional(), jumpOrb.GetPositional());
		if (playerIntersectsWithJumpOrb)
			AttemptOrbJump();
	}*/
}