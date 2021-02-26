#include <funnan/string/ToString.h>
#include <gtest/gtest.h>

namespace
{
	enum class TestEnum : int
	{
		One,
		Two,
		Three
	};

	struct TestClass
	{
		enum class TestEnum : int
		{
			One,
			Two,
			Three,
			Four
		};
	};
}

TEST(ToString, bool)
{
	{
		constexpr bool x = true;
		EXPECT_EQ("true", funnan::string::ToString(x));
	}

	{
		constexpr bool x = false;
		EXPECT_EQ("false", funnan::string::ToString(x));
	}
}

TEST(ToString, int)
{
	constexpr int x = 1;
	EXPECT_EQ("1", funnan::string::ToString(x));
}

TEST(ToString, float)
{
	constexpr float x = 1.0f;
	EXPECT_EQ("1.0000000", funnan::string::ToString(x));
}

TEST(ToString, double)
{
	constexpr double x = 1.0;
	EXPECT_EQ("1.0000000000000000", funnan::string::ToString(x));
}

TEST(ToString, enum)
{
	constexpr TestEnum x = TestEnum::One;
	// EXPECT_EQ("One", funnan::string::ToString(x));
	EXPECT_EQ("0", funnan::string::ToString(x));
}

TEST(ToString, enumNested)
{
	constexpr TestClass::TestEnum x = TestClass::TestEnum::One;
	// EXPECT_EQ("One", funnan::string::ToString(x));
	EXPECT_EQ("0", funnan::string::ToString(x));
}
