#pragma once

#include <funnan/string/TypeTraits.h>
#include <charconv>
#include <filesystem>
#include <funnan/string/export.hxx>
#include <string_view>

namespace funnan
{
	namespace string
	{
		template <typename T>
		typename std::remove_reference<T>::type StringTo(std::string_view x);

		template <typename T>
		void StringTo([[maybe_unused]] std::string_view x, T& t)
		{
			if constexpr(funnan::string::is_duration<T>::value == true)
			{
				t = T{StringTo<typename T::rep>(x)};
			}
			else if constexpr(std::is_same<bool, T>::value == true)
			{
				t = (x == "true") ? true : false;
			}
			else if constexpr(std::is_same<std::filesystem::path, std::remove_reference<T>::type>::value == true)
			{
				t = x;
			}
			else if constexpr(std::is_arithmetic<std::remove_reference<T>::type>::value == true)
			{
				std::from_chars(x.data(), x.data() + x.size(), t);
			}
			else if constexpr(std::is_enum<std::remove_reference<T>::type>::value == true)
			{
				t = static_cast<T>(StringTo<typename std::underlying_type<T>::type>(x));
			}
			else if constexpr(std::is_same<std::string, std::remove_reference<T>::type>::value == true)
			{
				t = x;
			}
		}

		template <typename T>
		typename std::remove_reference<T>::type StringTo(std::string_view x)
		{
			using TNoRef = typename std::remove_const<typename std::remove_reference<T>::type>::type;

			TNoRef t{};
			StringTo(x, t);
			return t;
		}
	}
}