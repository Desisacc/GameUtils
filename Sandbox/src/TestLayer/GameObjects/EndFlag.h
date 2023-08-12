#pragma once

#include <GT.h>

namespace TestLayer {

	class EndFlag : public GT::Component::GroupedComponent<GT::Component::ClassRenderable<EndFlag>>
	{
	public:
		EndFlag() = default;
		void Init(GT::Vector2<float> position, GT::Vector2<float> size, float depth = 0.0f);
		static void InitEndFlag();
	};

}