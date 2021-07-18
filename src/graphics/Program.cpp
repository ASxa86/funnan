#include <funnan/graphics/BindGuard.h>
#include <funnan/graphics/Program.h>
#include <glad/glad.h>

using namespace funnan::graphics;

Program::Program()
{
	this->handle = glCreateProgram();
}

Program::~Program()
{
	glDeleteProgram(this->handle);
}

void Program::bind() const
{
	glUseProgram(this->handle);
}

void Program::unbind() const
{
	glUseProgram(0);
}

void Program::attach(const std::vector<std::reference_wrapper<Shader>>& x)
{
	BindGuard bind(*this);
	for(const auto& shader : x)
	{
		glAttachShader(this->handle, shader.get().getHandle());
	}

	glLinkProgram(this->handle);
}
