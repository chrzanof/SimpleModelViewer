#include "Model.h"

#include <filesystem>
#include <iostream>

#include "ShaderProgram.h"
#include "Texture2d.h"

void Model::Draw(ShaderProgram& shaderProgram) const
{
	for (unsigned int i = 0; i < meshes.size(); i++)
	{
        meshes[i].Draw(shaderProgram);
	}
}

const std::vector<Mesh>& Model::GetMeshes() const
{
    return meshes;
}

void Model::loadModel(const std::string& path)
{
    Assimp::Importer import;
    const aiScene * scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }
    directory = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}

void Model::AddTexture(const std::string& path)
{
    std::shared_ptr<Texture2d> texture2d;
    if(auto search = usedTextures.find(path); search == usedTextures.end())
    {
        texture2d = std::make_shared<Texture2d>(path);
        usedTextures.insert(std::make_pair(path, texture2d));
    }
    else
    {
        texture2d = search->second;
    }
    for(int i = 0; i < meshes.size(); i++)
    {
        meshes[i].m_Textures.insert(meshes[i].m_Textures.begin(), texture2d);
    }
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }
    
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<std::shared_ptr<Texture2d>> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vector2f textCoords{ 0.0f, 0.0f };
        if (mesh->mTextureCoords[0])
        {
           
        	textCoords.x = mesh->mTextureCoords[0][i].x;
            textCoords.y = mesh->mTextureCoords[0][i].y;
            
        }
        Vertex vertex {
            Vector3f{mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z},
            Vector3f{mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z},
            textCoords
        };
    	vertices.push_back(vertex);
    }
    
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    if(mesh->mMaterialIndex >= 0)
    {
        
        textures = loadMaterialTextures(scene, mesh,aiTextureType_DIFFUSE, "texture_diffuse");
    }

    return Mesh{ vertices, indices, textures };
}

std::vector<std::shared_ptr<Texture2d>> Model::loadMaterialTextures(const aiScene* scene, aiMesh* mesh, aiTextureType type, std::string typeName)
{
    aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];
    std::vector<std::shared_ptr<Texture2d>> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        std::filesystem::path texturePath = str.C_Str();
        std::filesystem::path modelDir = directory;
        modelDir = modelDir.parent_path();
        modelDir /= texturePath;
        auto search = usedTextures.find(modelDir.string());
        if(search == usedTextures.end())
        {
            if (str.C_Str()[0] == '*')
            {
                int index = str.C_Str()[1] - '0';
                const aiTexture* texture = scene->mTextures[index];
                auto texture2d = std::make_shared<Texture2d>(texture);
                usedTextures.insert(std::make_pair(modelDir.string(), texture2d));
                textures.push_back(texture2d);
            }
            else
            {
                auto texture2d = std::make_shared<Texture2d>(modelDir.string());
                usedTextures.insert(std::make_pair(modelDir.string(), texture2d));
                textures.push_back(texture2d);
            }
        }
    	else
        {
            textures.push_back(search->second);
        }
        
    }
    return textures;
}
