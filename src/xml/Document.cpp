#include <funnan/xml/Document.h>
#include <fstream>

using namespace funnan::xml;

void Document::load(const std::filesystem::path& x)
{
	std::ifstream in(x);
	in.seekg(0, std::ios::end);
	this->buffer.resize(in.tellg());
	in.seekg(0, std::ios::beg);
	in.read(this->buffer.data(), this->buffer.size());
}

void Document::load(std::string_view x)
{
}

void Document::load(const std::string& x)
{
}
