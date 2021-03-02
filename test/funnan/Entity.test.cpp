#include <funnan/Entity.h>
#include <funnan/Scene.h>
#include <gtest/gtest.h>

namespace
{
	struct ComponentOne
	{
		int x{};
		NLOHMANN_DEFINE_TYPE_INTRUSIVE(ComponentOne, x)
	};

	struct ComponentTwo
	{
		float x{};
		NLOHMANN_DEFINE_TYPE_INTRUSIVE(ComponentTwo, x)
	};

	const auto TypeComponentOne = funnan::GetType<ComponentOne>();
	const auto TypeComponentTwo = funnan::GetType<ComponentTwo>();
}

TEST(Entity, create)
{
	funnan::ComponentFactory factory;
	funnan::Scene scene{factory};

	const auto entity = scene.create();
	EXPECT_TRUE(entity.test());
}

TEST(Entity, addComponentByType)
{
	funnan::ComponentFactory factory;
	funnan::Scene scene{factory};

	auto entity = scene.create();
	EXPECT_TRUE(entity.test());

	entity.addComponent<ComponentOne>();
	EXPECT_TRUE(entity.hasComponent<ComponentOne>());
	EXPECT_FALSE(entity.hasComponent<ComponentTwo>());
}

TEST(Entity, addComponentByName)
{
	funnan::ComponentFactory factory;
	factory.registerComponent<ComponentOne>();
	factory.registerComponent<ComponentTwo>();

	funnan::Scene scene{factory};
	auto entity = scene.create();
	EXPECT_TRUE(entity.test());

	entity.addComponent(TypeComponentOne.name);
	EXPECT_TRUE(entity.hasComponent(TypeComponentOne.name));
	EXPECT_FALSE(entity.hasComponent(TypeComponentTwo.name));
}

TEST(Entity, addComponentInit)
{
	funnan::ComponentFactory factory;
	funnan::Scene scene{factory};

	auto entity = scene.create();
	EXPECT_TRUE(entity.test());

	auto& one = entity.addComponent<ComponentOne>(std::numeric_limits<int>::max());
	EXPECT_EQ(one.x, std::numeric_limits<int>::max());

	auto& two = entity.addComponent<ComponentTwo>(std::numeric_limits<float>::max());
	EXPECT_EQ(two.x, std::numeric_limits<float>::max());
}

TEST(Entity, removeComponentByType)
{
	funnan::ComponentFactory factory;
	funnan::Scene scene{factory};
	auto entity = scene.create();
	entity.addComponent<ComponentOne>();
	EXPECT_TRUE(entity.hasComponent<ComponentOne>());

	entity.removeComponent<ComponentOne>();
	EXPECT_FALSE(entity.hasComponent<ComponentOne>());
}

TEST(Entity, removeComponentByName)
{
	funnan::ComponentFactory factory;
	factory.registerComponent<ComponentOne>();
	factory.registerComponent<ComponentTwo>();

	funnan::Scene scene{factory};
	auto entity = scene.create();
	entity.addComponent(TypeComponentOne.name);
	EXPECT_TRUE(entity.hasComponent(TypeComponentOne.name));

	entity.removeComponent(TypeComponentOne.name);
	EXPECT_FALSE(entity.hasComponent(TypeComponentOne.name));
}
