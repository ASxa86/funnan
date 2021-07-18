#pragma once

#include <string_view>
#include <funnan/graphics/export.hxx>

namespace funnan
{
	namespace graphics
	{
		class FUNNAN_GRAPHICS_EXPORT Shader
		{
		public:
			enum class Type : int
			{
				Fragment,
				Vertex
			};

			Shader(Type x);
			~Shader();

			void load(std::string_view x);

			template <int I, typename T>
			void addAttribute(std::string_view x)
			{
			}

			unsigned int getHandle() const;

		private:
			unsigned int handle{};
		};
	}
}
