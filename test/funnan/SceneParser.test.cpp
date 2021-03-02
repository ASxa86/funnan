#include <funnan/ComponentFactory.h>
#include <funnan/Entity.h>
#include <funnan/Scene.h>
#include <funnan/SceneParser.h>
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
}

TEST(SceneParaser, write_read)
{
	const auto file = std::filesystem::path("scene.xml");
	constexpr auto testC1{1};
	constexpr auto testC2{1.0f};

	funnan::ComponentFactory factory;
	factory.registerComponent<ComponentOne>();
	factory.registerComponent<ComponentTwo>();

	funnan::Scene sceneWrite{factory};

	auto e = sceneWrite.create();

	{
		auto& ec1 = e.addComponent<ComponentOne>(testC1);
		auto& ec2 = e.addComponent<ComponentTwo>(testC2);

		funnan::SceneParser parser{sceneWrite};
		parser.writeFile(file);
		ASSERT_TRUE(std::filesystem::exists(file));
	}

	funnan::Scene sceneLoad{factory};

	{
		funnan::SceneParser parser{sceneLoad};
		parser.loadFile(file);
	}

	auto eLoad = sceneLoad.get(e.getID());
	EXPECT_TRUE(eLoad.test());
	ASSERT_TRUE(eLoad.hasComponent<ComponentOne>());
	ASSERT_TRUE(eLoad.hasComponent<ComponentTwo>());

	auto& c1 = eLoad.getComponent<ComponentOne>();
	auto& c2 = eLoad.getComponent<ComponentTwo>();
	EXPECT_EQ(c1.x, testC1);
	EXPECT_EQ(c2.x, testC2);

	EXPECT_TRUE(std::filesystem::remove(file));
}
