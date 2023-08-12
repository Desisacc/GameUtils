#pragma once

#include <GT.h>

namespace TestLayer {

	class MovablePlatform : public GT::Component::GroupedComponent<GT::Component::ClassRenderable<MovablePlatform>, GT::Component::Directional>
	{
	public:
		static constexpr float PLATFORM_SPEED = 150.0f;
	public:
		MovablePlatform() = default;
		void Init(GT::Vector2<float> position, GT::Vector2<float> size, GT::Vector2<float> speed, float depth = 0.0f);
		static void InitMovablePlatforms();

		void OnUpdate(Hazel::Timestep ts);
	};

}