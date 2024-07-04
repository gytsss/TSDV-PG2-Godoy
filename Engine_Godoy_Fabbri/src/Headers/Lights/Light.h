#pragma once
#include <glm/vec3.hpp>

class Light
{
public:
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    
    
    Light(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular);

    ~Light();
    void setAmbient(glm::vec3 ambient);
    void setDiffuse(glm::vec3 diffuse);
    void setSpecular(glm::vec3 specular);
};
