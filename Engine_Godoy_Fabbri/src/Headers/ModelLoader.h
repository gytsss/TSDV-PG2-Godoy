#pragma once
#include <string>
#include <vector>

#include "Mesh.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"

static class ModelLoader
{
public:
    // model data 
    static std::vector<Texture> textures_loaded;
    // stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.

    static std::string directory;
    static bool gammaCorrection;

    // loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
    static void loadModel(std::string const& path, std::vector<Mesh> &meshes, bool gamma = false);
private:

    // processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
    static void processNode(aiNode* node, const aiScene* scene, std::vector<Mesh>& meshes, bool gamma = false);

    static Mesh processMesh(aiMesh* mesh, const aiScene* scene, std::vector<Mesh>& meshes, bool gamma = false);

    // checks all material textures of a given type and loads the textures if they're not loaded yet.
    // the required info is returned as a Texture struct.
    static std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName, bool gamma = false);
};


static unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma);
