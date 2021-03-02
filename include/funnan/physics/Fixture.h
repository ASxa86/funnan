#pragma once

#include <box2d/b2_fixture.h>
#include <funnan/Size.h>
#include <funnan/Vector.h>
#include <array>
#include <optional>
#include <variant>
#include <vector>

namespace funnan
{
	template <class... Ts>
	struct overloaded : Ts...
	{
		using Ts::operator()...;
	};

	template <class... Ts>
	overloaded(Ts...) -> overloaded<Ts...>;

	///
	///	\class Fixture
	///
	/// A fixture is used to attach a shape to a body for collision detection. A fixture
	/// inherits its transform from its parent. Fixtures hold additional non-geometric data
	/// such as friction, collision filters, etc.
	///
	class Fixture
	{
	public:
		struct Circle
		{
			auto operator<=>(const Circle&) const = default;
			Vector position{};
			double radius{};
		};

		struct Rectangle
		{
			auto operator<=>(const Rectangle&) const = default;
			Vector position{};
			Size size{};
		};

		struct Edge
		{
			auto operator<=>(const Edge&) const = default;
			Vector vertex1;
			Vector vertex2;
			std::optional<Vector> vertex0;
			std::optional<Vector> vertex3;
		};

		struct Chain
		{
			auto operator<=>(const Chain&) const = default;
			std::vector<Vector> vertices;
		};

		struct Polygon
		{
			auto operator<=>(const Polygon&) const = default;
			static constexpr auto MaxVertices{8};
			std::array<Vector, MaxVertices> vertices{};
			std::array<Vector, MaxVertices> normals{};
			Vector position{};
		};

		auto operator<=>(const Fixture&) const = default;
		bool operator==(const Fixture& x) const;

		///
		///
		///
		std::variant<Circle, Rectangle, Edge, Chain, Polygon> shape;

		///
		///	Restitution is used to make objects bounce.The restitution value is usually set to be between 0 and 1.
		///	Consider dropping a ball on a table.A value of zero means the ball won't bounce. This is called an
		///	inelastic collision. A value of one means the ball's velocity will be exactly reflected.
		///
		double restitution{};

		///
		///	Friction is used to make objects slide along each other realistically.Box2D supports static and dynamic
		///	friction, but uses the same parameter for both.Friction is simulated accurately in Box2D and the friction
		///	strength is proportional to the normal force(this is called Coulomb friction).The friction parameter is
		///	usually set between 0 and 1, but can be any non - negative value.A friction value of 0 turns off friction
		///	and a value of 1 makes the friction strong.
		///
		double friction{};

		///
		///	The fixture density is used to compute the mass properties of the parent body. The density can be zero
		///	or positive. You should generally use similar densities for all your fixtures.This will improve stacking
		///	stability.
		///
		double density{};

		///
		///	Sometimes game logic needs to know when two fixtures overlap yet there should be no collision
		///	response. This is done by using sensors. A sensor is a fixture that detects collision but does not produce
		///	a response.
		///
		bool sensor{false};

	private:
		friend class ComponentBody;
		b2Fixture* fixture{nullptr};
	};
}
