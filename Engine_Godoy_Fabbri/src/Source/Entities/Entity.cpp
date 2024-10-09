#include "Entities/Entity.h"

#include <glm/fwd.hpp>

namespace ToToEng
{
	Entity::Entity(Renderer* renderer)
	{
		this->renderer = renderer;

		isTrigger = false;

		color = { 0, 1, 0, 1 };

		vertices = new float();
		//parent = nullptr;
		
		transform = Transform();
	}

	Entity::~Entity()
	{
		delete positions;
		delete colors;
		delete vertices;
		delete indices;
		delete normals;

		Entity::deleteBuffers();
	}

	void Entity::genBuffers()
	{
		renderer->genVertexBuffer(VBO, VAO, vertices, id, vertexQty);
		renderer->genIndexBuffer(IBO, indices, id, indexQty);
	}
	void Entity::genBuffers3D()
	{
		renderer->genVertexBuffer3D(VBO, VAO, vertices, id, vertexQty);
		renderer->genIndexBuffer(IBO, indices, id, indexQty);
	}

	void Entity::deleteBuffers()
	{
		renderer->deleteBuffers(VBO, IBO, VAO, id);
	}

	void Entity::update()
	{
	}

	void Entity::setColor(vec4 color)
	{
		this->color = color;
	}

	void Entity::setIsTrigger(bool isTrigger)
	{
		this->isTrigger = isTrigger;
	}

	vec4 Entity::getColor()
	{
		return color;
	}

	bool Entity::getIsTrigger()
	{
		return isTrigger;
	}

	void Entity::updateVao()
	{
		delete vertices;

		vertices = new float[vertexQty * 9];

		int positionSize = 3;
		int colorsSize = 4;
		int textureCoordsSize = 2;
		
		for (unsigned int i = 0; i < vertexQty; i++)
		{
			
			vertices[9 * i] = positions[i * positionSize];
			vertices[9 * i + 1] = positions[i * positionSize + 1];
			vertices[9 * i + 2] = positions[i * positionSize + 2];

			vertices[9 * i + 3] = colors[i * colorsSize];
			vertices[9 * i + 4] = colors[i * colorsSize + 1];
			vertices[9 * i + 5] = colors[i * colorsSize + 2];
			vertices[9 * i + 6] = colors[i * colorsSize + positionSize];

			vertices[9 * i + 7] = textureCoords[i * textureCoordsSize];
			vertices[9 * i + 8] = textureCoords[i * textureCoordsSize + 1];
		}

		
		genBuffers();
	}
	void Entity::updateVao3D()
	{
		delete vertices;

		vertices = new float[vertexQty * 12];

		int positionSize = 3;
		int colorsSize = 4;
		int textureCoordsSize = 2;
		int normalsSize = 3;

		for (unsigned int i = 0; i < vertexQty; i++)
		{
			vertices[12 * i] = positions[i * positionSize];
			vertices[12 * i + 1] = positions[i * positionSize + 1];
			vertices[12 * i + 2] = positions[i * positionSize + 2];

			vertices[12 * i + 3] = colors[i * colorsSize];
			vertices[12 * i + 4] = colors[i * colorsSize + 1];
			vertices[12 * i + 5] = colors[i * colorsSize + 2];
			vertices[12 * i + 6] = colors[i * colorsSize + positionSize];

			vertices[12 * i + 7] = textureCoords[i * textureCoordsSize];
			vertices[12 * i + 8] = textureCoords[i * textureCoordsSize + 1];

			vertices[12 * i + 9] = normals[i * normalsSize];
			vertices[12 * i + 10] = normals[i * normalsSize + 1];
			vertices[12 * i + 11] = normals[i * normalsSize + 2];
		}

		genBuffers3D();
	}

