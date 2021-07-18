#pragma once

#include <utility>

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
Pimpl<T>::Pimpl() : m{std::make_unique<T>()}
{
}

template <typename T>
template <typename... Args>
Pimpl<T>::Pimpl(Args&&... args) : m{std::make_unique<T>(std::forward<Args>(args)...)}
{
}

template <typename T>
Pimpl<T>::~Pimpl()
{
}

template <typename T>
T* Pimpl<T>::operator->()
{
	return m.get();
}

template <typename T>
const T* Pimpl<T>::operator->() const
{
	return m.get();
}

template <typename T>
T& Pimpl<T>::operator*()
{
	return *m.get();
}
