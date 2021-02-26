#pragma once

#include <funnan/xml/Element.h>
#include <filesystem>
#include <funnan/xml/export.hxx>

namespace funnan
{
	namespace xml
	{
		class FUNNAN_XML_EXPORT Document : public Element
		{
		public:
			void load(const std::filesystem::path& x);
			void load(std::string_view x);
			void load(const std::string& x);

		private:
			void parseElement(Element& parent, std::string::iterator it);

			std::string buffer;
		};
	}
}