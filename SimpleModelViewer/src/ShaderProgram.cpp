#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(Shader&& vertexShader, Shader&& fragmentShader)
{
	this->m_Id = glCreateProgram();
	glAttachShader(this->m_Id, vertexShader.GetId());
	glAttachShader(this->m_Id, fragmentShader.GetId());
	glLinkProgram(this->m_Id);
	this->Bind();
	vertexShader.Delete();
	fragmentShader.Delete();
	this->Unbind();
}

ShaderProgram::ShaderProgram(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath)
	:ShaderProgram(
		Shader(ShaderType::vertexShader, vertexShaderFilePath),
		Shader(ShaderType::fragmentShader,fragmentShaderFilePath)
	)
{
															
}

GLuint ShaderProgram::GetId() const
{
	return this->m_Id;
}

void ShaderProgram::Bind() const
{
	glUseProgram(this->m_Id);
}

void ShaderProgram::Unbind() const
{
	glUseProgram(0);
}