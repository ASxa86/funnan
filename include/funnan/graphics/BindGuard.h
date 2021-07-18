#pragma once

#include <funnan/graphics/Bindable.h>

namespace funnan
{
	namespace graphics
	{
		class BindGuard final
		{
		public:
			BindGuard(const Bindable& x);
			~BindGuard();

		private:
			const Bindable& bindable;
		};
	}
}