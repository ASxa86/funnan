#include <funnan/ComponentFactory.h>
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
		int x{};
		NLOHMANN_DEFINE_TYPE_INTRUSIVE(ComponentTwo, x)
	};
}

TEST(Scene, each)
{
	funnan::ComponentFactory factory;
	funnan::Scene scene{factory};

	for (auto i = 0; i < 10; i++)
	{
		auto e = scene.create();
		e.addComponent<ComponentOne>();
		e.addComponent<ComponentTwo>();
	}
}
