#pragma once

namespace funnan
{
	namespace math
	{
		// https://oeis.org/A000796
		constexpr auto Pi = 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798214f;

		constexpr auto Radians(float x)
		{
			return x * Pi / 180.0f;
		}

		constexpr auto Degrees(float x)
		{
			return x * 180.0f / Pi;
		}
	}
}
