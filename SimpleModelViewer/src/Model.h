#pragma once
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
        loadModel(path);
    }
    Model(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<std::shared_ptr<Texture2d>> textures): directory("none")
    {
        meshes.emplace_back(std::move(vertices), std::move(indices), std::move(textures));
    }
    void Draw(ShaderProgram& shaderProgram) const;
    const std::vector<Mesh>& GetMeshes() const;
    void AddTexture(const std::string& path);
private:
    std::vector<Mesh> meshes;
    std::string directory;
    std::map<std::string, std::shared_ptr<Texture2d>> usedTextures;
    void loadModel(const std::string& path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<std::shared_ptr<Texture2d>> loadMaterialTextures(const aiScene* scene, aiMesh* mesh, aiTextureType type, std::string typeName);
};
