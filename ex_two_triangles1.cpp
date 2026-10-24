#include "include/glad/glad.h"
#include "include/GLFW/glfw3.h"
#include <string.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

const char *vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\0";

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

    // GLSL
    // vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // check if compilation of vertex shader was successful
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" <<
                infoLog << std::endl;
    }

    memset(infoLog, 0, sizeof(infoLog));

    // fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" <<
                infoLog << std::endl;
    }

    memset(infoLog, 0, sizeof(infoLog));

    // shader program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // we don't need the shader objects after linking them to the program
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" <<
                infoLog << std::endl;
    }


    float vertices[] = {
        -1.0f, -0.5f, 0.0f,
        0.0f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,

        0.0f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        1.0f, -0.5f, 0.0f,
    };
    // VAO for the first triangle
    unsigned int VAO0;
    glGenVertexArrays(1, &VAO0);
    glBindVertexArray(VAO0);

    // VBO for the first triangle
    unsigned int VBO0;
    glGenBuffers(1, &VBO0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO0);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // configure VAO for the first triangle
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); 
    glEnableVertexAttribArray(0);

    // VAO for the second triangle
    unsigned int VAO1;
    glGenVertexArrays(1, &VAO1);
    glBindVertexArray(VAO1);

    // VBO for the second triangle
    unsigned int VBO1;
    glGenBuffers(1, &VBO1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float),
        &vertices[9], GL_STATIC_DRAW);
    
    // configure VAO for the second triangle
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); 
    glEnableVertexAttribArray(0);



    // render loop
    while (!glfwWindowShouldClose(window))
    {
        // input processing section
        processInput(window);

        glClearColor(.2f, .3f, .3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // rendering section
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO0);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(VAO1);
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