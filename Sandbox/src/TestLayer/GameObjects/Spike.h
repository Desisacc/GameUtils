#pragma once

#include <GT.h>

namespace TestLayer {

	class Spike : public GT::Component::GroupedComponent<GT::Component::ClassRenderable<Spike>, GT::Component::Directional>
	{
	public:
		static constexpr float SPIKE_SPEED = 150.0f;
	public:
		Spike() = default;
		void Init(GT::Vector2<float> position, GT::Vector2<float> size, float depth = 0.0f);
		static void InitSpikes();

		void OnUpdate(Hazel::Timestep ts);
	};

}