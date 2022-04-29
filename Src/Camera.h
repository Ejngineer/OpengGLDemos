#ifndef __CMAERA_H__
#define	__CMAERA_H__

#include "GLFW/glfw3.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

class Camera
{
private:
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	float pitch = 0.0f;
	float yaw = -90.0f;
	float lastX = 600.0f;
	float lastY = 450.0f;
	bool FirstMouse = true;
public:
	Camera() = default;
	~Camera() = default;
	Camera(GLFWwindow* window);
	glm::vec3 GetCameraPos() { return cameraPos; };
	glm::vec3 GetCameraFront() { return cameraFront; }
	glm::vec3 GetCameraUp() { return cameraUp; }
	glm::mat4 GetViewMatrix() 
	{ 
		return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	};

	void ProcessInput(GLFWwindow* window, float deltaTime);
	void camera_mouse_callback(GLFWwindow* window, float xpos, float ypos);

};

#endif