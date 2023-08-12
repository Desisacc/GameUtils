#pragma once

#include <Hazel.h>

namespace GT {

	class Timer
	{
	public:
		Timer() = default;
		/*Timer(Hazel::Timestep timeToWaitInSeconds) noexcept
			: m_TimeToWait(timeToWaitInSeconds) {}*/

		bool TimerHasEnded(Hazel::Timestep ts, bool resetTimer = true);

		float GetWaitingTime() const { return m_TimeToWait; }
		void SetNewWaitingTime(Hazel::Timestep timeToWait) { m_TimeToWait = timeToWait; }
		void ResetPassedTime() { m_PassedTime = 0.0f; }
	private:
		Hazel::Timestep m_TimeToWait = 0.0f;
		Hazel::Timestep m_PassedTime = 0.0f;
	};

}