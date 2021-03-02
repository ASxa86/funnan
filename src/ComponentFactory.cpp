#include <funnan/ComponentFactory.h>

using namespace funnan;

std::unique_ptr<BasePool> ComponentFactory::create(std::string_view x) const
{
	const auto foundIt = std::find_if(std::begin(this->factory), std::end(this->factory), [x](const auto& pair) { return pair.first.name == x; });

	if(foundIt != std::end(this->factory))
	{
		return foundIt->second->create();
	}

	return nullptr;
}

std::unique_ptr<BasePool> ComponentFactory::create(const std::type_info& x) const
{
	const auto foundIt = std::find_if(std::begin(this->factory), std::end(this->factory), [&x](const auto& pair) { return pair.first.type == x; });

	if(foundIt != std::end(this->factory))
	{
		return foundIt->second->create();
	}

	return nullptr;
}

const TypeInfo* ComponentFactory::getTypeInfo(const std::type_info& x) const
{
	const auto foundIt = std::find_if(std::begin(this->factory), std::end(this->factory), [&x](const auto& pair) { return pair.first.type == x; });

	if(foundIt != std::end(this->factory))
	{
		return &foundIt->first;
	}

	return nullptr;
}

const TypeInfo* ComponentFactory::getTypeInfo(std::string_view x) const
{
	const auto foundIt = std::find_if(std::begin(this->factory), std::end(this->factory), [x](const auto& pair) { return pair.first.name == x; });

	if(foundIt != std::end(this->factory))
	{
		return &foundIt->first;
	}

	return nullptr;
}
