//
// Created by Ronan on 12/01/2021.
//

#include "Mesh.h"

Mesh::Mesh() {
	glGenVertexArrays(1, $_vao); //Generate VAO BUFFER
	glBindVertexArray($_vao); // Bind current vao

	glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, 0); //Set parameters 0 format
	glEnableVertexAttribArray(0); // Start
	glVertexAttribBinding(0, 0);// take data form buffer 0


	glVertexAttribFormat(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat)); //Set parameters 1 format
	glEnableVertexAttribArray(1); // Start
	glVertexAttribBinding(1, 0);// take data form buffer 1

	glBindVertexArray(0); //Unbind VAO


}

void Mesh::setVertices(float *vertices, size_t size) {

	glCreateBuffers(1, &_vbo);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, _vao);
	glBindVertexBuffer(0, _vbo, 0,8*sizeof(GLfloat));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::setIndices(uint16_t *indices, size_t size) {

}


