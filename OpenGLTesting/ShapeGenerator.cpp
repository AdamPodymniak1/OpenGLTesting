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
