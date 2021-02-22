#pragma once

#include <filesystem>
#include <funnan/xml/export.hxx>
#include <string_view>

namespace funnan
{
	namespace xml
	{
		class FUNNAN_XML_EXPORT Document
		{
		public:
			void load(const std::filesystem::path& x);
			void load(std::string_view x);
			void load(const std::string& x);

		private:
			std::string buffer;
		};
	}
}