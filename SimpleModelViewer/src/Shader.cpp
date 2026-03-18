#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(ShaderType type, const std::string& filePath)
{
	std::ifstream file;
	file.open(filePath);
	if (file.fail())
	{
		std::cout << "Error opening the file: " << filePath << "\n";
	}

	std::stringstream buffer;
	buffer << file.rdbuf();
	m_Source = buffer.str();

	m_Id = glCreateShader(static_cast<GLenum>(type));
	const char* sourceCStr = m_Source.c_str();
	glShaderSource(m_Id, 1, &sourceCStr, NULL);
	glCompileShader(m_Id);

	GLint shaderCompiled;
	glGetShaderiv(m_Id, GL_COMPILE_STATUS, &shaderCompiled);
	if (shaderCompiled != GL_TRUE)
	{
		GLsizei log_length = 0;
		GLchar message[1024];
		glGetShaderInfoLog(m_Id, 1024, &log_length, message);
		std::cout << message;
	}
}

void Shader::Delete()
{
	glDeleteShader(m_Id);
	m_Id = 0;
}

GLuint Shader::GetId() const
{
	return m_Id;
}

const std::string& Shader::GetSource()
{
	return m_Source;
}

