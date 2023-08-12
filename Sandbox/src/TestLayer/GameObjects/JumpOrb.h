#pragma once

#include <GT.h>

namespace TestLayer {

	class JumpOrb : public GT::Component::GroupedComponent<GT::Component::ClassRenderable<JumpOrb>>
	{
	public:
		static constexpr float JUMP_ORB_LENGTH = 30.0f;
	public:
		JumpOrb() = default;
		void Init(GT::Vector2<float> position, GT::Vector2<float> size, float depth = 0.0f);
		static void InitJumpOrbs();
	};

}