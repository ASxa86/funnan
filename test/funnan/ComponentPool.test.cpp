#include <funnan/ComponentPool.h>
#include <gtest/gtest.h>

namespace
{
	struct Component
	{
		int x{};

		// Required for successful compilation with property system.
		NLOHMANN_DEFINE_TYPE_INTRUSIVE(Component, x)
	};
}

TEST(ComponentPool, component)
{
	funnan::ComponentPool<Component> pool;
	EXPECT_TRUE(pool.empty());
	EXPECT_EQ(pool.size(), std::size_t{0});

	const auto type = pool.getComponentType();
	EXPECT_EQ(type, funnan::GetType<Component>());

	auto any = pool.create(0);
	ASSERT_TRUE(any.has_value());
	EXPECT_FALSE(pool.empty());
	EXPECT_EQ(pool.size(), std::size_t{1});

	auto c = std::any_cast<Component*>(any);
	ASSERT_TRUE(c != nullptr);
	EXPECT_EQ(c->x, 0);

	auto& c1 = pool.createType(1, 1);
	EXPECT_FALSE(pool.empty());
	EXPECT_EQ(pool.size(), std::size_t{2});
	EXPECT_EQ(c1.x, 1);

	EXPECT_NO_THROW(pool.destroy(0));
	EXPECT_FALSE(pool.empty());
	EXPECT_EQ(pool.size(), std::size_t{1});
	EXPECT_FALSE(pool.test(0));

	EXPECT_NO_THROW(c1 = pool[1]);
	EXPECT_EQ(c1.x, 1);
}
