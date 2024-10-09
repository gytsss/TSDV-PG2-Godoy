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

    void Transform::updateLocalTransformMatrix()
    {
        updateTransformRotation();
        const mat4 transformX = glm::rotate(mat4(1.0f),(rot.x), vec3(1.0f, 0.0f, 0.0f));
        const mat4 transformY = glm::rotate(mat4(1.0f),(rot.y), vec3(0.0f, 1.0f, 0.0f));
        const mat4 transformZ = glm::rotate(mat4(1.0f),(rot.z), vec3(0.0f, 0.0f, 1.0f));
        // Y * X * Z
        const mat4 roationMatrix = transformX * transformY * transformZ;
        // translation * rotation * scale (also know as TRS matrix)
        localModel = glm::translate(glm::mat4(1.0f), pos) * roationMatrix * glm::scale(mat4(1.0f), scale);
        updateTransformMatrix();
        
    }

    void Transform::updateTransformRotation()
    {
        quat rotation = EulerToQuat(rot);
        vec3 forward = QuatToVec(rotation, vec3(0.f, 0.f, 1.f));
        vec3 up = QuatToVec(rotation, vec3(0.f, 1.f, 0.f));
        vec3 right = QuatToVec(rotation, vec3(1.f, 0.f, 0.f));
        setForward(forward);
        setUp(up);
        setRight(right);
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

    void Transform::moveRight(float x)
    {
        vec3 rightVector = right(); 
        pos += rightVector * x;
        posMat = translate(posMat, rightVector * x);
        updateTransformMatrix();
    }

    void Transform::moveUp(float y)
    {
        vec3 upVector = up();
        pos += upVector * y;
        posMat = translate(posMat, upVector * y);
        updateTransformMatrix();
    }

    void Transform::moveForward(float z)
    {
        vec3 forwardVector = forward(); 
        pos += forwardVector * z;
        posMat = translate(posMat, forwardVector * z);
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

    void Transform::setForward(vec3 v)
    {
        localModel[2].x = -v.x;
        localModel[2].y = -v.y;
        localModel[2].z = -v.z;
        localModel[2].w = -0;
    }
    void Transform::setRight(vec3 v)
    {
        localModel[0].x = v.x;
        localModel[0].y = v.y;
        localModel[0].z = v.z;
        localModel[0].w = 0;
    };
    void Transform::setUp(vec3 v)
    {
        localModel[1].x = v.x;
        localModel[1].y = v.y;
        localModel[1].z = v.z;
        localModel[1].w = 0;
    }

    vec3 QuatToVec(glm::quat quat, glm::vec3 vec)
    {
        float x2 = quat.x * 2.f;
        float y2 = quat.y * 2.f;
        float z2 = quat.z * 2.f;
        float xx2 = quat.x * x2;
        float yy2 = quat.y * y2;
        float zz2 = quat.z * z2;
        float xy2 = quat.x * y2;
        float xz2 = quat.x * z2;
        float yz2 = quat.y * z2;
        float wx2 = quat.w * x2;
        float wy2 = quat.w * y2;
        float wz2 = quat.w * z2;

        glm::vec3 res;
        res.x = (1.f - (yy2 + zz2)) * vec.x + (xy2 - wz2) * vec.y + (xz2 + wy2) * vec.z;
        res.y = (xy2 + wz2) * vec.x + (1.f - (xx2 + zz2)) * vec.y + (yz2 - wx2) * vec.z;
        res.z = (xz2 - wy2) * vec.x + (yz2 + wx2) * vec.y + (1.f - (xx2 + yy2)) * vec.z;
        return res;
    }

    quat EulerToQuat(vec3 euler)
    {
        float deg2rad = (3.14f * 2.0f) / 360.0f;
        euler *= deg2rad;

        float cy = cos(euler.z * 0.5);
        float sy = sin(euler.z * 0.5);
        float cp = cos(euler.x * 0.5);
        float sp = sin(euler.x * 0.5);
        float cr = cos(euler.y * 0.5);
        float sr = sin(euler.y * 0.5);

        glm::quat q;
        q.w = cr * cp * cy + sr * sp * sy;
        q.x = cr * sp * cy + sr * cp * sy;
        q.y = sr * cp * cy - cr * sp * sy;
        q.z = cr * cp * sy - sr * sp * cy;
        return q;
    }
}