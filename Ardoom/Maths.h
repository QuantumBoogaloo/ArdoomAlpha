#pragma once

// Include intmax_t
#include <stdint.h>

#if defined(abs)
#undef abs
#endif

namespace maths
{
	//
	// abs
	//

	constexpr int abs(int value)
	{
		return (value < 0) ? -value : value;
	}

	constexpr long abs(long value)
	{
		return (value < 0) ? -value : value;
	}

	constexpr long long abs(long long value)
	{
		return (value < 0) ? -value : value;
	}

	//
	// lerp
	//

	constexpr float lerp(float low, float high, float factor)
	{
		return (((1 - factor) * low) + (factor * high));
	}

	constexpr double lerp(double low, double high, double factor)
	{
		return (((1 - factor) * low) + (factor * high));
	}

	constexpr long double lerp(long double low, long double high, long double factor)
	{
		return (((1 - factor) * low) + (factor * high));
	}

	//
	// inverseLerp
	//

	constexpr float inverseLerp(float first, float second, float factor) noexcept
	{
		return ((factor - first) / (second - first));
	}

	constexpr double inverseLerp(double first, double second, double factor) noexcept
	{
		return ((factor - first) / (second - first));
	}

	constexpr long double inverseLerp(long double first, long double second, long double factor) noexcept
	{
		return ((factor - first) / (second - first));
	}

	//
	// map
	//

	constexpr float map(float from, float fromLow, float fromHigh, float toLow, float toHigh) noexcept
	{
		return (toLow + (from - fromLow) * ((toHigh - toLow) / (fromHigh - fromLow)));
	}

	constexpr double map(double from, double fromLow, double fromHigh, double toLow, double toHigh) noexcept
	{
		return (toLow + (from - fromLow) * ((toHigh - toLow) / (fromHigh - fromLow)));
	}

	constexpr long double map(long double from, long double fromLow, long double fromHigh, long double toLow, long double toHigh) noexcept
	{
		return (toLow + (from - fromLow) * ((toHigh - toLow) / (fromHigh - fromLow)));
	}
}