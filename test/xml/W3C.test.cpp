#include <funnan/xml/Document.h>
#include <gtest/gtest.h>

using namespace funnan::xml;

namespace
{
	constexpr std::string_view XMLTestFile{XMLTEST_FILE};
	const std::filesystem::path XMLTestFilePath{XMLTestFile};
}

TEST(W3C, node)
{
	constexpr std::string_view xml{R"(<TEST TYPE = "not-wf" ENTITIES="none" ID="not-wf-sa-160"
		URI="not-wf/sa/160.xml" SECTIONS="2.8">Violates the <EM>PEs in Internal Subset</EM> WFC
		by using a PE reference within a declaration. </TEST>)"};
}

///
/// https://www.w3.org/XML/Test/
///
/// Test the funnan::xml API conformance with W3C XML Standard.
///
TEST(W3C, conformance)
{
	Document doc;
	doc.load(XMLTestFilePath);

	auto testcase = doc.getChild("TESTCASES");

	if(testcase != nullptr)
	{
		std::cout << testcase->getChildren("TEST").size() << "\n";
	}
}
