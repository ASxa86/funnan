#include <funnan/physics/ComponentBody.h>

#include <box2d/b2_chain_shape.h>
#include <box2d/b2_circle_shape.h>
#include <box2d/b2_edge_shape.h>
#include <box2d/b2_polygon_shape.h>

using namespace funnan;

void ComponentBody::addFixture(const Fixture& x)
{
	if(this->body != nullptr)
	{
		this->fixtures.push_back(x);
		auto& f = this->fixtures.back();

		b2FixtureDef def{};
		def.density = x.density;
		def.friction = x.friction;
		def.isSensor = x.sensor;
		def.restitution = x.restitution;

		std::visit(overloaded{[this, &def, &f](const Fixture::Circle& x) {
								  b2CircleShape shape;
								  shape.m_p = {static_cast<float>(x.position.x), static_cast<float>(x.position.y)};
								  shape.m_radius = static_cast<float>(x.radius);
								  def.shape = &shape;
								  this->body->CreateFixture(&def);
							  },
							  [this, &def, &f](const Fixture::Rectangle& x) {
								  b2PolygonShape shape;
								  shape.SetAsBox(static_cast<float>(x.size.width), static_cast<float>(x.size.height));
								  shape.m_centroid.x = static_cast<float>(x.position.x);
								  shape.m_centroid.y = static_cast<float>(x.position.y);
								  def.shape = &shape;
								  f.fixture = this->body->CreateFixture(&def);
							  },
							  [this, &def, &f](const Fixture::Chain& x) {
								  b2ChainShape shape;

								  std::vector<b2Vec2> vertices;

								  for(const auto& vertex : x.vertices)
								  {
									  vertices.push_back({static_cast<float>(vertex.x), static_cast<float>(vertex.y)});
								  }

								  shape.CreateLoop(vertices.data(), vertices.size());
								  def.shape = &shape;
								  f.fixture = this->body->CreateFixture(&def);
							  },
							  [this, &def, &f](const Fixture::Edge& x) {
								  b2EdgeShape shape;
								  funnan::Vector dv{0.0, 0.0};
								  b2Vec2 v0(static_cast<float>(x.vertex0.value_or(dv).x), static_cast<float>(x.vertex0.value_or(dv).y));
								  b2Vec2 v1(static_cast<float>(x.vertex1.x), static_cast<float>(x.vertex1.y));
								  b2Vec2 v2(static_cast<float>(x.vertex2.x), static_cast<float>(x.vertex2.y));
								  b2Vec2 v3(static_cast<float>(x.vertex3.value_or(dv).x), static_cast<float>(x.vertex3.value_or(dv).y));

								  shape.SetOneSided(v0, v1, v2, v3);
								  def.shape = &shape;
								  f.fixture = this->body->CreateFixture(&def);
							  },
							  [this, &def, &f](const Fixture::Polygon& x) {
								  b2PolygonShape shape;

								  std::vector<b2Vec2> vertices;

								  for(const auto& vertex : x.vertices)
								  {
									  vertices.push_back({static_cast<float>(vertex.x), static_cast<float>(vertex.y)});
								  }

								  shape.Set(vertices.data(), vertices.size());
								  def.shape = &shape;
								  f.fixture = this->body->CreateFixture(&def);
							  }},
				   x.shape);
	}
}

void ComponentBody::removeFixture(const Fixture& x)
{
	if(this->body != nullptr)
	{
		this->body->DestroyFixture(x.fixture);
		std::erase(this->fixtures, x);
	}
}

void ComponentBody::removeFixture(std::ptrdiff_t x)
{
	if(x > 0 && x < this->fixtures.size())
	{
		this->removeFixture(this->fixtures[x]);
	}
}

const std::vector<Fixture>& ComponentBody::getFixtures()
{
	return this->fixtures;
}
