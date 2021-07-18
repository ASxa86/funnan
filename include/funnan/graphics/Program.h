#pragma once

#include <funnan/graphics/Bindable.h>
#include <funnan/graphics/Shader.h>
#include <vector>

namespace funnan
{
	namespace graphics
	{
		class FUNNAN_GRAPHICS_EXPORT Program : public Bindable
		{
		public:
			Program();
			~Program() override;

			void bind() const override;
			void unbind() const override;

			void attach(const std::vector<std::reference_wrapper<Shader>>& x);
		};
	}
}
