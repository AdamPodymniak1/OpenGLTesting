#include <string>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include "Vertex.h"
#include "ShapeGenerator.h"

GLuint compileShader(GLenum type, const char* src)
{
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char info[512];
        glGetShaderInfoLog(shader, 512, nullptr, info);
        std::cout << "Shader compile error:\n" << info << std::endl;
    }

    return shader;
}

GLuint linkProgram(GLuint vertexShader, GLuint fragmentShader)
{
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        char info[512];
        glGetProgramInfoLog(program, 512, nullptr, info);
        std::cout << "Shader linking error:\n" << info << std::endl;
    }
    return program;
}

const char* ReadShaderCode(const char* fileName) {
    std::ifstream file(fileName, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        std::cout << "File loading failed\n";
        exit(1);
    }

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    char* buffer = new char[size + 1];
    if (!file.read(buffer, size)) {
        std::cout << "File read failed\n";
        delete[] buffer;
        exit(1);
    }

    buffer[size] = '\0';
    return buffer;
}

int main()
{
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Chuja Chuja", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "GLEW init failed\n";
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    ShapeData shape = ShapeGenerator::makeCube();

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, shape.vertexBufferSize(), shape.vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (char*)(3 * sizeof(float)));

    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, shape.indexBufferSize(), shape.indices, GL_STATIC_DRAW);

    GLuint transformationMatrixBuffer;
    glGenBuffers(1, &transformationMatrixBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, transformationMatrixBuffer);

    glm::mat4 projectionMatrix = glm::perspective(45.0f, ((float)width) / height, 0.1f, 10.0f);
    glm::mat4 fullTransform[] = {
        projectionMatrix * glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, -4.0f))* glm::rotate(glm::mat4(1.0f), 36.0f, glm::vec3(1.0f, 0.0f, 1.0f)),
        projectionMatrix * glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, -7.0f)) * glm::rotate(glm::mat4(1.0f), 54.0f, glm::vec3(0.0f, 1.0f, 0.0f)),
    };

    GLuint matrixVBO;
    glGenBuffers(1, &matrixVBO);
    glBindBuffer(GL_ARRAY_BUFFER, matrixVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(fullTransform), &fullTransform[0], GL_STATIC_DRAW);

    for (int i = 0; i < 4; i++) {
        glEnableVertexAttribArray(2 + i);
        glVertexAttribPointer(2 + i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4) * i));
        glVertexAttribDivisor(2 + i, 1);
    }

    const char* vertexShaderSource = ReadShaderCode("vertex.glsl");

    const char* fragmentShaderSource = ReadShaderCode("fragment.glsl");

    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    GLuint shaderProgram = linkProgram(vertexShader, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);

        glUseProgram(shaderProgram);

        glBindVertexArray(VAO);
        glDrawElementsInstanced(GL_TRIANGLES, shape.numIndecies, GL_UNSIGNED_SHORT, 0, 2);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    shape.cleanup();

    glfwTerminate();
    return 0;
}