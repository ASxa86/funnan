#pragma once

#include <chrono>
#include <memory>
#include <type_traits>

namespace funnan
{
	namespace string
	{
		template <typename T, typename _ = void>
		struct is_container : std::false_type
		{
		};

		template <typename T>
		struct is_container<T, std::conditional_t<false,
												  std::void_t<typename T::value_type, typename T::size_type, typename T::allocator_type,
															  typename T::iterator, typename T::const_iterator, decltype(std::declval<T>().size()),
															  decltype(std::declval<T>().begin()), decltype(std::declval<T>().end()),
															  decltype(std::declval<T>().cbegin()), decltype(std::declval<T>().cend())>,
												  void>> : public std::true_type
		{
		};

		template <class T>
		struct is_unique_ptr : std::false_type
		{
		};

		template <class T, class D>
		struct is_unique_ptr<std::unique_ptr<T, D>> : std::true_type
		{
		};

		template <class T>
		struct is_duration : std::false_type
		{
		};

		template <class Rep, class Period>
		struct is_duration<std::chrono::duration<Rep, Period>> : std::true_type
		{
		};
	}
}
