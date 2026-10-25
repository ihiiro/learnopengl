#include "include/glad/glad.h"
#include "include/GLFW/glfw3.h"
#include <string.h>
#include <iostream>

#include "shader.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);


int main()
{
    // initialize glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create window object
    GLFWwindow* window = glfwCreateWindow(800, 600, "learnopengl", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // initialize glad
    if (!gladLoadGLLoader ( ( GLADloadproc )glfwGetProcAddress ) )
    {
        std::cout << "Failed to initialize glad" << std::endl;
        return -1;
    }

    // tell opengl size of viewing window
    glViewport(0, 0, 800, 600);

    // register resize callback
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    Shader ourShader("shaders/vshader.glsl", "shaders/fshader.glsl");

    float vertices[] = {
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right 
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
        0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f // top
    };
    // VERTEX ARRAY OBJECT
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // VERTEX BUFFER OBJECT
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    

    // tell opengl the in-memory VBO positional data layout
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // now the color layout
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
        (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);



    // render loop
    while (!glfwWindowShouldClose(window))
    {
        // input processing section
        processInput(window);

        glClearColor(.2f, .3f, .3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // rendering section
        ourShader.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);


        
        

        // swap buffers and check for events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // cleanup
    glfwTerminate();

    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}