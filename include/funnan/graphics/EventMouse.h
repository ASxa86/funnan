#pragma once

#include <chrono>

namespace funnan
{
	namespace graphics
	{
		struct EventMouse final
		{
			enum class Type : uint8_t
			{
				Unknown,
				Moved,
				ButtonLeftPressed,
				ButtonLeftReleased,
				ButtonMiddlePressed,
				ButtonMiddleReleased,
				ButtonRightPressed,
				ButtonRightReleased,
				WheelDown,
				WheelUp,
				WheelLeft,
				WheelRight
			};

			const std::chrono::system_clock::time_point timestamp{std::chrono::system_clock::now()};
			int x{};
			int y{};
			Type type{};
		};
	}
}
