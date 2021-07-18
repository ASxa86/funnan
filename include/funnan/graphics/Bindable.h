#pragma once

namespace funnan
{
	namespace graphics
	{
		class Bindable
		{
		public:
			virtual ~Bindable() = default;
			virtual void bind() const = 0;
			virtual void unbind() const = 0;

			unsigned int getHandle() const;

		protected:
			unsigned int handle{};
		};
	}
}
