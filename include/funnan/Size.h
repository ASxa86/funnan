#pragma once

#include <compare>

namespace funnan
{
	struct Size
	{
		auto operator<=>(const Size&) const = default;
		double width{};
		double height{};
	};
}
