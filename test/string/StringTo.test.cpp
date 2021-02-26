#include <funnan/string/StringTo.h>
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

TEST(StringTo, bool)
{
	{
		const std::string x = "true";
		EXPECT_EQ(true, funnan::string::StringTo<bool>(x));
	}

	{
		const std::string x = "false";
		EXPECT_EQ(false, funnan::string::StringTo<bool>(x));
	}
}

TEST(StringTo, int)
{
	const std::string x = "1";
	EXPECT_EQ(1, funnan::string::StringTo<int>(x));
}

TEST(StringTo, float)
{
	const std::string x = "1.0f";
	EXPECT_FLOAT_EQ(1.0f, funnan::string::StringTo<float>(x));
}

TEST(StringTo, double)
{
	const std::string x = "1.0";
	EXPECT_DOUBLE_EQ(1.0, funnan::string::StringTo<double>(x));
}

TEST(StringTo, enum)
{
	// const std::string x = "One"
	const std::string x = "0";
	EXPECT_EQ(TestEnum::One, funnan::string::StringTo<TestEnum>(x));
}

TEST(String, enumNested)
{
	// const std::string x = "One";
	const std::string x = "0";
	EXPECT_EQ(TestClass::TestEnum::One, funnan::string::StringTo<TestClass::TestEnum>(x));
}
