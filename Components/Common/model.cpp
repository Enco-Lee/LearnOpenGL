#include "Model.h"
#include "texture.h"

namespace Hub
{
    Model::Model(const char* path)
    {
        loadModel(std::string(path));
    }

    void Model::draw(Shader& shader)
    {
        for (unsigned int i = 0; i < meshes.size(); ++i)
        {
            meshes[i].draw(shader);
        }
    }

    void Model::loadModel(std::string path)
    {
        Assimp::Importer import;
        const aiScene*   scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
            return;
        }
        directory = path.substr(0, path.find_last_of('/'));
        processNode(scene->mRootNode, scene);
    }

    void Model::processNode(aiNode* node, const aiScene* scene)
    {
        // process all the node's meshes (if any)
        for (unsigned int i = 0; i < node->mNumMeshes; ++i)
        {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            meshes.push_back(processMesh(mesh, scene));
        }

        // then do the same for each of its children
        for (unsigned int i = 0; i < node->mNumChildren; ++i)
        {
            processNode(node->mChildren[i], scene);
        }
    }

    Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
    {
        std::vector<MeshData::Vertex>  vertices;
        std::vector<unsigned int>      indices;
        std::vector<MeshData::Texture> textures;
        for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
        {
            MeshData::Vertex vertex;
            vertex.position = Vector3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
            vertex.normal   = Vector3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
            if (mesh->mTextureCoords[0])
            {
                vertex.texCoords = Vector2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
            }
            else
            {
                vertex.texCoords = Vector2(0.f, 0.f);
            }
            vertices.push_back(vertex);
        }
        // process indices
        for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
        {
            aiFace face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; ++j)
            {
                indices.push_back(face.mIndices[j]);
            }
        }

        // process materials
        if (mesh->mMaterialIndex >= 0)
        {
            aiMaterial*                    material = scene->mMaterials[mesh->mMaterialIndex];
            std::vector<MeshData::Texture> diffuseMaps =
                loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
            textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
            std::vector<MeshData::Texture> specularMaps =
                loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
            textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        }

        return Mesh(vertices, indices, textures);
    }

    static SPTexture TextureFromFile(const std::string& filePath)
    {
        auto texture = Texture::create(filePath.c_str());
        texture->setWrapping(Wrapping::axis_t::S, Wrapping::wrapping_t::Repeat);
        texture->setWrapping(Wrapping::axis_t::T, Wrapping::wrapping_t::Repeat);
        texture->setFilter(Filter::operator_t::Mag, Filter::filter_t::Linear);
        texture->setFilter(Filter::operator_t::Min, Filter::filter_t::LinearMipmapLinear);
        return texture;
    }

    std::vector<MeshData::Texture>
    Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
    {
        std::vector<MeshData::Texture> textures;
        for (unsigned int i = 0; i < mat->GetTextureCount(type); ++i)
        {
            aiString str;
            mat->GetTexture(type, i, &str);
            auto path = std::string(str.C_Str());
            if (textureLoadedMap.find(path) != textureLoadedMap.end())
            {
                textures.push_back(textureLoadedMap[path]);
            }
            else
            {
                MeshData::Texture texture;
                auto              filePath = directory + "/" + path;
                texture.ptr                = TextureFromFile(filePath);
                /*texture.id = texture.ptr->getID();*/
                texture.type = typeName;
                texture.path = path;
                textures.push_back(texture);
                textureLoadedMap[path] = texture;
            }
        }
        return textures;
    }

} // namespace Hub