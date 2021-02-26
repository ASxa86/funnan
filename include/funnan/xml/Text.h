#pragma once

#include <funnan/string/StringTo.h>
#include <funnan/xml/Element.h>

namespace funnan
{
	namespace xml
	{
		class FUNNAN_XML_EXPORT Text : public Element
		{
		public:
			template <typename T>
			T as() const
			{
				return funnan::string::StringTo<T>(this->text);
			}

		private:
			std::string text;
		};
	}
}