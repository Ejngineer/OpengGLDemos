#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Camera.h"
#include "Cube.h"
#include "Sphere.h"
#include "Texture.h"
#include "gtx/string_cast.hpp"
#include "stb_image.h"


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
	window = glfwCreateWindow(1920, 1080, "OpenGL Demos", NULL, NULL);
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

	glViewport(0, 0, 1920, 1080);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);


	glfwWindowHint(GLFW_SAMPLES, 4);


	const float vertices[] =
	{
		//Position          //Normals       //TexCoords  //Tangents
		-1.0f,-1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f, 0.0f, 0.0f,
		 1.0f,-1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 2.0f, 0.0f, 0.0f,
		 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 2.0f, 0.0f, 0.0f,
		 
		-1.0f,-1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f, 0.0f, 0.0f,
		 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 2.0f, 0.0f, 0.0f,
		-1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 2.0f, 0.0f, 0.0f
	};

	VertexArray VAO;
	VertexBuffer VBO(vertices, sizeof(vertices));

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(sizeof(float) * 6));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(sizeof(float) * 8));
	glEnableVertexAttribArray(3);

	double lastframe = 0.0f;
	double currentframe;
	float deltaTime;

	Shader SphereShader("shaders/vertexshader.glsl", "shaders/fragmentshader.glsl");
	Shader SphereShader1("shaders/vertexshader1.glsl", "shaders/fragmentshader1.glsl");

	Sphere sphere(1.0f, 72, 72, false);
	Sphere sphere1(1.0f, 144, 144, false);

	Texture BrickWall, BrickWallNorm;
	BrickWall.Bind();
	BrickWall.Load("textures/brickwall.jpg");

	BrickWallNorm.Bind();
	BrickWallNorm.Load("textures/brickwall_normal.jpg");

	Texture RBrickWall, RBrickWallNorm;
	RBrickWall.Bind();
	RBrickWall.Load("textures/Red_Brick_Diffuse.jpg");
	RBrickWallNorm.Bind();
	RBrickWallNorm.Load("textures/Red_Brick_Normal.jpg");
	
	SphereShader.use();
	SphereShader.setInt1i("walltext", 0);
	SphereShader.setInt1i("walltextnorm", 1);


	//stbi_set_flip_vertically_on_load(1);

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
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);

		/*Use shader program*/
		SphereShader.use();
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		SphereShader.setMat4f("model", model);
		SphereShader.setMat4f("view", view);
		SphereShader.setMat4f("projection", projection);
		SphereShader.setFloat3fv("viewPos", camera.GetCameraPos());
		SphereShader.setFloat3fv("lightPos", glm::vec3(1.0f, 1.0f, 3.0f));
		SphereShader.setInt1i("Divisions", 3);

		/*Activate our textures*/
		BrickWall.ActivateTexture2D(0);
		BrickWall.Bind();
		BrickWallNorm.ActivateTexture2D(1);
		BrickWallNorm.Bind();

		//VAO.Bind();
		//glDrawArrays(GL_TRIANGLES,0, 6);
		//VAO.UnBind();
		sphere.Draw();

		SphereShader.use();
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(2.5f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		SphereShader.setMat4f("model", model);
		SphereShader.setMat4f("view", view);
		SphereShader.setMat4f("projection", projection);
		SphereShader.setFloat3fv("viewPos", camera.GetCameraPos());
		SphereShader.setFloat3fv("lightPos", glm::vec3(1.0f, 1.0f, 3.0f));
		SphereShader.setInt1i("Divisions", 2.5);
		
		RBrickWall.ActivateTexture2D(0);
		RBrickWall.Bind();
		RBrickWallNorm.ActivateTexture2D(1);
		RBrickWallNorm.Bind();
		//VAO.Bind();
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		//VAO.UnBind();
		sphere.Draw();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	//Delete memory for a model matrix array
	//delete[] modelMatrices;

	glfwTerminate();
	return 0;
}