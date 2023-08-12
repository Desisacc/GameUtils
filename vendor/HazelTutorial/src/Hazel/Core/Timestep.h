#pragma once

namespace Hazel
{

	class Timestep
	{
	public:
		Timestep(float time = 0.0f)
			: m_Time(time)
		{
		}

		operator float() const { return m_Time; }

		float GetSeconds() const { return m_Time; }
		float GetMilliseconds() const { return m_Time * 1000.0f; }

		//MODED
		Timestep operator+(const Timestep& other) const
		{
			return m_Time + other.m_Time;
		}
		//MODED
	private:
		float m_Time;
	};

}