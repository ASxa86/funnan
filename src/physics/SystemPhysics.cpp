#include <funnan/ComponentTransform.h>
#include <funnan/Scene.h>
#include <funnan/physics/SystemPhysics.h>

using namespace funnan;

namespace funnan
{
	b2Vec2 Vec2Vec(const Vector& x)
	{
		return {static_cast<float>(x.x), static_cast<float>(x.y)};
	}

	Vector Vec2Vec(const b2Vec2& x)
	{
		return {x.x, x.y};
	}
}

SystemPhysics::SystemPhysics() : world({0.0, 0.0})
{
	this->signalComponentAdd.connect([this](auto id, auto& c) { this->onComponentAdd(id, c); });
	this->signalComponentRemove.connect([this](auto id, auto& c) { this->onComponentRemove(id, c); });
}

void SystemPhysics::fixed(Time x, Scene& scene)
{
	for(const auto id : *this)
	{
		auto& c = (*this)[id];

		// A quick way to only check entities with components we care about vs having to loop over every entity in the scene.
		auto e = scene.get(id);
		if(e.hasComponent<ComponentTransform>() == true)
		{
			auto& t = e.getComponent<ComponentTransform>();
			c.body->SetTransform({static_cast<float>(t.position.x), static_cast<float>(t.position.y)}, static_cast<float>(t.angle));
		}

		c.body->SetLinearVelocity(Vec2Vec(c.linearVelocity));
		c.body->SetFixedRotation(c.fixedRotation);
	}

	this->world.Step(static_cast<float>(x.toSeconds().count()), 2, 8);

	for(const auto id : *this)
	{
		auto& c = (*this)[id];

		auto e = scene.get(id);
		if(e.hasComponent<ComponentTransform>() == true)
		{
			auto& t = e.getComponent<ComponentTransform>();
			t.position = Vec2Vec(c.body->GetTransform().p);
			t.angle = c.body->GetTransform().q.GetAngle();
		}

		c.linearVelocity = Vec2Vec(c.body->GetLinearVelocity());
		c.fixedRotation = c.body->IsFixedRotation();
	}
}

void SystemPhysics::onComponentAdd(EntityID, ComponentBody& x)
{
	b2BodyDef def{};
	def.type = static_cast<b2BodyType>(x.type);
	def.angle = static_cast<float>(x.angle);
	def.position = Vec2Vec(x.position);

	auto body = this->world.CreateBody(&def);
	x.body = body;
}

void SystemPhysics::onComponentRemove(EntityID, ComponentBody& x)
{
	this->world.DestroyBody(x.body);
}
