#pragma once
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <vector>

#include "ShaderProgram.h"
#include "Texture2d.h"
#include "Vertex.h"

struct Texture {
	unsigned int id;
	std::string type;
};

class Mesh
{
public:
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices,
		std::vector<Texture2d> textures);
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

	void setupMesh();
	const std::vector<Vertex>& GetVerticesData() const;
	const std::vector<unsigned int>& GetIndicesData() const;
	void Bind() const;
	void Unbind() const;
	void Draw(ShaderProgram& shaderProgram, Texture2d& texture) const;

private:
	std::vector<Vertex> m_Vertices;
	std::vector<unsigned int> m_Indices;
	std::vector<Texture2d> m_Textures;

	GLuint m_VAO, m_VBO, m_EBO;
};

