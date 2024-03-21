#include "Entity2D.h"

void ToToEng::Entity2D::setOffset(vec2 offset)
{
    this->uvOffset = offset;

    updateVao();
}

void ToToEng::Entity2D::setScale(vec2 scale)
{
    this->uvScale = scale;

    updateVao();
}

ToToEng::Entity2D::Entity2D(Renderer* renderer): Entity(renderer)
{
    vertexQty = 4;
    indexQty = 6;
    id = 1;

    transform.setScale({100.f, 100.f, 100.f});

    positions = new float[vertexQty * 3]
    {
        -.5f, -.5f, 0.f,
        .5f, -.5f, 0.f,
        -.5f, .5f, 0.f,
        .5f, .5f, 0.f
    };

    colors = new float[vertexQty * 4]
    {
        1.f, 1.f, 1.f, 1.f,
        1.f, 1.f, 1.f, 1.f,
        1.f, 1.f, 1.f, 1.f,
        1.f, 1.f, 1.f, 1.f
    };

    textureCoords = new float[vertexQty * 2]
    {
        0.f, 1.f,
        1.f, 1.f,
        0.f, 0.f,
        0.f, 1.f
    };

    indices = new unsigned int[indexQty]
    {
        0, 1, 2,
        1, 2, 3
    };

    uvOffset = {0, 0};
    uvScale = {1, 1};

    updateVao();

    collider = new BoxCollider2D({0.f, 0.f}, {1.f, 1.f}, &transform);
}

ToToEng::Entity2D::~Entity2D()
{
    delete collider;
}

void ToToEng::Entity2D::updateVao()
{
    delete vertices;

    vertices = new float[vertexQty * 9];

    for (unsigned int i = 0; i < vertexQty; i++)
    {
        vertices[9 * i] = positions[i * 3];
        vertices[9 * i + 1] = positions[i * 3 + 1];
        vertices[9 * i + 2] = positions[i * 3 + 2];

        vertices[9 * i + 3] = colors[i * 4];
        vertices[9 * i + 4] = colors[i * 4 + 1];
        vertices[9 * i + 5] = colors[i * 4 + 2];
        vertices[9 * i + 6] = colors[i * 4 + 3];

        vertices[9 * i + 7] = textureCoords[i * 2] * uvScale.x + uvOffset.x;
        vertices[9 * i + 8] = textureCoords[i * 2 + 1] * uvScale.y + uvOffset.y;
    }

    genBuffers();
}

void ToToEng::Entity2D::draw()
{
}