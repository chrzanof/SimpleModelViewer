#pragma once
#include <vector>
#include <string>
#include "ShaderProgram.h"
#include "TextureCubeMap.h"
class Skybox
{
public:
	Skybox(const std::vector<std::string>& skyboxFaces);
	void Draw(const ShaderProgram& shader);

private:
	unsigned int m_VAO, m_VBO;
	std::vector<float> m_Vertices {
	-1.0f,  3.0f, 1.0f,
	 3.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f
	};
	TextureCubeMap m_TextureCubeMap;

};

