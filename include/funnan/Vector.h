#pragma once

#include <compare>
#include <nlohmann/json.hpp>

namespace funnan
{
	struct Vector
	{
		auto operator<=>(const Vector&) const = default;
		double x{};
		double y{};

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(Vector, x, y)
	};
}
