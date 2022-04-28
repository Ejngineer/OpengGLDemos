#include "Camera.h"

void Camera::ProcessInput(GLFWwindow* window, float deltaTime)
{
	float speed = 2.5f * deltaTime;

	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		cameraPos += speed * cameraFront;
	}
	if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		cameraPos -= glm::normalize(cross(cameraFront, cameraUp)) * speed;
	}
	if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		cameraPos -= speed * cameraFront;
	}
	if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		cameraPos += glm::normalize(cross(cameraFront, cameraUp)) * speed;
	}
}
