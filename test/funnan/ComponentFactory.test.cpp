#include <funnan/ComponentFactory.h>
#include <gtest/gtest.h>

namespace
{
	struct Component
	{
		int x{};
		NLOHMANN_DEFINE_TYPE_INTRUSIVE(Component, x)
	};

	struct CustomPool : public funnan::ComponentPool<Component>
	{
	};
}

TEST(ComponentFactory, register)
{
	funnan::ComponentFactory factory;
	factory.registerComponentPool<Component, CustomPool>();
	auto pool = factory.create("Component");
	ASSERT_TRUE(pool != nullptr);

	EXPECT_EQ(pool->getComponentType(), funnan::GetType<Component>());
	EXPECT_TRUE(dynamic_cast<CustomPool*>(pool.get()) != nullptr);
}
