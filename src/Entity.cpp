#include <funnan/Entity.h>

using namespace funnan;

Entity::Entity(EntityID i, Scene* s) : id{i}, scene{s}
{
}

EntityID Entity::getID() const noexcept
{
	return this->id;
}

bool Entity::test() const
{
	return this->scene != nullptr && this->scene->test(this->id);
}

bool Entity::hasComponent(std::string_view x) const
{
	const auto pool = this->scene->getPool(x);

	if(pool != nullptr)
	{
		return pool->test(this->id);
	}

	return {};
}

std::any Entity::addComponent(std::string_view x)
{
	const auto pool = this->scene->getPool(x);

	if(pool != nullptr)
	{
		return pool->create(this->id);
	}

	return {};
}

std::any Entity::getComponent(std::string_view x)
{
	return this->scene->getPool(x)->get(this->id);
}

void Entity::removeComponent(std::string_view x)
{
	this->scene->getPool(x)->destroy(this->id);
}
