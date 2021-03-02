#pragma once

#include <funnan/EntityID.h>
#include <funnan/Properties.h>
#include <funnan/System.h>
#include <funnan/TypeInfo.h>
#include <any>

namespace funnan
{
	class BasePool : public Properties, public System
	{
	public:
		virtual std::any create(EntityID x) = 0;
		virtual void destroy(EntityID x) = 0;
		virtual bool test(EntityID x) const = 0;
		virtual std::any get(EntityID x) = 0;
		virtual TypeInfo getComponentType() const = 0;
		virtual bool empty() const = 0;
		virtual std::size_t size() const = 0;
	};

	template <typename T>
	class ComponentPool : public BasePool
	{
	public:
		ComponentPool()
		{
			this->addProperty("pool", this->pool);
			this->addProperty("indices", this->indices);
			this->addProperty("direct", this->direct);

			// Upon deserialization, provide any additional component initialization as necessary.
			this->signalDeserialize.connect([this] {
				for(auto index : this->indices)
				{
					if(this->test(index) == true)
					{
						this->signalComponentAdd.notify(index, this->pool[index]);
					}
				}
			});
		}

		~ComponentPool() override
		{
			for(auto index : this->indices)
			{
				if(this->test(index) == true)
				{
					this->signalComponentRemove.notify(index, this->pool[index]);
				}
			}
		}

		std::any create(EntityID x) override
		{
			return &this->createType(x);
		}

		template <typename... Args>
		T& createType(EntityID x, Args&&... args)
		{
			if(x >= this->indices.size())
			{
				this->indices.resize(static_cast<typename decltype(this->indices)::size_type>(x) + 1, EntityNull);
			}

			this->pool.emplace_back(std::forward<Args>(args)...);
			this->indices[x] = this->pool.size() - 1;
			this->direct.push_back(x);
			this->signalComponentAdd.notify(x, this->pool.back());
			return this->pool.back();
		}

		void destroy(EntityID x) override
		{
			// For a more efficient removal. Let's move the last element into place of the element
			// we are removing and then pop the last element off as it has been invalidated.
			auto& component = (*this)[x];
			this->signalComponentRemove.notify(x, component);
			component = std::move(this->pool.back());
			this->pool.pop_back();

			const auto back = this->direct.back();
			auto& candidate = this->indices[x];
			this->indices[back] = candidate;
			this->direct[candidate] = back;
			candidate = EntityNull;
			this->direct.pop_back();
		}

		bool test(EntityID x) const override
		{
			return x < this->indices.size() && this->indices[x] != EntityNull;
		}

		std::any get(EntityID x) override
		{
			return &(*this)[x];
		}

		T& operator[](EntityID x)
		{
			return this->pool[this->indices[x]];
		}

		TypeInfo getComponentType() const override
		{
			return GetType<T>();
		}

		bool empty() const override
		{
			return this->pool.empty();
		}

		std::size_t size() const override
		{
			return this->pool.size();
		}

		auto begin()
		{
			return std::begin(this->direct);
		}

		const auto begin() const
		{
			return std::begin(this->direct);
		}

		auto end()
		{
			return std::end(this->direct);
		}

		const auto end() const
		{
			return std::end(this->direct);
		}

	protected:
		Signal<void(EntityID, T&)> signalComponentAdd;
		Signal<void(EntityID, T&)> signalComponentRemove;

	private:
		std::vector<T> pool;
		std::vector<EntityID> indices;
		std::vector<EntityID> direct;
	};
}
