#pragma once
#include <string>
#include <vector>
class TextureCubeMap
{
public:
	TextureCubeMap(const std::vector<std::string> faces);
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

