#pragma once
#include "Light.h"

class SpotLight : public Light
{
public:
    glm::vec3 position;
    glm::vec3 direction;
    float constant;
    float linear;
    float quadratic;
    float cutOff;
    float outerCutOff;

    SpotLight(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular,
        glm::vec3 position, glm::vec3 direction, float constant, float linear, float quadratic, float cutOff, float outerCutOff);
    ~SpotLight();
    void setPosition(glm::vec3 position);
    void setConstant(float constant);
    void setLinear(float linear);
    void setQuadratic(float quadratic);
    void setCutOff(float cutOff);
    void setOuterCutOff(float outerCutOff);
    
};
