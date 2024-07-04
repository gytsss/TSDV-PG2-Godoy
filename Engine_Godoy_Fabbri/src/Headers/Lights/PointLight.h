#pragma once
#include "Light.h"

class PointLight : public Light
{
public:
    glm::vec3 position;
    float constant;
    float linear;
    float quadratic;

    
    PointLight(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, glm::vec3 position, float constant, float linear, float quadratic);
    ~PointLight();
    
    void setPosition(glm::vec3 position);
    void setConstant(float constant);
    void setLinear(float linear);
    void setQuadratic(float quadratic);
    
    
};
