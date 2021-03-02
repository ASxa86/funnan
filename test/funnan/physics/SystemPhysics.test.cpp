#include <funnan/ComponentFactory.h>
#include <funnan/physics/ComponentBody.h>
#include <funnan/physics/SystemPhysics.h>
#include <gtest/gtest.h>

using namespace funnan;

TEST(SystemPhysics, registerPool)
{
	ComponentFactory factory;
	factory.registerComponentPool<ComponentBody, SystemPhysics>();

	auto pool = factory.create("funnan::ComponentBody");
	ASSERT_TRUE(pool != nullptr);

	auto physics = dynamic_cast<SystemPhysics*>(pool.get());
	ASSERT_TRUE(physics != nullptr);

	auto& c = physics->createType(0);
	c.angle = 0.0;

	Fixture fixture;
	Fixture::Circle circle;
	circle.position = {5.0, 5.0};
	circle.radius = 10.0;
	fixture.shape = circle;
	fixture.sensor = true;
	c.addFixture(fixture);
	c.removeFixture(fixture);

	physics->destroy(0);
}