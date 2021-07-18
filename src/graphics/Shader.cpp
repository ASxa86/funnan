#include <funnan/graphics/Shader.h>
#include <glad/glad.h>
#include <array>
#include <iostream>

using namespace funnan::graphics;

Shader::Shader(Type x)
{
	GLenum type = GL_FRAGMENT_SHADER;

	switch(x)
	{
		case Type::Vertex:
			type = GL_VERTEX_SHADER;
			break;

		default:
			break;
	}

	this->handle = glCreateShader(type);
}

Shader::~Shader()
{
	glDeleteShader(this->handle);
}

void Shader::load(std::string_view x)
{
	const auto temp = x.data();
	glShaderSource(this->handle, 1, &temp, nullptr);
	glCompileShader(this->handle);

	int success{};
	std::string infoLog;
	infoLog.resize(512);
	glGetShaderiv(this->handle, GL_COMPILE_STATUS, &success);

	if(!success)
	{
		glGetShaderInfoLog(this->handle, infoLog.size(), NULL, infoLog.data());
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

unsigned int Shader::getHandle() const
{
	return this->handle;
}
