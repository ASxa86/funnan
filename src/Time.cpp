#include <funnan/Time.h>

using namespace funnan;

Time::Time(Nanoseconds x) : nanoseconds{x}
{
}

Time::Time(Microseconds x) : nanoseconds{x}
{
}

Time::Time(Milliseconds x) : nanoseconds{x}
{
}

Time::Time(Seconds x) : nanoseconds{std::chrono::duration_cast<Nanoseconds>(x)}
{
}

Time::Nanoseconds Time::toNanoseconds() const
{
	return this->nanoseconds;
}

Time::Microseconds Time::toMicroseconds() const
{
	return std::chrono::duration_cast<Microseconds>(this->nanoseconds);
}

Time::Milliseconds Time::toMilliseconds() const
{
	return std::chrono::duration_cast<Milliseconds>(this->nanoseconds);
}

Time::Seconds Time::toSeconds() const
{
	return std::chrono::duration_cast<Seconds>(this->nanoseconds);
}
