#include "Lights\SpotLight.h"

SpotLight::SpotLight(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, glm::vec3 position,
    glm::vec3 direction, float constant, float linear, float quadratic, float cutOff, float outerCutOff) : Light(ambient, diffuse, specular)
{
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
    this->position = position;
    this->constant = constant;
    this->linear = linear;
    this->quadratic = quadratic;
    this->cutOff = cutOff;
    this->outerCutOff = outerCutOff;
    this->direction = direction;
}

SpotLight::~SpotLight()
{
    
}

void SpotLight::setPosition(glm::vec3 position)
{
    this->position = position;
}

void SpotLight::setConstant(float constant)
{
    this->constant = constant;
}

void SpotLight::setLinear(float linear)
{
    this->linear = linear;
}

void SpotLight::setQuadratic(float quadratic)
{
    this->quadratic = quadratic;
}

void SpotLight::setCutOff(float cutOff)
{
    this->cutOff = cutOff;
}

void SpotLight::setOuterCutOff(float outerCutOff)
{
    this->outerCutOff = outerCutOff;
}
