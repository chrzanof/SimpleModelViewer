#pragma once
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
    Model(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture2d> textures): directory("none")
    {
        meshes.emplace_back(std::move(vertices), std::move(indices), std::move(textures));
    }
    void Draw(ShaderProgram& shaderProgram, Texture2d& texture) const;
    const std::vector<Mesh>& GetMeshes() const;
private:
    std::vector<Mesh> meshes;
    std::string directory;
    void loadModel(const std::string& path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture2d> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};
