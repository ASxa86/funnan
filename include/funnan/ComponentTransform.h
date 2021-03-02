#pragma once

#include <funnan/Vector.h>
#include <nlohmann/json.hpp>

namespace funnan
{
	struct ComponentTransform
	{
		auto operator<=>(const ComponentTransform&) const = default;
		Vector position{};
		double angle{};

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(ComponentTransform, position, angle)
	};
}
