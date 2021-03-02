#pragma once

#include <funnan/Property.h>
#include <functional>

namespace funnan
{
	///
	///	\class PropertyTemplateMethod
	///
	///	\brief This class override property to manage class methods as a reflective property.
	///
	///	\author Aaron Shelley
	///
	///	\date February 17, 2020
	///
	template <typename T>
	class PropertyTemplateMethod : public Property
	{
	public:
		using Writer = std::function<void(T)>;
		using Reader = std::function<T()>;

		PropertyTemplateMethod(std::string_view n, Writer w, Reader r) : Property{n}, writer{std::move(w)}, reader{std::move(r)}
		{
		}

		void setValue(std::any value) override
		{
			this->writer(std::any_cast<T>(value));
		}

		std::any getValue() const override
		{
			return this->reader();
		}

		void setValueString(std::string_view x) override
		{
			T t{};
			auto j = nlohmann::json::parse(x);
			j.get_to(t);
			this->writer(t);
		}

		std::string getValueString() const override
		{
			nlohmann::json j = this->reader();
			return j.dump();
		}

		const std::type_info& getTypeInfo() const noexcept override
		{
			return typeid(T);
		}

	private:
		Writer writer;
		Reader reader;
	};
}
