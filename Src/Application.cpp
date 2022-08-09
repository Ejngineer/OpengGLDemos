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
#include "CubeSphere.h"
#include "quadSphere.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"


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

	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to intialize glad" << std::endl;
		return -1;
	}

	glViewport(0, 0, 1920, 1080);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);


	glfwWindowHint(GLFW_SAMPLES, 4);

	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	//const float vertices[] =
	//{
	//	//Position          //Normals        //TexCoords  //Tangents
	//	-1.0f,-1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f, 0.0f, 0.0f,
	//	 1.0f,-1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 2.0f, 0.0f, 0.0f,
	//	 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 2.0f, 0.0f, 0.0f,
	//	 
	//	 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 2.0f, 0.0f, 0.0f,
	//	-1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 2.0f, 0.0f, 0.0f,
	//	-1.0f,-1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f, 0.0f, 0.0f,
	//};



	glm::vec3 pos1(-1.0f, 1.0f, 0.0f);
	glm::vec3 pos2(-1.0f, -1.0f, 0.0f);
	glm::vec3 pos3(1.0f, -1.0f, 0.0f);
	glm::vec3 pos4(1.0f, 1.0f, 0.0f);
	// texture coordinates
	glm::vec2 uv1(0.0f, 1.0f);
	glm::vec2 uv2(0.0f, 0.0f);
	glm::vec2 uv3(1.0f, 0.0f);
	glm::vec2 uv4(1.0f, 1.0f);
	// normal vector
	glm::vec3 nm(0.0f, 0.0f, 1.0f);

	// calculate tangent/bitangent vectors of both triangles
	glm::vec3 tangent1, bitangent1;
	glm::vec3 tangent2, bitangent2;
	// triangle 1
	// ----------
	glm::vec3 edge1 = pos2 - pos1;
	glm::vec3 edge2 = pos3 - pos1;
	glm::vec2 deltaUV1 = uv2 - uv1;
	glm::vec2 deltaUV2 = uv3 - uv1;

	float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

	tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
	tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
	tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
	tangent1 = glm::normalize(tangent1);

	bitangent1.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
	bitangent1.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
	bitangent1.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
	bitangent1 = glm::normalize(bitangent1);

	// triangle 2
	// ----------
	edge1 = pos3 - pos1;
	edge2 = pos4 - pos1;
	deltaUV1 = uv3 - uv1;
	deltaUV2 = uv4 - uv1;

	f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

	tangent2.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
	tangent2.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
	tangent2.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
	tangent2 = glm::normalize(tangent2);


	bitangent2.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
	bitangent2.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
	bitangent2.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
	bitangent2 = glm::normalize(bitangent2);


	float quadVertices[] = {
		// positions            // normal         // texcoords  // tangent                          // bitangent
		pos1.x, pos1.y, pos1.z, nm.x, nm.y, nm.z, uv1.x, uv1.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
		pos2.x, pos2.y, pos2.z, nm.x, nm.y, nm.z, uv2.x, uv2.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
		pos3.x, pos3.y, pos3.z, nm.x, nm.y, nm.z, uv3.x, uv3.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,

		pos1.x, pos1.y, pos1.z, nm.x, nm.y, nm.z, uv1.x, uv1.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z,
		pos3.x, pos3.y, pos3.z, nm.x, nm.y, nm.z, uv3.x, uv3.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z,
		pos4.x, pos4.y, pos4.z, nm.x, nm.y, nm.z, uv4.x, uv4.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z

	};

	VertexArray VAO;
	VertexBuffer VBO(quadVertices, sizeof(quadVertices));

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(sizeof(float) * 6));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(sizeof(float) * 8));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(11 * sizeof(float)));
	glEnableVertexAttribArray(4);

	double lastframe = 0.0f;
	double currentframe;
	float deltaTime;

	Shader SphereShader("shaders/vertexshader.glsl", "shaders/fragmentshader.glsl");
	Shader SphereShader1("shaders/vertexshader1.glsl", "shaders/fragmentshader1.glsl");

	//Cubesphere Sphere(1.0f, 7, false);
	quadSphere Sphere(1.0f, 144, 144, false);

	Texture BrickWall, BrickWallNorm;
	BrickWall.Bind();
	BrickWall.Load("textures/brickwall.jpg");
	
	BrickWallNorm.Bind();
	BrickWallNorm.Load("textures/brickwall_normal.jpg");
	
	Texture RBrickWall, RBrickWallNorm, RBrickWallDisp;
	RBrickWall.Bind();
	RBrickWall.Load("textures/toybox.png");
	RBrickWallNorm.Bind();
	RBrickWallNorm.Load("textures/toyboxnormal.png");
	RBrickWallDisp.Bind();
	RBrickWallDisp.Load("textures/toyboxdisp.png");
	

	Texture ParallaxWall, ParallaxWallNorm, ParallaxWallDisp;
	ParallaxWall.Bind();
	ParallaxWall.Load("textures/bricks2.jpg");
	ParallaxWallNorm.Bind();
	ParallaxWallNorm.Load("textures/bricks2_normal.jpg");
	ParallaxWallDisp.Bind();
	ParallaxWallDisp.Load("textures/bricks2_disp.jpg");

	SphereShader.use();
	SphereShader.setInt1i("walltext", 0);
	SphereShader.setInt1i("walltextnorm", 1);
	SphereShader.setInt1i("walltextdepth", 2);

	float heightscale = 0.0f;

	float Height1 = 0.0f;
	float Height2 = 0.0f;
	float Height3 = 0.0f;
	int Divisions1 = 1;
	int Divisions2 = 1;
	int Divisions3 = 1;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		glfwGetCursorPos(window, &cursPos.xpos, &cursPos.ypos);
		currentframe = glfwGetTime();
		deltaTime = float(currentframe) - float(lastframe); 
		lastframe = currentframe;

		camera.ProcessInput(window, deltaTime);
		//camera.camera_mouse_callback(window, cursPos.xpos, cursPos.ypos);

		/*check to see if escape key had been pressed*/
		ProcessInput(window);
		
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		ImGui::Begin("Options");
		//ImGui::SliderFloat("Height 1", &Height1, 0.0f, 1.0f, "%.5f");
		ImGui::SliderFloat("Height 2", &Height2, 0.0f, 1.0f, "%.5f");
		ImGui::SliderFloat("Height 3", &Height3, 0.0f, 1.0f, "%.5f");
		ImGui::SliderInt("Divisions 1", &Divisions1, 1.0f, 5.0f);
		ImGui::SliderInt("Divisions 2", &Divisions2, 1.0f, 5.0f);
		ImGui::SliderInt("Divisions 3", &Divisions3, 1.0f, 5.0f);

		stbi_set_flip_vertically_on_load(0);

		glm::mat4 model(1.0f);
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);

		/*Use shader program*/
		SphereShader.use();
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, glm::radians((float)glfwGetTime() * 10.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		SphereShader.setMat4f("model", model);
		SphereShader.setMat4f("view", view);
		SphereShader.setMat4f("projection", projection);
		SphereShader.setFloat3fv("viewPos", camera.GetCameraPos());
		SphereShader.setFloat3fv("lightPos", glm::vec3(3.0f, 1.0f, 3.0f));
		SphereShader.setInt1i("Divisions", Divisions1);
		SphereShader.setFloat1f("height_scale", Height1);

		/*Activate our textures*/
		BrickWall.ActivateTexture2D(0);
		BrickWall.Bind();
		BrickWallNorm.ActivateTexture2D(1);
		BrickWallNorm.Bind();
		Sphere.Draw();
		
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(3.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		
		SphereShader.setMat4f("model", model);
		SphereShader.setInt1i("Divisions", Divisions2);
		SphereShader.setFloat1f("height_scale", Height2);
		ParallaxWall.ActivateTexture2D(0);
		ParallaxWall.Bind();
		ParallaxWallNorm.ActivateTexture2D(1);
		ParallaxWallNorm.Bind();
		ParallaxWallDisp.ActivateTexture2D(2);
		ParallaxWallDisp.Bind();
		Sphere.Draw();
		
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(6.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		SphereShader.setMat4f("model", model);
		SphereShader.setInt1i("Divisions", Divisions3);
		SphereShader.setFloat1f("height_scale", Height3);
		RBrickWall.ActivateTexture2D(0);
		RBrickWall.Bind();
		RBrickWallNorm.ActivateTexture2D(1);
		RBrickWallNorm.Bind();
		RBrickWallDisp.ActivateTexture2D(2);
		RBrickWallDisp.Bind();

		//VAO.Bind();
		//glDrawArrays(GL_TRIANGLES,0, 6);
		//VAO.UnBind();
		Sphere.Draw();

		ImGui::End();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		
	}

	//Delete memory for a model matrix array
	//delete[] modelMatrices;

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}






