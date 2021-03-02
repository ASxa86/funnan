#pragma once

#include <functional>
#include <vector>

namespace funnan
{
	template <typename T>
	class Signal;

	template <typename R, typename... Args>
	class Signal<R(Args...)>
	{
	public:
		void notify(Args... x) const
		{
			for(const auto& f : this->functions)
			{
				f(x ...);
			}
		}

		void connect(std::function<R(Args...)> x)
		{
			this->functions.push_back(std::move(x));
		}

	private:
		std::vector<std::function<R(Args...)>> functions;
	};
}