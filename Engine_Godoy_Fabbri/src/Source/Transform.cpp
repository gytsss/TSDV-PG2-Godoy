#include "Transform.h"

namespace ToToEng
{
    void Transform::updateTransformMatrix()
    {
        transformMatrix = posMat * rotMat * scaleMat;
    }

    Transform::Transform()
    {
        pos = {0.0f, 0.0f, 0.0f};
        setPos({0.0f, 0.0f, 0.0f});
        setScale({1.0f, 1.0f, 1.0f});
        setRot({0.0f, 0.0f, 0.0f});
        rotMat = mat4(1.0f);

        updateTransformMatrix();
    }

    Transform::~Transform()
    {
    }

    vec3 Transform::getPos()
    {
        return pos;
    }

    vec3 Transform::getScale()
    {
        return scale;
    }

    vec3 Transform::getRot()
    {
        return rot;
    }

    vec3 Transform::getPrevPos()
    {
        return prevPos;
    }

    mat4 Transform::getTransformMatrix()
    {
        return transformMatrix;
    }

    vec3 Transform::up()
    {
        return normalize(vec3(transformMatrix[1][0], transformMatrix[1][1], transformMatrix[1][2]));
    }

    vec3 Transform::right()
    {
        return normalize(vec3(transformMatrix[0][0], transformMatrix[0][1], transformMatrix[0][2]));
    }

    vec3 Transform::forward()
    {
        return normalize(vec3(-transformMatrix[2][0], -transformMatrix[2][1], -transformMatrix[2][2]));
    }

    void Transform::lerpPos(vec3 target, float t)
    {
        const vec3 newPos
        {
            pos.x + t * (target.x - pos.x),
            pos.y + t * (target.y - pos.y),
            pos.z + t * (target.z - pos.z)
        };

        setPos(newPos);

        updateTransformMatrix();
    }

    void Transform::lerpPos(vec2 target, float t)
    {
        const vec3 newPos
        {
            pos.x + t * (target.x - pos.x),
            pos.y + t * (target.y - pos.y),
            pos.z
        };

        setPos(newPos);

        updateTransformMatrix();
    }

    void Transform::lerpPos2D(vec3 target, float t)
    {
        const vec3 newPos
        {
            pos.x + t * (target.x - pos.x),
            pos.y + t * (target.y - pos.y),
            pos.z
        };

        setPos(newPos);

        updateTransformMatrix();
    }

    void Transform::setPos(const vec3& v)
    {
        prevPos = pos;
        
        pos = vec3(0.f, 0.f, 0.f);

        posMat = mat4(1.f);

        translateX(v.x);
        translateY(v.y);
        translateZ(v.z);

        updateTransformMatrix();
    }

    void Transform::translateX(float x)
    {
        pos.x += x;

        posMat = translate(posMat, vec3(x, 0.f, 0.f));

        updateTransformMatrix();
    }

    void Transform::translateY(float y)
    {
        pos.y += y;

        posMat = translate(posMat, vec3(0.f, y, 0.f));

        updateTransformMatrix();
    }

    void Transform::translateZ(float z)
    {
        pos.z += z;

        posMat = translate(posMat, vec3(0.f, 0.f, z));

        updateTransformMatrix();
    }

    void Transform::setScale(const vec3& v)
    {
        scale = v;

        scaleMat = mat4(1.f);

        scaleMat = glm::scale(scaleMat, scale);

        updateTransformMatrix();
    }

    void Transform::setScaleX(float x)
    {
        scale.x = x;

        scaleMat = glm::scale(scaleMat, scale);

        updateTransformMatrix();
    }

    void Transform::setScaleY(float y)
    {
        scale.y = y;

        scaleMat = glm::scale(scaleMat, scale);

        updateTransformMatrix();
    }

    void Transform::setScaleZ(float z)
    {
        scale.z = z;

        scaleMat = glm::scale(scaleMat, scale);

        updateTransformMatrix();
    }

    void Transform::setRot(const vec3& v)
    {
        rot = v;

        rotMat = mat4(1.f);

        rotateX(v.x);
        rotateY(v.y);
        rotateZ(v.z);

        updateTransformMatrix();
    }

    void Transform::rotateX(float x)
    {
        rot.x += x;

        rotMat = rotate(rotMat, radians(x), vec3(1.f, 0.f, 0.f));

        updateTransformMatrix();
    }

    void Transform::rotateY(float y)
    {
        rot.y += y;

        rotMat = rotate(rotMat, radians(y), vec3(0.f, 1.f, 0.f));

        updateTransformMatrix();
    }

    void Transform::rotateZ(float z)
    {
        rot.z += z;

        rotMat = rotate(rotMat, radians(z), vec3(0.f, 0.f, 1.f));

        updateTransformMatrix();
    }
}
