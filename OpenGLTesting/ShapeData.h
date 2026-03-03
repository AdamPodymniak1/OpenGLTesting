#pragma once
#include <GL/glew.h>
#include "Vertex.h"

struct ShapeData {
	ShapeData() : 
		vertices(0), numVertices(0),
		indices(0), numIndecies(0) {}
	Vertex* vertices;
	unsigned int numVertices;
	unsigned short* indices;
	unsigned int numIndecies;
	GLsizeiptr vertexBufferSize() const {
		return numVertices * sizeof(Vertex);
	}
	GLsizeiptr indexBufferSize() const {
		return numIndecies * sizeof(unsigned short);
	}
	void cleanup() {
		delete[] vertices;
		delete[] indices;
		numVertices = numIndecies = 0;
	}
};