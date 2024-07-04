#include "Lights/PointLight.h"

PointLight::PointLight(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular,
    const glm::vec3& position, float constant, float linear, float quadratic) : Light(ambient, diffuse, specular)
{
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
    this->position = position;
    this->constant = constant;
    this->linear = linear;
    this->quadratic = quadratic;
}

PointLight::~PointLight()
{
    
}

void PointLight::setPosition(glm::vec3 position)
{
    this->position = position;
}

void PointLight::setConstant(float constant)
{
    this->constant = constant;
}

void PointLight::setLinear(float linear)
{    
    this->linear = linear;
}

void PointLight::setQuadratic(float quadratic)
{
    this->quadratic = quadratic;
}
