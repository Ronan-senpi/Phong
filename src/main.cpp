#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "Shader.h"

void processInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

//Rezise
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "cpp-base", nullptr, nullptr);

    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600); // Zone de rendu

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); //Rezise


    Shader myShader("myShader");

    while(!glfwWindowShouldClose(window))
    {
        // Envents
        glfwPollEvents();

        // Inputs
        processInput(window);

        //Rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        myShader.bind();
		glm::translate(glm::vec3(0.0f,0.0f,0.0f)); //Position in word space;
        //Use mesh

        //Draw mesh

        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}
