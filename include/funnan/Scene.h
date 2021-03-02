#pragma once

#include <funnan/ComponentFactory.h>
#include <funnan/ComponentPool.h>
#include <funnan/Properties.h>
#include <funnan/export.hxx>

namespace funnan
{
	class Entity;

	class FUNNAN_EXPORT Scene : public Properties
	{
	public:
		Scene(const ComponentFactory& x);

		Entity create();
		void destroy(Entity x);
		bool test(Entity x) const;
		Entity get(EntityID x) const;
		const std::vector<Entity>& collect() const;
		bool empty() const;
		std::size_t size() const;

		template <typename... Args>
		void each(typename std::type_identity<std::function<void(Entity, Args&...)>>::type f);

		template <typename T>
		auto getPool()
		{
			ComponentPool<T>* pool{};

			for(const auto& basePool : this->pools)
			{
				pool = dynamic_cast<ComponentPool<T>*>(basePool.get());

				if(pool != nullptr)
				{
					break;
				}
			}

			if(pool == nullptr)
			{
				auto newPool = std::make_unique<ComponentPool<T>>();
				pool = newPool.get();
				this->pools.push_back(std::move(newPool));
			}

			return pool;
		}

		BasePool* getPool(std::string_view x);

		const std::vector<std::unique_ptr<BasePool>>& getPools() const;

	private:
		std::vector<std::unique_ptr<BasePool>> pools;
		std::vector<Entity> entities;
		std::vector<Entity> destroyed;
		const ComponentFactory& factory;
	};
}

#include <funnan/Entity.h>

template <typename... Args>
void funnan::Scene::each(typename std::type_identity<std::function<void(Entity, Args&...)>>::type f)
{
	const auto tuple = std::make_tuple(this->template getPool<Args>()...);

	std::apply(
		[this, &f](auto... pool) {
			for(auto e : this->entities)
			{
				const auto valid = (pool->test(e) && ...);

				if(valid == true)
				{
					f(e, (*pool)[e]...);
				}
			}
		},
		tuple);
}
