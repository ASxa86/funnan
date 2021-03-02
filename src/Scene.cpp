#include <funnan/Scene.h>
#include <nlohmann/json.hpp>

using namespace funnan;

Scene::Scene(const ComponentFactory& x) : Properties(), factory{x}
{
	// Initialize all loaded entities with the scene's pointer.
	this->addProperty(
		"entities",
		[this](const auto& x) {
			this->entities = x;

			for(auto& e : this->entities)
			{
				e.scene = this;
			}
		},
		[this] { return this->entities; });
	this->addProperty("destroyed", this->destroyed);
}

Entity Scene::create()
{
	Entity e{EntityNull, this};

	if(this->destroyed.empty() == true)
	{
		e.id = this->entities.size();
		e.scene = this;
		this->entities.push_back(e);
	}
	else
	{
		e = this->destroyed.back();
		e.scene = this;
		this->entities[e.getID()] = e;
		this->destroyed.pop_back();
	}

	return e;
}

void Scene::destroy(Entity x)
{
	if(this->test(x) == true)
	{
		// Copy the destroyed entity with a valid id and pointer to manage before invalidating it.
		// This makes it possible to recover the entity on creation.
		this->destroyed.push_back(x);

		for(auto& pool : this->pools)
		{
			if(pool->test(x.getID()) == true)
			{
				pool->destroy(x.getID());
			}
		}

		// Invalidate the entity within the entity pool.
		this->entities[x.getID()].id = EntityNull;
		this->entities[x.getID()].scene = nullptr;
	}
}

bool Scene::test(Entity x) const
{
	return x.getID() < this->entities.size() && this->entities[x.getID()].getID() == x.getID();
}

Entity Scene::get(EntityID x) const
{
	const auto foundIt = std::find_if(std::begin(this->entities), std::end(this->entities), [x](auto e) { return e.getID() == x; });

	if(foundIt != std::end(this->entities))
	{
		return *foundIt;
	}

	return {};
}

bool Scene::empty() const
{
	return this->entities.empty();
}

std::size_t Scene::size() const
{
	return this->entities.size();
}

const std::vector<Entity>& Scene::collect() const
{
	return this->entities;
}

const std::vector<std::unique_ptr<BasePool>>& Scene::getPools() const
{
	return this->pools;
}

BasePool* Scene::getPool(std::string_view x)
{
	BasePool* pool{};

	const auto foundPool =
		std::find_if(std::begin(this->pools), std::end(this->pools), [x](const auto& pool) { return pool->getComponentType().name == x; });

	if(foundPool != std::end(this->pools))
	{
		pool = (*foundPool).get();
	}
	else
	{
		auto newPool = this->factory.create(x);

		if(newPool != nullptr)
		{
			this->pools.push_back(std::move(newPool));
			pool = this->pools.back().get();
		}
	}

	return pool;
}
