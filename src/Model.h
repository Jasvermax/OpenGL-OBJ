#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <string>
#include <assimp/scene.h>

#include "Mesh.h"

class Shader;

class Model {
public:
    Model(const std::string& path);
    void Draw(Shader& shader);

private:
    std::vector<Mesh> meshes;
    std::string directory;

    void loadModel(const std::string& path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);

    unsigned int loadTexture(const std::string& path);
};

#endif
