#pragma once

#include <funnan/ComponentPool.h>
#include <funnan/TypeInfo.h>
#include <funnan/export.hxx>
#include <map>

namespace funnan
{
	namespace impl
	{
		struct CreatorBase
		{
			virtual std::unique_ptr<BasePool> create() = 0;
		};

		template <typename T>
		struct Creator : public CreatorBase
		{
			std::unique_ptr<BasePool> create() override
			{
				return std::make_unique<T>();
			}
		};
	}

	class FUNNAN_EXPORT ComponentFactory
	{
	public:
		ComponentFactory() = default;
		~ComponentFactory() = default;

		ComponentFactory(const ComponentFactory&) = delete;
		ComponentFactory(ComponentFactory&& x) noexcept = delete;
		ComponentFactory& operator=(const ComponentFactory&) = delete;
		ComponentFactory& operator=(ComponentFactory&&) noexcept = delete;

		template <typename T>
		void registerComponent()
		{
			TypeInfo t(typeid(T));
			this->factory[t] = std::make_unique<impl::Creator<ComponentPool<T>>>();
		}

		template <typename T, typename Pool>
		void registerComponentPool()
		{
			TypeInfo t(typeid(T));
			this->factory[t] = std::make_unique<impl::Creator<Pool>>();
		}

		std::unique_ptr<BasePool> create(std::string_view x) const;
		std::unique_ptr<BasePool> create(const std::type_info& x) const;

		const TypeInfo* getTypeInfo(const std::type_info& x) const;
		const TypeInfo* getTypeInfo(std::string_view x) const;

	private:
		std::map<TypeInfo, std::unique_ptr<impl::CreatorBase>> factory;
	};
}