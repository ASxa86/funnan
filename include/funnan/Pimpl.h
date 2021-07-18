#pragma once

#include <memory>

///
///	\class Pimpl
///
///	\brief Private Implementation. Useful for hiding implementation details and modifying code without changing the API.
///
///	Modified from http://herbsutter.com/gotw/_101/
///
///	\date April 12, 2017
///
///	\author Aaron Shelley
///
template <typename T>
class Pimpl
{
public:
	Pimpl();
	template <typename... Args>
	Pimpl(Args&&...);
	~Pimpl();
	T* operator->();
	const T* operator->() const;
	T& operator*();

private:
	std::unique_ptr<T> m;
};
