#include "TestLayer/EntSys/MoveBlock.h"

void MoveBlock::Init(GT::Vector2<float> position, GT::Vector2<float> size, GT::Vector2<float> speed)
{
	c_Position = position;
	c_Size = size;
	c_Speed = speed;
}

void MoveBlock::OnUpdate(Hazel::Timestep ts)
{
	c_Position.x += c_Speed.x * ts;
	c_Position.y += c_Speed.y * ts;
}

void MoveBlock::OnRender()
{
	c_SpriteSheet.OnRender(*this);
}