#pragma once
#include "Light.h"

class DirLight : public Light
{
public:
    glm::vec3 direction;


    DirLight(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, const glm::vec3& direction);
    ~DirLight();
    
    void setDirection(const glm::vec3& direction);
    
};
