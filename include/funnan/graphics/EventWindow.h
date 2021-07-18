#pragma once

#include <chrono>

namespace funnan
{
	namespace graphics
	{
		struct EventWindow
		{
			enum class Type : uint8_t
			{
				Unknown,
				Closed,
				Resized,
				Moved
			};

			const std::chrono::system_clock::time_point timestamp{std::chrono::system_clock::now()};
			Type type{};
			int x{};
			int y{};
			int width{};
			int height{};
		};
	}
}
