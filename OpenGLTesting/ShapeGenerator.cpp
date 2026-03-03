#include <glm/glm/glm.hpp>
#include "ShapeGenerator.h"
#include "Vertex.h"

ShapeData ShapeGenerator::makeTriangle() {
    ShapeData ret;

    Vertex vertices[] = {
        glm::vec3(0.0f,  1.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),

        glm::vec3(-1.0f, -1.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),

        glm::vec3(1.0f, -1.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),
    };

    ret.numVertices = sizeof(vertices) / sizeof(*vertices);
    ret.vertices = new Vertex[ret.numVertices];
    memcpy(ret.vertices, vertices, sizeof(vertices));

    unsigned short indices[] = {
        0,1,2,
    };

    ret.numIndecies = sizeof(indices) / sizeof(*indices);
    ret.indices = new unsigned short[ret.numIndecies];
    memcpy(ret.indices, indices, sizeof(indices));

    return ret;
}

ShapeData ShapeGenerator::makeCube() {
    ShapeData ret;
    Vertex vertices[] = {
        glm::vec3(-1.0f, +1.0f, +1.0f),
        glm::vec3(+1.0f, +0.0f, +0.0f),
        glm::vec3(+1.0f, +1.0f, +1.0f),
        glm::vec3(+0.0f, +1.0f, +0.0f),
        glm::vec3(+1.0f, +1.0f, -1.0f),
        glm::vec3(+0.0f, +0.0f, +1.0f),
        glm::vec3(-1.0f, +1.0f, -1.0f),
        glm::vec3(+1.0f, +1.0f, +1.0f),

        glm::vec3(-1.0f, +1.0f, -1.0f),
        glm::vec3(+1.0f, +0.0f, +1.0f),
        glm::vec3(+1.0f, +1.0f, -1.0f),
        glm::vec3(+0.0f, +0.5f, +0.2f),
        glm::vec3(+1.0f, -1.0f, -1.0f),
        glm::vec3(+0.8f, +0.6f, +0.4f),
        glm::vec3(-1.0f, -1.0f, -1.0f),
        glm::vec3(+0.3f, +1.0f, +0.5f),

        glm::vec3(+1.0f, +1.0f, -1.0f),
        glm::vec3(+0.2f, +0.5f, +0.2f),
        glm::vec3(+1.0f, +1.0f, +1.0f),
        glm::vec3(+0.9f, +0.3f, +0.7f),
        glm::vec3(+1.0f, -1.0f, +1.0f),
        glm::vec3(+0.3f, +0.7f, +0.5f),
        glm::vec3(+1.0f, -1.0f, -1.0f),
        glm::vec3(+0.5f, +0.7f, +0.5f),

        glm::vec3(-1.0f, +1.0f, +1.0f),
        glm::vec3(+0.7f, +0.8f, +0.2f),
        glm::vec3(-1.0f, +1.0f, -1.0f),
        glm::vec3(+0.5f, +0.7f, +0.3f),
        glm::vec3(-1.0f, -1.0f, -1.0f),
        glm::vec3(+0.4f, +0.7f, +0.7f),
        glm::vec3(-1.0f, -1.0f, -1.0f),
        glm::vec3(+0.2f, +0.5f, +1.0f),

        glm::vec3(+1.0f, +1.0f, +1.0f),
        glm::vec3(+0.6f, +1.0f, +0.7f),
        glm::vec3(-1.0f, +1.0f, +1.0f),
        glm::vec3(+0.6f, +0.4f, +0.8f),
        glm::vec3(-1.0f, -1.0f, +1.0f),
        glm::vec3(+0.2f, +0.8f, +0.7f),
        glm::vec3(+1.0f, -1.0f, +1.0f),
        glm::vec3(+0.2f, +0.7f, +1.0f),

        glm::vec3(+1.0f, -1.0f, -1.0f),
        glm::vec3(+0.8f, +0.3f, +0.7f),
        glm::vec3(-1.0f, -1.0f, -1.0f),
        glm::vec3(+0.8f, +0.9f, +0.5f),
        glm::vec3(-1.0f, -1.0f, +1.0f),
        glm::vec3(+0.5f, +0.8f, +0.5f),
        glm::vec3(+1.0f, -1.0f, +1.0f),
        glm::vec3(+0.9f, +1.0f, +0.2f),
    };
    ret.numVertices = sizeof(vertices) / sizeof(*vertices);
    ret.vertices = new Vertex[ret.numVertices];
    memcpy(ret.vertices, vertices, sizeof(vertices));

    unsigned short indices[] = {
            0,  1,  2,  0,  2,  3,
            4,  5,  6,  4,  6,  7,
            8,  9, 10,  8, 10, 11,
           12, 13, 14, 12, 14, 15,
           16, 17, 18, 16, 18, 19,
           20, 22, 21, 20, 23, 22,
    };

    ret.numIndecies = sizeof(indices) / sizeof(*indices);
    ret.indices = new GLushort[ret.numIndecies];
    memcpy(ret.indices, indices, sizeof(indices));

    return ret;
}