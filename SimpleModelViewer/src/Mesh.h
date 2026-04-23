#pragma once
#include <memory>
#include <glad/glad.h> 
#include <vector>
#include "ShaderProgram.h"
#include "Texture2d.h"
#include "Vertex.h"

class Mesh
{
	friend class Model;
public:
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices,
		std::vector<std::shared_ptr<Texture2d>> textures);
	~Mesh();
	Mesh(Mesh&& other) noexcept
		: m_Vertices(std::move(other.m_Vertices)),
		m_Indices(std::move(other.m_Indices)),
		m_Textures(std::move(other.m_Textures)),
		m_VAO(other.m_VAO),
		m_VBO(other.m_VBO),
		m_EBO(other.m_EBO)
	{
		other.m_VAO = 0;
		other.m_VBO = 0;
		other.m_EBO = 0;
	}

	
	const std::vector<Vertex>& GetVerticesData() const;
	const std::vector<unsigned int>& GetIndicesData() const;
	void Bind() const;
	void Unbind() const;
	void Draw(ShaderProgram& shaderProgram) const;

private:
	void SetupMesh();
	std::vector<Vertex> m_Vertices;
	std::vector<unsigned int> m_Indices;
	std::vector<std::shared_ptr<Texture2d>> m_Textures;

	GLuint m_VAO, m_VBO, m_EBO;
};