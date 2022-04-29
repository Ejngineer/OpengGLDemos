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

void Camera::camera_mouse_callback(GLFWwindow* window, float xpos, float ypos)
{
	if (FirstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		FirstMouse = false;
	}
	
	float offsetX = xpos - lastX;
	float offsetY = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.1f;
	offsetX *= sensitivity;
	offsetY *= sensitivity;

	yaw += offsetX;
	pitch += offsetY;

	glm::vec3 direction(0.0f);
	direction.x = cosf(glm::radians(yaw)) * cosf(glm::radians(pitch));
	direction.y = sinf(glm::radians(pitch));
	direction.z = sinf(glm::radians(yaw)) * cosf(glm::radians(pitch));
	cameraFront = glm::normalize(direction);

	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}
	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}
}
