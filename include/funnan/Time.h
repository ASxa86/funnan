#pragma once

#include <funnan/export.hxx>
#include <chrono>

namespace funnan
{
	class FUNNAN_EXPORT Time
	{
	public:
		using Nanoseconds = std::chrono::nanoseconds;
		using Microseconds = std::chrono::microseconds;
		using Milliseconds = std::chrono::milliseconds;
		using Seconds = std::chrono::duration<double>;

		Time(Nanoseconds x);
		Time(Microseconds x);
		Time(Milliseconds x);
		Time(Seconds x);

		Nanoseconds toNanoseconds() const;
		Microseconds toMicroseconds() const;
		Milliseconds toMilliseconds() const;
		Seconds toSeconds() const;

	private:
		Nanoseconds nanoseconds{};
	};
}
