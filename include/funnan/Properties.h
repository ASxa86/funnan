#pragma once

#include <funnan/PropertyTemplateMember.h>
#include <funnan/PropertyTemplateMethod.h>
#include <funnan/Signal.h>

namespace funnan
{
	class FUNNAN_EXPORT Properties
	{
	public:
		Properties() = default;
		virtual ~Properties() = default;
		Properties(const Properties&) = delete;
		Properties(Properties&& x) noexcept = delete;
		Properties& operator=(const Properties&) = delete;
		Properties& operator=(Properties&&) noexcept = delete;

		template <typename T>
		void addProperty(std::string_view name, T& p)
		{
			this->properties.push_back(std::make_unique<PropertyTemplateMember<T>>(name, p));
		}

		template <typename T>
		void addProperty(std::string_view name, std::function<void(T)> writer, std::function<T()> reader)
		{
			this->properties.push_back(std::make_unique<PropertyTemplateMethod<T>>(name, std::move(writer), std::move(reader)));
		}

		template <typename Writer, typename Reader>
		void addProperty(std::string_view name, Writer writer, Reader reader)
		{
			using Type = decltype(reader());
			this->addProperty<Type>(name, std::move(writer), std::move(reader));
		}

		Property* getProperty(std::string_view name) const noexcept;

		const std::vector<std::unique_ptr<Property>>& getProperties() const noexcept;

		Signal<void()> signalSerialize;
		Signal<void()> signalDeserialize;

	private:
		std::vector<std::unique_ptr<Property>> properties;

	};
}
