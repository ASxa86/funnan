#include <funnan/physics/Fixture.h>

using namespace funnan;

bool Fixture::operator==(const Fixture& x) const
{
	return this->density == x.density && this->friction == x.friction && this->restitution == x.restitution && this->sensor == x.sensor
		   && this->shape == x.shape;
}
