#include "Lights/DirLight.h"

DirLight::DirLight(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular,
    const glm::vec3& direction) : Light(ambient, diffuse, specular)
{
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
    this->direction = direction;
}

DirLight::~DirLight()
{
    
}

void DirLight::setDirection(const glm::vec3& direction)
{
    this->direction = direction;
}
