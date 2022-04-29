#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Camera.h"
#include "Cube.h"


#include <iostream>
#include <string>

struct CursPos
{
    double xpos;
    double ypos;
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, Camera* camera, double xpos, double ypos)
{
    //camera->camera_mouse_callback(window, xpos, ypos);
}

void ProcessInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

int main(void)
{
    GLFWwindow* window;
    Camera camera;
    CursPos cursPos;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1200, 900, "OpenGL Demos", NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to intialize glad" << std::endl;
        return -1;
    }

    glViewport(0, 0, 1200, 900);

    glEnable(GL_DEPTH_TEST);

    Cube cube;

    Shader TriShader("shaders/vertexshader.glsl", "shaders/fragmentshader.glsl");

    double lastframe = 0.0f;
    double currentframe;
    float deltaTime;
    

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glfwGetCursorPos(window, &cursPos.xpos, &cursPos.ypos);
        currentframe = glfwGetTime();
        deltaTime = float(currentframe) - float(lastframe);
        lastframe = currentframe;

        camera.ProcessInput(window, deltaTime);
        camera.camera_mouse_callback(window, cursPos.xpos, cursPos.ypos);

        /*check to see if escape key had been pressed*/
        ProcessInput(window);

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        glm::mat4 model(1.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1200.0f / 900.0f, 0.1f, 100.0f);

        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));

        TriShader.use();
        TriShader.setMat4f("model", model);
        TriShader.setMat4f("view", view);
        TriShader.setMat4f("projection", projection);
        cube.Draw();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}