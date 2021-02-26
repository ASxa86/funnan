#pragma once

#include <funnan/string/TypeTraits.h>
#include <charconv>
#include <chrono>
#include <filesystem>
#include <funnan/string/export.hxx>
#include <string>

namespace funnan
{
	namespace string
	{
		///
		///	\brief Special ToString overload to support floating point precision and format.
		///
		///	\param x The double to convert.
		///	\param precision The decimal precision to output.
		///	\param fmt Specify either scientific or fixed format.
		///
		FUNNAN_STRING_EXPORT std::string ToString(float x, int precision = std::numeric_limits<float>::digits10 + 1,
												  std::chars_format fmt = std::chars_format::fixed);

		FUNNAN_STRING_EXPORT std::string ToString(double x, int precision = std::numeric_limits<double>::digits10 + 1,
												  std::chars_format fmt = std::chars_format::fixed);

		///
		///	\brief Generic type conversion/serialization to a std::string.
		///
		///	Complex types such as containers and classes will be serialized as json strings.
		///
		template <typename T>
		std::string ToString([[maybe_unused]] const T& x)
		{
			using TNoRef = typename std::remove_reference<T>::type;

			if constexpr(funnan::string::is_duration<TNoRef>::value == true)
			{
				return ToString(x.count());
			}
			else if constexpr(std::is_same<bool, TNoRef>::value == true)
			{
				return x ? "true" : "false";
			}
			else if constexpr(std::is_same<std::filesystem::path, TNoRef>::value == true)
			{
				return x.string();
			}
			else if constexpr(std::is_arithmetic<TNoRef>::value == true)
			{
				constexpr auto MaxDigits = std::numeric_limits<TNoRef>::digits10 + 1;
				std::string buffer;
				buffer.resize(MaxDigits);

				const auto [p, ec] = std::to_chars(buffer.data(), buffer.data() + buffer.size(), x);

				if(ec == std::errc())
				{
					buffer.resize(p - buffer.data());
				}

				return buffer;
			}
			else if constexpr(std::is_enum<TNoRef>::value == true)
			{
				return ToString(static_cast<typename std::underlying_type<TNoRef>::type>(x));
			}
			else if constexpr(std::is_convertible<TNoRef, std::string>::value == true)
			{
				return static_cast<std::string>(x);
			}
			else if constexpr(std::is_same<std::string, TNoRef>::value == true)
			{
				return x;
			}
		}
	}
}