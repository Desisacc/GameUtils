#pragma once

#include "TestLayer/EntSys/Entity.h"
#include "TestLayer/EntSys/EntityHolder.h"

#include "GT/Utils.h"
#include "GT/Components.h"

class MoveBlock : public GT::Component::Positional, public GT::Component::Directional, public GT::Component::Renderable
{
public:
	MoveBlock() = default;
	void Init(GT::Vector2<float> position, GT::Vector2<float> size, GT::Vector2<float> speed);

	void OnUpdate(Hazel::Timestep ts);
	void OnRender();
};