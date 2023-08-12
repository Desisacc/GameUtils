#pragma once

#include <Hazel.h>

namespace GT {

	template<typename ... Args>
	inline constexpr void Assert(bool expression, const char* message = "", Args&& ... args)
	{
		if (!expression)
		{
			HZ_ERROR(message, std::forward<Args>(args)...);
			HZ_ASSERT(false);
		}
	}

}