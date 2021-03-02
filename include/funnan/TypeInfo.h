#pragma once

#include <funnan/export.hxx>
#include <string_view>
#include <typeinfo>

namespace funnan
{
	///
	///	\brief Get the human readable string for the given type at compile-time.
	///
	template <typename T>
	constexpr std::string_view GetTypeName()
	{
		// Arithmetic values are currently not supported. This is due to the amount of work involved to ensure
		// cross-platform compatibility. MSVC: "unsigned int", GCC: "int unsigned".
		static_assert(std::is_arithmetic<T>::value == false, "T must not be an arithmetic type.");
#ifdef WIN32
		constexpr std::string_view signature = __FUNCSIG__;

		// "std::basic_string_view<char, std::char_traits<char>> GetTypeName<namespace::Class>()"
		constexpr std::string_view removedLeft = signature.substr(signature.find_last_of('<') + 1);

		// "class namespace::Class>()"
		constexpr std::string_view removedRight = removedLeft.substr(0, removedLeft.find_last_of('>'));

		// "class namespace::Class"
		constexpr std::string_view removedSpace = removedRight.substr(removedRight.find_last_of(' ') + 1);

		// "namespace::Class"
		return removedSpace;
#else
		constexpr std::string_view signature = __PRETTY_FUNCTION__;
		constexpr std::string_view withT{"T = "};

		// GCC // constexpr std::string_view GetTypeName() [with T = namespace::Class; std::string_view = std::basic_string_view<char>]
		// Clang // std::string_view GetTypeName() [T = namespace::Class]
		constexpr std::string_view removedLeft = signature.substr(signature.find(withT) + withT.size());

		// GCC // namespace::Class; std::string_view = std::basic_string_view<char>]
		// Clang // namespace::Class]
		constexpr std::string_view removedRight = removedLeft.substr(0, removedLeft.find_first_of(";]"));

		// namespace::Class
		return removedRight;
#endif
	}

	///
	///	\brief Get the human readable string for the given type_info object at run-time.
	///
	FUNNAN_EXPORT std::string GetTypeName(const std::type_info& x);

	struct TypeInfo
	{
		TypeInfo(const std::type_info& t) : type{t}, name{GetTypeName(this->type)}
		{
		}

		bool operator==(std::string_view x) const
		{
			return this->name == x;
		}

		bool operator==(const TypeInfo& x) const
		{
			return this->type == x.type;
		}

		bool operator==(const std::type_info& x) const
		{
			return this->type == x;
		}

		bool operator<(const TypeInfo& x) const
		{
			return this->name < x.name;
		}

		const std::type_info& type;
		const std::string name;
	};

	FUNNAN_EXPORT TypeInfo GetType(const std::type_info& x);

	template <typename T>
	TypeInfo GetType()
	{
		return {typeid(T)};
	}
}
