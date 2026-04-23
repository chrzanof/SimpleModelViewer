#include "TextureCubeMap.h"

#include <iostream>
#include "stb_image.h"
#include <glad/glad.h>

TextureCubeMap::TextureCubeMap(const std::vector<std::string> faces)
{
	glGenTextures(1, &m_Id);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_Id);
	glTexParameteri(
		GL_TEXTURE_CUBE_MAP,
		GL_TEXTURE_MIN_FILTER,
		GL_LINEAR_MIPMAP_LINEAR
	);
	glTexParameteri(
		GL_TEXTURE_CUBE_MAP,
		GL_TEXTURE_MAG_FILTER,
		GL_LINEAR
	);

	for (int i = 0; i < faces.size(); i++)
	{
		unsigned char* data = stbi_load(faces.at(i).c_str(), &m_Width, &m_Height, &m_NrChannels, 0);
		if (data)
		{
			GLint format = m_NrChannels == 4 ? GL_RGBA : GL_RGB;
			glTexImage2D(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0,
				GL_RGBA,
				m_Width,
				m_Height,
				0,
				format,
				GL_UNSIGNED_BYTE,
				data
			);
			glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
		}
		else
		{
			std::cout << "Failed to load texture from path: " << faces.at(i) << "\n";
		}
		stbi_image_free(data);
	}

}

void TextureCubeMap::Bind() const
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_Id);
}

void TextureCubeMap::Unbind() const
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

unsigned int TextureCubeMap::GetId() const
{
	return m_Id;
}

int TextureCubeMap::GetWidth() const
{
	return m_Width;
}

int TextureCubeMap::GetHeight() const
{
	return m_Height;
}

int TextureCubeMap::GetNrChannels() const
{
	return m_NrChannels;
}
