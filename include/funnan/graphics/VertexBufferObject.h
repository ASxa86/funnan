#pragma once

#include <funnan/graphics/Bindable.h>
#include <funnan/graphics/Vertex.h>
#include <funnan/graphics/export.hxx>
#include <vector>

namespace funnan
{
	namespace graphics
	{
		class FUNNAN_GRAPHICS_EXPORT VertexBufferObject : public Bindable
		{
		public:
			enum class DrawType : int
			{
				Static,
				Dynamic,
				Stream
			};

			VertexBufferObject();
			~VertexBufferObject() override;

			void bind() const override;
			void unbind() const override;

			void load(const std::vector<funnan::graphics::Vertex>& vertices, DrawType type = DrawType::Static);
		};
	}
}
