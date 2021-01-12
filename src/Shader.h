//
// Created by Ronan on 11/01/2021.
//
#ifndef PHONG_SHADER_H
#define PHONG_SHADER_H


#include <string>
#include <glad/glad.h>

class Shader {
public:
	Shader(const std::string& name);
	~Shader();
	void bind();
	GLuint getId() const;
private:
	GLuint _id;
	static GLuint loadShader(const std::string& path, GLenum type);
};


#endif //PHONG_SHADER_H
