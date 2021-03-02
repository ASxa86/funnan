#include <funnan/TypeInfo.h>

#include <boost/core/demangle.hpp>

std::string funnan::GetTypeName(const std::type_info& x)
{
	auto name = boost::core::demangle(x.name());

	static constexpr std::string_view StringClass = "class";
	static constexpr std::string_view StringStruct = "struct";
	static constexpr std::string_view StringAnonymous = "`anonymous namespace'::";

	// If the run-time type is of "class " or "struct " remove it. Otherwise, leave the space in for types such as "unsigned int", "long long", etc...
	// i.e. "class precog::MyClass" -> "precog::MyClass"
	if(name.compare(0, StringClass.size(), StringClass) == 0 || name.compare(0, StringStruct.size(), StringStruct) == 0)
	{
		name = name.substr(name.find_first_of(' ') + 1);
	}

	// Remove anonymous namespaces.
	if(name.compare(0, StringAnonymous.size(), StringAnonymous) == 0)
	{
		name = name.substr(name.find_last_of(':') + 1);
	}

	return name;
}

funnan::TypeInfo funnan::GetType(const std::type_info& x)
{
	return {x};
}
