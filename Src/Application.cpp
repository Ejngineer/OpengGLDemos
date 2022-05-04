#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Camera.h"
#include "Cube.h"
#include "Sphere.h"
#include "gtx/string_cast.hpp"


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

	float quadVertices[] =
	{
		//vertices          //Normals
		-0.5f, 0.0f,-0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f, 0.0f,-0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f, 0.0f, 0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.0f, 0.5f, 0.0f, 1.0f, 0.0f
	};

	unsigned int quadIndices[] =
	{
		0,1,2,
		2,3,0
	};

	VertexArray VAO;
	VertexBuffer VBO(quadVertices, sizeof(quadVertices));
	IndexBuffer IBO(quadIndices, sizeof(quadIndices));

	VAO.Bind();

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	/* Geometries*/
	//Cube cube;
	Sphere sphere(1.0f, 72, 36, true);
	
	Shader TriShader("shaders/vertexshader.glsl", "shaders/fragmentshader.glsl");

	double lastframe = 0.0f;
	double currentframe;
	float deltaTime;

	/*Instancing code*/
	const unsigned int amount = 16384;
	glm::mat4 *modelMatrices;
	modelMatrices = new glm::mat4[amount];
	//modelMatrices = new glm::mat4[amount];
	srand(glfwGetTime());

	int index = 0;
	int offset = 0.1f;

	for (int z = -256; z < 256; z+=4)
	{
		for (int x = -256; x < 256; x+=4)
		{
			glm::mat4 model = glm::mat4(1.0f);
			float y = (rand() % 128);
			float dx = (rand() % 128) - 64.0f;
			float dz = (rand() % 128) - 64.0f;
			model = glm::translate(model, glm::vec3(x, 0.0f, z));
			//model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			modelMatrices[index] = model;
			index++;
		}
	}

	/*Instance Array VertexBuffer data*/
	VertexBuffer InstVBO;
	InstVBO.setDataStaticf(&modelMatrices[0], amount * sizeof(glm::mat4));

	/*Add model matrix data to sphere Vertex array object pointers*/
	unsigned int InstVAO = sphere.GetVAO();
	glBindVertexArray(InstVAO);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (void*)0);
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (void*)(1 * sizeof(glm::vec4)));
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (void*)(2 * sizeof(glm::vec4)));
	glEnableVertexAttribArray(6);
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (void*)(3 * sizeof(glm::vec4)));

	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);
	glVertexAttribDivisor(6, 1);

	InstVBO.UnBind();

	/*Random colors and specular highlight values for instanced objects*/
	srand(glfwGetTime());
	float Colors[4 * amount];
	for (unsigned int i = 0; i < 4 * amount; i+=4)
	{
		float r = ((rand() % 225) + 30) / 255.0f;
		float g = ((rand() % 225) + 30) / 255.0f;
		float b = ((rand() % 225) + 30) / 255.0f;
		float pow = (rand() % 9);

		Colors[i] = r;
		Colors[i + 1] = g;
		Colors[i + 2] = b;
		Colors[i + 3] = pow;
	}

	VertexBuffer ColorBuffer;
	ColorBuffer.setDataStaticf(Colors, sizeof(Colors));

	glEnableVertexAttribArray(7);
	glVertexAttribPointer(7, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(8);
	glVertexAttribPointer(8, 1, GL_FLOAT, GL_FALSE, 4 * sizeof(int), (void*)(3 * sizeof(float)));

	glVertexAttribDivisor(7, 1);
	glVertexAttribDivisor(8, 1);

	ColorBuffer.UnBind();

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
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 10000.0f);

		TriShader.use();
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(500.0f, 1.0f, 500.0f));
		TriShader.setInt1i("Instance", false);
		TriShader.setMat4f("model", model);
		TriShader.setMat4f("view", view);
		TriShader.setMat4f("projection", projection);
		TriShader.setFloat3fv("viewPos", camera.GetCameraPos());
		TriShader.setFloat3fv("lightPosition", glm::vec3(1.0f, 100.0f, 1.0f));
		//TriShader.setFloat3fv("inColor", glm::vec3(1.0f, 1.0f, 1.0f));

		//VAO.Bind();
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//VAO.UnBind();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		

		//TriShader.setMat4f("model", model);
		//TriShader.setFloat3fv("inColor", glm::vec3(0.0f, 1.0f, 0.0f));
		TriShader.setInt1i("Instance", true);

		//cube.Draw();
		//sphere.Draw();
		sphere.DrawInstanced(amount);

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