#pragma once
#include <filesystem>
#include <map>
#include <string>
#include <vector>

#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "ShaderProgram.h"
#include "Texture2d.h"

class Model
{
public:
    Model(const std::string& path)
    {
        LoadModel(path);
    }
    Model(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<std::shared_ptr<Texture2d>> textures): directory("none")
    {
        meshes.emplace_back(std::move(vertices), std::move(indices), std::move(textures));
    }
    void Draw(ShaderProgram& shaderProgram) const;
    const std::vector<Mesh>& GetMeshes() const;
    Vector3f GetLargestDiagonal() const;
    void AddTexture(const std::string& path);
private:
    std::vector<Mesh> meshes;
    std::string directory;
    std::map<std::string, std::shared_ptr<Texture2d>> usedTextures;
    void LoadModel(const std::string& path);
    void ProcessNode(aiNode* node, const aiScene* scene);
    Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<std::shared_ptr<Texture2d>> LoadMaterialTextures(const aiScene* scene, aiMesh* mesh, aiTextureType type, std::string typeName);
    const std::filesystem::path FindCorrectPath(std::filesystem::path fileName) const;
};
