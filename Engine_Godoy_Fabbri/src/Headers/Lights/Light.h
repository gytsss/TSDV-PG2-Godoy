#pragma once
#include <string>
#include <glm/vec3.hpp>

enum LightType
{
    Directional,
    Point,
    Spot
};


class Light
{
public:
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    LightType tag;
    bool isOn = true;
    
    
    Light(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular);

    ~Light();
    void setAmbient(glm::vec3 ambient);
    void setDiffuse(glm::vec3 diffuse);
    void setSpecular(glm::vec3 specular);

    void turnOn();
    void turnOff();
    void turn();
};
