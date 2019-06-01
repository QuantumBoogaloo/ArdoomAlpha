#pragma once

#include <float.h>

#include "Traits.h"

#define PI_LITERAL 3.14159265358979323846264338327950288419716939937510L
#define TAU_LITERAL 6.28318530717958647692528676655900576839433879875021L

namespace constants
{
	template<typename Type>	struct Pi;

	template<> struct Pi<float> { static constexpr float value = PI_LITERAL; };
	template<> struct Pi<double> { static constexpr double value = PI_LITERAL; };
	template<> struct Pi<long double> { static constexpr long double value = PI_LITERAL; };

	template<typename Type>	struct Tau;

	template<> struct Tau<float> { static constexpr float value = TAU_LITERAL; };
	template<> struct Tau<double> { static constexpr double value = TAU_LITERAL; };
	template<> struct Tau<long double> { static constexpr long double value = TAU_LITERAL; };

	template<typename Type> struct Epsilon;

	template<> struct Epsilon<float> { static constexpr float value = FLT_EPSILON; };
	template<> struct Epsilon<double> { static constexpr double value = DBL_EPSILON; };
	template<> struct Epsilon<long double> { static constexpr long double value = LDBL_EPSILON; };
}

#undef PI_LITERAL
#undef TAU_LITERAL