	// glm::mat4 Entity::getGlobMat()
	// {
	// 	if (parent == nullptr)
	// 		return transform.getLocalModel();
	// 	else
	// 		getGlobMat(parent)* transform.getLocalModel();
	// }
	//
	// glm::mat4 Entity::getGlobMat(Entity* matParent)
	// {
	// 	if (matParent->parent == nullptr)
	// 		return transform.getLocalModel();
	// 	else
	// 		return getGlobMat(matParent->parent) * transform.getLocalModel();
	// }
	//
	// glm::vec3 Entity::GetPosGlobalMat()
	// {
	// 	vec3 text1 = GetPos(transform.getLocalModel());
	// 	vec3 text2 = GetPos(transform.getLocalModel());
	// 	text2 = GetPos(transform.getWorldModel());
	//
	//
	// 	return GetPos(transform.getWorldModel());
	// }
	//
	// glm::vec3 Entity::GetPos(glm::mat4 mat)
	// {
	// 	return glm::vec3(mat[3][0], mat[3][1], mat[3][2]);
	// }
	//
	// glm::vec3 Entity::GetRot(glm::mat4 mat)
	// {
	// 	return ToEulerRad(GetRotationByMatrix(mat));
	// }
	//
	// glm::vec3 Entity::GetScale(glm::mat4 mat)
	// {
	// 	glm::vec4 m0 = glm::vec4(mat[0].x, mat[0].y, mat[0].z, mat[0].w);
	// 	glm::vec4 m1 = glm::vec4(mat[1].x, mat[1].y, mat[1].z, mat[1].w);
	// 	glm::vec4 m2 = glm::vec4(mat[2].x, mat[2].y, mat[2].z, mat[2].w);
	// 	return glm::vec3(glm::length(m0), glm::length(m1), glm::length(m2));
	//
	// }
	//
	// glm::vec3 Entity::ToEulerRad(glm::quat rot)
	// {
	// 	float sqw = rot.w * rot.w;
	// 	float sqx = rot.x * rot.x;
	// 	float sqy = rot.y * rot.y;
	// 	float sqz = rot.z * rot.z;
	// 	float unit = sqx + sqy + sqz + sqw;
	// 	float test = rot.x * rot.w - rot.y * rot.z;
	//
	// 	glm::vec3 v = glm::vec3();
	//
	// 	if (test > 0.4995f * unit)
	// 	{
	// 		v.y = 2.f * atan2(rot.y, rot.x);
	// 		v.x = glm::pi<float>() / 2.f;
	// 		v.z = 0.f;
	//
	// 		return NormalizeAngles(v * 57.29578f);
	// 	}
	// 	if (test < -0.4995f * unit)
	// 	{
	// 		v.y = -2.f * atan2(rot.y, rot.x);
	// 		v.x = -glm::pi<float>() / 2.f;
	// 		v.z = 0.f;
	//
	// 		return NormalizeAngles(v * 57.29578f);
	// 	}
	//
	// 	glm::vec4 q = glm::vec4(rot.w, rot.z, rot.x, rot.y);
	// 	v.y = atan2(2.f * q.x * q.w + 2.f * q.y * q.z, 1.f - 2.f * (q.z * q.z + q.w * q.w));
	// 	v.x = asin(2.f * (q.x * q.z - q.w * q.y));
	// 	v.z = atan2(2.f * q.x * q.y + 2.f * q.z * q.w, 1.f - 2.f * (q.y * q.y + q.z * q.z));
	//
	// 	return NormalizeAngles(v * 57.29578f);
	// }
	//
	// glm::quat Entity::GetRotationByMatrix(glm::mat4 mat)
	// {
	// 	glm::vec3 s = GetScale(mat);
	//
	// 	float m00 = mat[0].x / s.x;
	// 	float m01 = mat[0].y / s.y;
	// 	float m02 = mat[0].z / s.z;
	// 	float m10 = mat[1].x / s.x;
	// 	float m11 = mat[1].y / s.y;
	// 	float m12 = mat[1].z / s.z;
	// 	float m20 = mat[2].x / s.x;
	// 	float m21 = mat[2].y / s.y;
	// 	float m22 = mat[2].z / s.z;
	//
	// 	glm::quat q = glm::quat();
	// 	q.w = glm::sqrt(glm::max(0.f, 1.f + m00 + m11 + m22)) / 2.f;
	// 	q.x = glm::sqrt(glm::max(0.f, 1.f + m00 - m11 - m22)) / 2.f;
	// 	q.y = glm::sqrt(glm::max(0.f, 1.f - m00 + m11 - m22)) / 2.f;
	// 	q.z = glm::sqrt(glm::max(0.f, 1.f - m00 - m11 + m22)) / 2.f;
	// 	q.x *= glm::sign(q.x * (m21 - m12));
	// 	q.y *= glm::sign(q.y * (m02 - m20));
	// 	q.z *= glm::sign(q.z * (m10 - m01));
	//
	// 	float qMagnitude = glm::sqrt(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z);
	// 	q.w /= qMagnitude;
	// 	q.x /= qMagnitude * -1;
	// 	q.y /= qMagnitude * -1;
	// 	q.z /= qMagnitude * -1;
	//
	// 	return q;
	// }
	//
	// glm::vec3 Entity::NormalizeAngles(glm::vec3 angles)
	// {
	// 	angles.x = NormalizeAngle(angles.x);
	// 	angles.y = NormalizeAngle(angles.y);
	// 	angles.z = NormalizeAngle(angles.z);
	//
	// 	return angles;
	// }
	//
	// float Entity::NormalizeAngle(float angle)
	// {
	// 	while (angle > 360.f)
	// 		angle -= 360.f;
	// 	while (angle < 0.f)
	// 		angle += 360.f;
	//
	// 	return angle;
	// }
	//
	// void Entity::SetParent(Entity* parent)
	// {
	// 	this->parent = parent;
	// }
	// void Entity::setChildren(std::vector<Entity*> children)
	// {
	// 	this->children = children;
	// }
	// void Entity::AddChildren(Entity* children)
	// {
	// 	this->children.push_back(children);
	// }
	//
	// void Entity::setWorldModelWithParentModel(glm::mat4 parentModel)
	// {
	// 	transform.setParentModel(parentModel);
	//
	// 	updateModelMatrix();
	// }
	//
	// void Entity::updateModelMatrix()
	// {
	// 	transform.updateLocalTransformMatrix();
	// 	if (parent != NULL)
	// 	{
	// 		transform.setLocalModel(transform.getLocalModel());
	// 		transform.setWorldModel(transform.getParentModel() * transform.getLocalModel());
	// 	}
	// 	else
	// 	{
	// 		transform.setWorldModel(transform.getLocalModel());
	// 	}
	// 	setTransformations();
	//
	// }
	//
	// void Entity::setTransformations()
	// {
	// 	// if (meshes.size() > 0)
	// 	// {
	// 	// 	volume = new MikkaiEngine::aabb(originVolume->min, originVolume->max);
	// 	// 	volume->update(originVolume->min, originVolume->max);
	// 	// }
	//
	// 	for (int i = 0; i < children.size(); i++)
	// 	{
	// 		children[i]->setWorldModelWithParentModel(transform.getWorldModel());
	// 		children[i]->setTransformations();
	//
	// 		updateAABBWithChildren(children[i]);
	// 	}
	//
	// 	UpdateExtremos();
	// }
	//
	// void Entity::UpdateExtremos()
	// {
	// 	vec3 center = transform.getPos();
	// 	vec3 extend = vec3(0);
	// 	// if (getVolume() != nullptr)
	// 	// {
	// 	// 	center = getVolume()->GetGlobalVolume(getTransform()->getWorldModel()).center;
	// 	// 	extend = getVolume()->GetGlobalVolume(getTransform()->getWorldModel()).extents;
	// 	// }
	// 	extremos.clear();
	// 	extremos.push_back(center + vec3(extend.x, extend.y, extend.z));
	// 	extremos.push_back(center + vec3(extend.x, extend.y, -extend.z));
	// 	extremos.push_back(center + vec3(extend.x, -extend.y, extend.z));
	// 	extremos.push_back(center + vec3(-extend.x, extend.y, extend.z));
	// 	extremos.push_back(center + vec3(extend.x, -extend.y, -extend.z));
	// 	extremos.push_back(center + vec3(-extend.x, -extend.y, extend.z));
	// 	extremos.push_back(center + vec3(-extend.x, extend.y, -extend.z));
	// 	extremos.push_back(center + vec3(-extend.x, -extend.y, -extend.z));
	// }
	//
	// void Entity::updateAABBWithChildren(Entity* child)
	// {
	// 	// if (child->getVolume() != NULL)
	// 	// {
	// 	// 	MikkaiEngine::aabb* childVolume = child->getVolume();
	// 	//
	// 	// 	glm::vec3 minAABB = glm::vec3(std::numeric_limits<float>::max());
	// 	// 	glm::vec3 maxAABB = glm::vec3(std::numeric_limits<float>::min());
	// 	//
	// 	// 	if (volume != NULL)
	// 	// 	{
	// 	// 		minAABB.x = glm::min(volume->min.x, childVolume->min.x);
	// 	// 		minAABB.y = glm::min(volume->min.y, childVolume->min.y);
	// 	// 		minAABB.z = glm::min(volume->min.z, childVolume->min.z);
	// 	//
	// 	// 		maxAABB.x = glm::max(volume->max.x, childVolume->max.x);
	// 	// 		maxAABB.y = glm::max(volume->max.y, childVolume->max.y);
	// 	// 		maxAABB.z = glm::max(volume->max.z, childVolume->max.z);
	// 	//
	// 	// 		volume->update(minAABB, maxAABB);
	// 	// 	}
	// 	// 	else
	// 	// 	{
	// 	// 		volume = new MikkaiEngine::aabb(childVolume->min, childVolume->max);
	// 	// 	}
	// 	// }
	// }
	
}
