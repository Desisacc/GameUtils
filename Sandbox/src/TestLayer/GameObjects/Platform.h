#pragma once

#include <GT.h>

namespace TestLayer {

	class Platform : public GT::Component::GroupedComponent<GT::Component::ClassRenderable<Platform>>
	{
	public:
		Platform() = default;
		void Init(GT::Vector2<float> position, GT::Vector2<float> size, float depth = 0.0f);
		static void InitPlatforms();
	};

}