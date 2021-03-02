#pragma once

#include <funnan/export.hxx>
#include <funnan/ComponentPool.h>
#include <funnan/physics/ComponentBody.h>

#include <box2d/b2_world.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_body.h>
#include <unordered_map>

namespace funnan
{
	class FUNNAN_EXPORT SystemPhysics : public ComponentPool<ComponentBody>
	{
	public:
		SystemPhysics();

		void fixed(Time x, Scene& scene) override;

	private:
		void onComponentAdd(EntityID id, ComponentBody& x);
		void onComponentRemove(EntityID id, ComponentBody& x);

		std::unordered_map<EntityID, b2Body*> bodies;
		std::unordered_map<decltype(ComponentBody::fixtures)::size_type, b2Fixture*> fixtures;
		b2World world;
	};
}