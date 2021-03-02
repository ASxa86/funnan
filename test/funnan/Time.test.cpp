#include <funnan/Time.h>
#include <gtest/gtest.h>

using namespace std::chrono_literals;

TEST(Time, nanoseconds)
{
	constexpr auto nanoseconds = 1000000000ns;
	constexpr auto microseconds = 1000000us;
	constexpr auto milliseconds = 1000ms;
	constexpr auto seconds = 1.0s;

	funnan::Time time(nanoseconds);
	EXPECT_EQ(time.toNanoseconds(), nanoseconds);
	EXPECT_EQ(time.toMicroseconds(), microseconds);
	EXPECT_EQ(time.toMilliseconds(), milliseconds);
	EXPECT_EQ(time.toSeconds(), seconds);
}

TEST(Time, microseconds)
{
	constexpr auto nanoseconds = 1000000000ns;
	constexpr auto microseconds = 1000000us;
	constexpr auto milliseconds = 1000ms;
	constexpr auto seconds = 1.0s;

	funnan::Time time(microseconds);
	EXPECT_EQ(time.toNanoseconds(), nanoseconds);
	EXPECT_EQ(time.toMicroseconds(), microseconds);
	EXPECT_EQ(time.toMilliseconds(), milliseconds);
	EXPECT_EQ(time.toSeconds(), seconds);
}

TEST(Time, milliseconds)
{
	constexpr auto nanoseconds = 1000000000ns;
	constexpr auto microseconds = 1000000us;
	constexpr auto milliseconds = 1000ms;
	constexpr auto seconds = 1.0s;

	funnan::Time time(milliseconds);
	EXPECT_EQ(time.toNanoseconds(), nanoseconds);
	EXPECT_EQ(time.toMicroseconds(), microseconds);
	EXPECT_EQ(time.toMilliseconds(), milliseconds);
	EXPECT_EQ(time.toSeconds(), seconds);
}

TEST(Time, seconds)
{
	constexpr auto nanoseconds = 1000000000ns;
	constexpr auto microseconds = 1000000us;
	constexpr auto milliseconds = 1000ms;
	constexpr auto seconds = 1.0s;

	funnan::Time time(seconds);
	EXPECT_EQ(time.toNanoseconds(), nanoseconds);
	EXPECT_EQ(time.toMicroseconds(), microseconds);
	EXPECT_EQ(time.toMilliseconds(), milliseconds);
	EXPECT_EQ(time.toSeconds(), seconds);
}
