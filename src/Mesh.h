//
// Created by Ronan on 12/01/2021.
//

#ifndef PHONG_MESH_H
#define PHONG_MESH_H

#include <cstdint>
#include <glad/glad.h>

class Mesh {
public:
	Mesh();

	void setVertices(float *vertices, size_t size);

	void setIndices(uint16_t *indices, size_t size);

private:
	GLuint _vao; // Vertex array objet (setup attrib shader)
	GLuint _vbo; // Vertices array object Buffer
	GLushort _ibo; // Index buffer object (index VBO)
};


#endif //PHONG_MESH_H
