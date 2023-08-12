#include "gtpch.h"
#include "GT/Utils/Timer.h"

namespace GT {

	bool Timer::TimerHasEnded(Hazel::Timestep ts, bool resetTimer)
	{
		if (ts + m_PassedTime >= m_TimeToWait)
		{
			if (resetTimer)
				ResetPassedTime();

			return true;
		}

		m_PassedTime = m_PassedTime + ts;
		return false;
	}

}