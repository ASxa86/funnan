#include <funnan/xml/Element.h>

using namespace funnan::xml;

Element::Element(std::string_view x) : name{x}
{
}

Element::~Element()
{
}

void Element::setName(std::string_view x)
{
	this->name = x;
}

std::string_view Element::getName() const noexcept
{
	return this->name;
}

void Element::setText(std::string_view /*x*/)
{
}

std::string_view Element::getText() const noexcept
{
	//return this->text;
	return {};
}

Element* Element::insertChild(std::ptrdiff_t index, std::unique_ptr<Element> child)
{
	child->parent = this;
	this->children.insert(std::begin(this->children) + index, std::move(child));
	return this->children.back().get();
}

Element* Element::addChild(std::unique_ptr<Element> x)
{
	return this->insertChild(this->children.size(), std::move(x));
}

Element* Element::addChild(std::string_view x)
{
	return this->addChild(std::make_unique<Element>(x));
}

std::unique_ptr<Element> Element::removeChild(std::ptrdiff_t x)
{
	auto element = std::move(this->children[x]);
	this->children.erase(std::begin(this->children) + x);
	element->parent = nullptr;
	return element;
}

Element* Element::getChild(std::string_view x) const noexcept
{
	return this->getChild([x](const auto& element) { return element->getName() == x; });
}

Element* Element::getParent() const noexcept
{
	return this->parent;
}

Element* Element::getRoot() const noexcept
{
	auto p = this->parent;

	if(p != nullptr)
	{
		while(p->getParent() != nullptr)
		{
			p = p->getParent();
		}
	}

	return p;
}

std::vector<Element*> Element::getChildren(std::string_view x) const noexcept
{
	return this->getChildren([x](const auto& element) { return element->getName() == x; });
}

const std::vector<std::unique_ptr<Element>>& Element::getChildren() const noexcept
{
	return this->children;
}

const std::vector<Attribute>& Element::getAttributes() const noexcept
{
	return this->attributes;
}
