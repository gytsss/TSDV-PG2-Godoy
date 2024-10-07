#pragma once
#include <vector>

#include "Entities/Entity.h"
#include "Entities/Entity3D.h"
#include "Mesh.h"
#include "ModelLoader.h"

class TOTO_API Model : public ToToEng::Entity3D
{
public:
    std::vector<Mesh> meshes;
    // constructor, expects a filepath to a 3D model.
    Model(ToToEng::Renderer *renderer, std::string const &path, bool gamma = false);

    // draws the model, and thus all its meshes
      void draw() override;
    
};

