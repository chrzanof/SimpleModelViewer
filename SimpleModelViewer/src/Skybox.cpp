#include "Skybox.h"

Skybox::Skybox(const std::vector<std::string>& skyboxFaces): m_TextureCubeMap(skyboxFaces)
{
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_Vertices.size(), &m_Vertices.front(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
	glBindVertexArray(0);
}

void Skybox::Draw(const ShaderProgram& shader)
{
	shader.Bind();
	glActiveTexture(GL_TEXTURE0);
	m_TextureCubeMap.Bind();

	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindVertexArray(0);
	m_TextureCubeMap.Unbind();
	shader.Unbind();
}
