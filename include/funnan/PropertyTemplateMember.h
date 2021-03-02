#pragma once

#include <funnan/Property.h>
#include <nlohmann/json.hpp>

namespace funnan
{
	///
	///	\class PropertyTemplateMember
	///
	///	\brief This class override property to manage class member variables as a reflective property.
	///
	///	\author Aaron Shelley
	///
	///	\date February 17, 2020
	///
	template <typename T>
	class PropertyTemplateMember : public Property
	{
	public:
		PropertyTemplateMember(std::string_view n, T& p) : Property{n}, property{p}
		{
		}

		void setValue(std::any value) override
		{
			this->property = std::any_cast<T>(value);
		}

		std::any getValue() const override
		{
			return this->property;
		}

		void setValueString(std::string_view x) override
		{
			auto j = nlohmann::json::parse(x);
			j.get_to(this->property);
		}

		std::string getValueString() const override
		{
			nlohmann::json j = this->property;
			return j.dump();
		}

		const std::type_info& getTypeInfo() const noexcept override
		{
			return typeid(T);
		}

	private:
		T& property;
	};
}
