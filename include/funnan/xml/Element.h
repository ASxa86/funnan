#pragma once

#include <funnan/xml/Attribute.h>
#include <algorithm>
#include <concepts>
#include <funnan/xml/export.hxx>
#include <memory>
#include <string_view>
#include <vector>

namespace funnan
{
	namespace xml
	{
		class FUNNAN_XML_EXPORT Element
		{
		public:
			Element() = default;
			Element(std::string_view x);
			virtual ~Element();
			Element(Element&&) noexcept = default;
			Element& operator=(Element&&) noexcept = default;
			Element(const Element&) = delete;
			Element& operator=(const Element&) = delete;

			void setName(std::string_view x);
			std::string_view getName() const noexcept;

			void setText(std::string_view x);
			std::string_view getText() const noexcept;

			Element* addChild(std::unique_ptr<Element> x);
			Element* addChild(std::string_view x);
			Element* insertChild(std::ptrdiff_t index, std::unique_ptr<Element> child);
			std::unique_ptr<Element> removeChild(std::ptrdiff_t x);

			template <typename T>
			Element* getChild(T x) const noexcept requires std::predicate<T, const std::unique_ptr<Element>&>
			{
				const auto foundIt = std::ranges::find_if(this->children, x);

				if(foundIt != std::end(this->children))
				{
					return foundIt->get();
				}

				return nullptr;
			}

			Element* getChild(std::string_view x) const noexcept;

			Element* getParent() const noexcept;
			Element* getRoot() const noexcept;

			template <typename T>
			std::vector<Element*> getChildren(T x) const noexcept requires std::predicate<T, const std::unique_ptr<Element>&>
			{
				std::vector<Element*> v;
				v.reserve(this->children.size());

				for(const auto& child : this->children)
				{
					if(x(child) == true)
					{
						v.push_back(child.get());
					}
				}

				return v;
			}

			std::vector<Element*> getChildren(std::string_view x) const noexcept;
			const std::vector<std::unique_ptr<Element>>& getChildren() const noexcept;
			const std::vector<Attribute>& getAttributes() const noexcept;

		private:
			std::vector<std::unique_ptr<Element>> children;
			std::vector<Attribute> attributes;
			std::string name;
			Element* parent{nullptr};
		};
	}
}