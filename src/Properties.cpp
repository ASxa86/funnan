#include <funnan/Properties.h>
#include <algorithm>

using namespace funnan;

Property* Properties::getProperty(std::string_view name) const noexcept
{
	const auto foundIt = std::find_if(std::begin(this->properties), std::end(this->properties), [name](auto& p) { return p->getName() == name; });

	if(foundIt != std::end(this->properties))
	{
		return foundIt->get();
	}

	return nullptr;
}

const std::vector<std::unique_ptr<Property>>& Properties::getProperties() const noexcept
{
	return this->properties;
}
