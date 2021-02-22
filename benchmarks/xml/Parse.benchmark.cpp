#include <celero/Celero.h>
#include <pugixml.hpp>

#include <funnan/xml/Document.h>
#include <filesystem>
#include <fstream>

namespace
{
	constexpr std::string_view XMLTestFile{XMLTEST_FILE};
	const std::filesystem::path XMLTestFilePath{XMLTestFile};
}

BASELINE(Parse, fstream, 10, 100)
{
	std::string buffer;

	std::ifstream in(XMLTestFilePath);
	in.seekg(0, std::ios::end);
	buffer.resize(in.tellg());
	in.seekg(0, std::ios::beg);
	in.read(buffer.data(), buffer.size());
	in.close();
}

BENCHMARK(Parse, pugixml, 10, 100)
{
	pugi::xml_document doc;
	doc.load_file(XMLTestFile.data());
}

BENCHMARK(Parse, funnan, 10, 100)
{
	funnan::xml::Document doc;
	doc.load(XMLTestFilePath);
}
