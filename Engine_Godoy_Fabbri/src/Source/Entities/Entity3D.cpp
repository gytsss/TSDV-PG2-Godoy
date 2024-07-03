#include "Entities/Entity3D.h"

ToToEng::Entity3D::Entity3D(Renderer* renderer): Entity(renderer)
{
    vertexQty = 24;
    indexQty = 36;
    id = 1;


    positions = new float[vertexQty * 3]
    {
        //Back
        -.5f, -.5f, -.5f,
        .5f, -.5f, -.5f,
        -.5f, .5f, -.5f,
        .5f, .5f, -.5f,
        
        //Right
        .5f, -.5f, -.5f,
        .5f, -.5f, .5f,
        .5f, .5f, -.5f,
        .5f, .5f, .5f,
        
        //Top
        -.5f, .5f, -.5f,
        .5f, .5f, -.5f,
        -.5f, .5f, .5f,
        .5f, .5f, .5f,
        
        //Front
        -.5f, -.5f, .5f,
        .5f, -.5f, .5f,
        -.5f, .5f, .5f,
        .5f, .5f, .5f,
        
        //Bottom
        -.5f, -.5f, -.5f,
        .5f, -.5f, -.5f,
        -.5f, -.5f, .5f,
        .5f, -.5f, .5f,
        
        //Left
        -.5f, -.5f, -.5f,
        -.5f, .5f, -.5f,
        -.5f, -.5f, .5f,
        -.5f, .5f, .5f
    };

    colors = new float[vertexQty * 4]
    {
        0.f, 1.f, 0.f, 1.f,
        0.f, 1.f, 0.f, 1.f,
        0.f, 1.f, 0.f, 1.f,
        0.f, 1.f, 0.f, 1.f,

        0.f, 1.f, 0.f, 1.f,
        0.f, 1.f, 0.f, 1.f,
        0.f, 1.f, 0.f, 1.f,
        0.f, 1.f, 0.f, 1.f,

        0.f, 1.f, 0.f, 1.f,
        0.f, 1.f, 0.f, 1.f,
        0.f, 1.f, 0.f, 1.f,
        0.f, 1.f, 0.f, 1.f,

        0.f, 1.f, 0.f, 1.f,
        0.f, 1.f, 0.f, 1.f,
        0.f, 1.f, 0.f, 1.f,
        0.f, 1.f, 0.f, 1.f,

        0.f, 1.f, 0.f, 1.f,
        0.f, 1.f, 0.f, 1.f,
        0.f, 1.f, 0.f, 1.f,
        0.f, 1.f, 0.f, 1.f,

        0.f, 1.f, 0.f, 1.f,
        0.f, 1.f, 0.f, 1.f,
        0.f, 1.f, 0.f, 1.f,
        0.f, 1.f, 0.f, 1.f
    };

    textureCoords = new float[vertexQty * 2]
    {
        0.f, 1.f,
        1.f, 1.f,
        0.f, 0.f,
        0.f, 1.f,

        0.f, 1.f,
        1.f, 1.f,
        0.f, 0.f,
        0.f, 1.f,

        0.f, 1.f,
        1.f, 1.f,
        0.f, 0.f,
        0.f, 1.f,

        0.f, 1.f,
        1.f, 1.f,
        0.f, 0.f,
        0.f, 1.f,

        0.f, 1.f,
        1.f, 1.f,
        0.f, 0.f,
        0.f, 1.f,

        0.f, 1.f,
        1.f, 1.f,
        0.f, 0.f,
        0.f, 1.f,
    };

    normals = new float[vertexQty * 3]
    {
        //Back
        0.f, 0.f, -1.f,
        0.f, 0.f, -1.f,
        0.f, 0.f, -1.f,
        0.f, 0.f, -1.f,

        //Right
        1.f, 0.f, 0.f,
        1.f, 0.f, 0.f,
        1.f, 0.f, 0.f,
        1.f, 0.f, 0.f,

        //Top
        0.f, 1.f, 0.f,
        0.f, 1.f, 0.f,
        0.f, 1.f, 0.f,
        0.f, 1.f, 0.f,
        
        //Front
        0.f, 0.f, 1.f,
        0.f, 0.f, 1.f,
        0.f, 0.f, 1.f,
        0.f, 0.f, 1.f,

        //Bottom
        0.f, -1.f, 0.f,
        0.f, -1.f, 0.f,
        0.f, -1.f, 0.f,
        0.f, -1.f, 0.f,

        //Left
        -1.f, 0.f, 0.f,
        -1.f, 0.f, 0.f,
        -1.f, 0.f, 0.f,
        -1.f, 0.f, 0.f
    };

    indices = new unsigned int[indexQty]
    {
        0, 1, 2,
        1, 2, 3,

        4, 5, 6,
        5, 6, 7,

        8, 9, 10,
        9, 10, 11,

        12, 13, 14,
        13, 14, 15,

        16, 17, 18,
        17, 18, 19,

        20, 21, 22,
        21, 22, 23
    };

    updateVao3D();
}

ToToEng::Entity3D::~Entity3D()
{
}

void ToToEng::Entity3D::draw()
{
    //renderer->drawShape(VAO, indexQty, color, transform.getTransformMatrix());
    renderer->drawLightEntity3D(VAO, indexQty, color, transform.getTransformMatrix());
    
}
