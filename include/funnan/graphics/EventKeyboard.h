#pragma once

#include <chrono>

namespace funnan
{
	namespace graphics
	{
		struct EventKeyboard final
		{
			enum class Type : uint8_t
			{
				Unknown,
				KeyPressed,
				KeyReleased
			};

			enum class Key : uint8_t
			{
				Unknown,
				A,
				B,
				C,
				D,
				E,
				F,
				G,
				H,
				I,
				J,
				K,
				L,
				M,
				N,
				O,
				P,
				Q,
				R,
				S,
				T,
				U,
				V,
				W,
				X,
				Y,
				Z
			};

			const std::chrono::system_clock::time_point timestamp{std::chrono::system_clock::now()};
			Type type{};
			Key key{};
		};
	}
}
