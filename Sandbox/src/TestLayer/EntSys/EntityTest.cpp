#include "TestLayer/EntSys/EntityHolder.h"
#include "TestLayer/EntSys/Entity.h"

#include "GT/Utils.h"

class Position
{
public:
	float x = 0.0f, y = 0.0f;
	Position(float p_x, float p_y) noexcept
		: x(p_x), y(p_y) {}
	Position& operator=(std::initializer_list<float> values)
	{
		GT::Assert(values.size() == 2, "values.size() in class position was {0} when it should be 2!", values.size());
		x = *(values.begin() + 0);
		y = *(values.begin() + 1);
		return *this;
	}
};

void WeTest()
{
	EntityHolder holder;
	Entity& en = holder.AddEntity("Guy");

	Position& enPosition = en.Add<Position>(1.0f, 2.0f);
	enPosition.x = 10.0f;
	enPosition = { 1.0f, 2.0f };


}