#include <funnan/xml/Element.h>
#include <gtest/gtest.h>

using namespace funnan::xml;

namespace
{
	constexpr std::string_view ElementName{"name"};
}

TEST(Element, addChildByElement)
{
	Element parent;
	auto element = parent.addChild(std::make_unique<Element>());
	EXPECT_TRUE(element != nullptr);
	EXPECT_TRUE(element->getName().empty());
	EXPECT_TRUE(element->getText().empty());
}

TEST(Element, addChildByName)
{
	Element parent;
	auto element = parent.addChild(ElementName);
	EXPECT_TRUE(element != nullptr);
	EXPECT_EQ(element->getName(), ElementName);
	EXPECT_TRUE(element->getText().empty());
}

TEST(Element, getChild)
{
	Element parent;
	const auto child0 = parent.addChild("name0");
	EXPECT_TRUE(child0 != nullptr);

	const auto child1 = parent.addChild("name1");
	EXPECT_TRUE(child1 != nullptr);

	const auto child2 = parent.addChild("name2");
	EXPECT_TRUE(child2 != nullptr);

	const auto child3 = parent.addChild("name3");
	EXPECT_TRUE(child3 != nullptr);

	const auto child4 = parent.addChild("name4");
	EXPECT_TRUE(child4 != nullptr);

	EXPECT_EQ(parent.getChild([c = child0](const auto& x) { return x->getName() == c->getName(); }), child0);
	EXPECT_EQ(parent.getChild([c = child1](const auto& x) { return x->getName() == c->getName(); }), child1);
	EXPECT_EQ(parent.getChild([c = child2](const auto& x) { return x->getName() == c->getName(); }), child2);
	EXPECT_EQ(parent.getChild([c = child3](const auto& x) { return x->getName() == c->getName(); }), child3);
	EXPECT_EQ(parent.getChild([c = child4](const auto& x) { return x->getName() == c->getName(); }), child4);
}