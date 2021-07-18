#include <funnan/graphics/BindGuard.h>
#include <funnan/graphics/VertexBufferObject.h>
#include <glad/glad.h>

using namespace funnan::graphics;

VertexBufferObject::VertexBufferObject()
{
	glGenBuffers(1, &this->handle);
}

VertexBufferObject::~VertexBufferObject()
{
	glDeleteBuffers(1, &this->handle);
}

void VertexBufferObject::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, this->handle);
}

void VertexBufferObject::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBufferObject::load(const std::vector<Vertex>& vertices, DrawType type)
{
	GLenum usage = GL_STATIC_DRAW;

	switch(type)
	{
		case DrawType::Dynamic:
			usage = GL_DYNAMIC_DRAW;
			break;

		case DrawType::Stream:
			usage = GL_STREAM_DRAW;
			break;

		default:
			break;
	}

	BindGuard bind(*this);
	using VertexType = std::remove_reference_t<decltype(vertices)>::value_type;
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexType) * vertices.size(), vertices.data(), usage);
}