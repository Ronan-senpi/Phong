#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Mesh.h"
#include "Shader.h"
#include "Dragon.h"

void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

//Rezise
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
	glViewport(0, 0, width, height);
}

void messageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message,
                     const void *userParam) {
	switch (severity) {
		case GL_DEBUG_SEVERITY_HIGH:
			std::cout << "ERROR " << id << ": " << message << std::endl;

		case GL_DEBUG_SEVERITY_MEDIUM:
			std::cout << "WARNING " << id << ": " << message << std::endl;
			break;
		case GL_DEBUG_SEVERITY_LOW:
			std::cout << "INFO " << id << ": " << message << std::endl;
			break;
	}
}

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

	GLFWwindow *window = glfwCreateWindow(800, 600, "cpp-base", nullptr, nullptr);


	if (window == nullptr) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glViewport(0, 0, 800, 600); // Zone de rendu

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); //Rezise

	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glEnable(GL_DEPTH_TEST);
	glDebugMessageCallback(messageCallback, nullptr);

	std::cout << "Driver: " << glGetString(GL_VERSION) << "\n";
	std::cout << "GPU: " << glGetString(GL_RENDERER) << "\n";

	Shader myShader("myShader");
	Mesh dragon;
	dragon.setVertices(DragonVertices, sizeof(DragonVertices) / sizeof(float));
	dragon.setIndices(DragonIndices, sizeof(DragonIndices) / sizeof(uint16_t));

	while (!glfwWindowShouldClose(window)) {
		// Envents
		glfwPollEvents();

		// Inputs
		processInput(window);

		//Rendering
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		myShader.bind();
		//Displays Position
		glm::vec3 pos(0.0f, -5.0f, 0.0f);


		glm::mat4 model = glm::translate(pos)// Position in word space
		                  * glm::eulerAngleXYZ(0.0f, (float)glfwGetTime() * 2.0f, 0.0f) // Model angle
		                  * glm::scale(glm::vec3(1.0f, 1.0f, 1.0f)); //scale

		//Update for move cam
		glm::vec3 camPos(-20.0f, 5.0f, 0.0f);
		glm::mat4 view = glm::lookAt(camPos,
		                             glm::vec3(0.0f, 0.0f, 0.0f),
		                             glm::vec3(0.0f, 1.0f, 0.0f));
		GLint viewport[4];
		glGetIntegerv(GL_VIEWPORT, viewport);
		GLfloat ratio = (float) viewport[2] / (float) viewport[3];
		glm::mat4 projection = glm::perspective(glm::radians(60.0f), ratio, 0.01f, 100.0f);

		glm::mat4 mvp = projection * view * model;

		glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(mvp));
		glUniformMatrix4fv(1, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(2, 1, glm::value_ptr(camPos));

		//Use mesh
		dragon.bind();
		glDrawElements(GL_TRIANGLES, sizeof(DragonIndices) / sizeof(uint16_t), GL_UNSIGNED_SHORT, nullptr);
		dragon.unbind();

		//Draw mesh

		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return 0;
}
