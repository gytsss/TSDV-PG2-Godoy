#include "Lights/Light.h"



Light::Light(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular)
{
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
}

Light::~Light()
{
}

void Light::setAmbient(glm::vec3 ambient)
{
    this->ambient = ambient;
}

void Light::setDiffuse(glm::vec3 diffuse)
{
    this->diffuse = diffuse;
}

void Light::setSpecular(glm::vec3 specular)
{
    this->specular = specular;
}
