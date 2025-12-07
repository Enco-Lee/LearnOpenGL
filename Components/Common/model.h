#pragma once
#include "shader.h"
#include "mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <unordered_map>

namespace Hub
{
    class Model
    {
    public:
        Model(const char* path);
        void draw(Shader& shader);

    private:
        // model data
        std::vector<Mesh> meshes;
        std::string       directory;

        void loadModel(std::string path);
        void processNode(aiNode* node, const aiScene* scene);
        Mesh processMesh(aiMesh* mesh, const aiScene* scene);

        std::vector<MeshData::Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
        std::unordered_map<std::string, MeshData::Texture> textureLoadedMap;
    };
} // namespace Hub