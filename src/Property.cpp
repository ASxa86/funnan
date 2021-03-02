#include <funnan/Property.h>

using namespace funnan;

Property::Property(std::string_view x) : name{x}
{
}

Property::~Property()
{
}

std::string_view Property::getName() const noexcept
{
	return this->name;
}
