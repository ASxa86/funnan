#pragma once

#include <box2d/b2_body.h>
#include <funnan/physics/Fixture.h>
#include <funnan/export.hxx>

namespace funnan
{
	class FUNNAN_EXPORT ComponentBody
	{
	public:
		enum class Type : int
		{
			Static,
			Kinematic,
			Dynamic
		};

		void addFixture(const Fixture& x);
		void removeFixture(const Fixture& x);
		void removeFixture(std::ptrdiff_t x);
		const std::vector<Fixture>& getFixtures();

		Vector position{};
		Vector linearVelocity{};
		double angularVelocity{};
		double angle{};
		bool awake{};
		bool enabled{};
		bool fixedRotation{};
		Type type{Type::Static};

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(ComponentBody, position, linearVelocity, angularVelocity, angle, awake, enabled, fixedRotation, type)

	private:
		friend class SystemPhysics;
		std::vector<Fixture> fixtures;
		b2Body* body{nullptr};
	};
}
