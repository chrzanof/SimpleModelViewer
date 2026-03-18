#pragma once
#include <string>
#include <assimp/texture.h>

class Texture2d
{
public:
	Texture2d(const std::string& fileName);
	Texture2d(const aiTexture* aiTexture);
	void Bind() const;
	void Unbind() const;
	unsigned int GetId() const;
	int GetWidth() const;
	int GetHeight() const;
	int GetNrChannels() const;

private:
	unsigned int m_Id;
	int m_Width, m_Height, m_NrChannels;
};

