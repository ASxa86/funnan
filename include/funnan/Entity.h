#pragma once

#include <any>
#include <cstddef>
#include <funnan/export.hxx>
#include <limits>
#include <string_view>
#include <nlohmann/json.hpp>
#include <funnan/EntityID.h>

namespace funnan
{
	class Scene;

	class FUNNAN_EXPORT Entity
	{
	public:
		Entity(EntityID id = EntityNull, Scene* s = nullptr);

		EntityID getID() const noexcept;

		bool test() const;

		template <typename T>
		bool hasComponent() const;

		template <typename T, typename... Args>
		T& addComponent(Args... args);

		template <typename T>
		T& getComponent();

		template <typename T>
		void removeComponent();

		bool hasComponent(std::string_view x) const;
		std::any addComponent(std::string_view x);
		std::any getComponent(std::string_view x);
		void removeComponent(std::string_view x);

		friend void to_json(nlohmann::json& j, const funnan::Entity& x)
		{
			j = x.id;
		}

		friend void from_json(const nlohmann::json& j, funnan::Entity& x)
		{
			j.get_to(x.id);
		}

	private:
		friend class Scene;
		Scene* scene{nullptr};
		EntityID id{EntityNull};
	};
}

#include <funnan/Scene.h>

template <typename T>
bool funnan::Entity::hasComponent() const
{
	return this->scene->getPool<T>()->test(this->getID());
}

template <typename T, typename... Args>
T& funnan::Entity::addComponent(Args... args)
{
	return this->scene->getPool<T>()->createType(this->getID(), std::forward<Args>(args)...);
}

template <typename T>
T& funnan::Entity::getComponent()
{
	return (*this->scene->getPool<T>())[this->getID()];
}

template <typename T>
void funnan::Entity::removeComponent()
{
	this->scene->getPool<T>()->destroy(this->getID());
}
