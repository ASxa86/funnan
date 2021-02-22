#pragma once

#include <string>
#include <string_view>

namespace funnan
{
	namespace xml
	{
		class Attribute
		{
		public:
			std::string_view getName() const;
			std::string_view getValue() const;

			template <typename T>
			T getValue() const
			{
				return T{};
			}

		private:
			std::string name;
			std::string value;
		};
	}
}