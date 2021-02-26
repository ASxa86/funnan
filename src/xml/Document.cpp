#include <funnan/xml/Document.h>
#include <fstream>

#include <iostream>

using namespace funnan::xml;

void Document::load(const std::filesystem::path& x)
{
	if(std::filesystem::exists(x) == true)
	{
		std::ifstream in(x, std::ios::binary | std::ios::ate);

		if(in.is_open() == true)
		{
			this->buffer.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(this->buffer.data(), this->buffer.size());

			for(auto it = std::begin(this->buffer); it != std::end(this->buffer); ++it)
			{
				++it;

				// <?xml version="1.0" encoding="UTF-8"?>
				if(*it == '?')
				{
					while(*it != '>')
					{
						++it;
					}
				}

				this->parseElement(*this, it);
			}
		}
	}
}

void Document::load(std::string_view x)
{
}

void Document::load(const std::string& x)
{
}

void Document::parseElement(Element& parent, std::string::iterator it)
{
	static constexpr std::string_view commentBeg{"!--"};
	static constexpr std::string_view commentEnd{"--"};

	static constexpr auto tagBeg{'<'};
	static constexpr auto tagEnd{'>'};

	static constexpr auto elementEnd{'/'};

	bool tagParsing{false};

	for(; it != std::end(this->buffer); ++it)
	{
		// We've found the beginning of an XML element.
		// <TESTCASES PROFILE="James Clark XMLTEST cases, 18-Nov-1998">
		if(*it == tagBeg)
		{
			tagParsing = true;

			// T
			++it;

			if(*it == tagEnd)
			{
				tagParsing = false;
			}

			// Comment Sequence <!-- -->
			if(std::string_view{it, it + commentBeg.size()} == commentBeg)
			{
				it += commentBeg.size();

				while(std::string_view{it, it + commentEnd.size()} != commentEnd)
				{
					++it;
				}

				it += commentEnd.size();

				if(*it != tagEnd)
				{
					// Invalid XML syntax
				}
			}
			else if(*it == elementEnd)
			{
				++it;
				auto nameBegIt = it;
				auto nameEndIt = it;

				while(*it != tagEnd)
				{
					nameEndIt = ++it;
				}

				// We've reached the end of this parent. Exit scope.
				// </TESTCASES>
				const std::string_view elementName{nameBegIt, nameEndIt};

				if(parent.getName() == elementName)
				{
					return;
				}
			}
			else
			{
				if(tagParsing == true)
				{
					// Determine the name of this element.
					const auto nameBegIt = it;
					auto nameEndIt = it;

					// TESTCASES  PROFILE="James Clark XMLTEST cases, 18-Nov-1998">
					// Parse the first string before whitespace to determine the tag's name.
					// Anything that follows will be attributes.
					while(*it != ' ')
					{
						nameEndIt = ++it;
					}

					const std::string_view elementName{nameBegIt, nameEndIt};

					auto element = parent.addChild(elementName);
					this->parseElement(*element, it);
				}
			}
		}
	}
}
