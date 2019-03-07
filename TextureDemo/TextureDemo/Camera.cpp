#include "Camera.h"

Camera::Camera(Shader &shader, Window &window, glm::vec2 windowSize) 
	: shader(shader), window(window), windowSize(windowSize)
{
	position = glm::vec3(0.0f);
}

Camera::~Camera()
{
}

glm::vec2 Camera::getMousePosition()
{
	//holds the mouse positions
	double xpos, ypos;
	//gets the mouse positions
	glfwGetCursorPos(window.getWindow(), &xpos, &ypos);
	//returns a vector with the mouse positions in relation to the window size
	return glm::vec2((-xpos / (windowSize.x / 2) + 1), (ypos / (windowSize.y / 2) - 1));
}

void Camera::update(double deltaTime) 
{
	//positional updates
	glm::vec2 mousePosition(getMousePosition());
	if ((glm::abs(glm::length(mousePosition)) > panningThreshold) && ((position.x >= -6) && (position.x <= 6)))
	{
		position.x += (mousePosition.x * panningSpeed) * deltaTime;
	}
	else {
		if (position.x <= -6) position.x += panningSpeed * deltaTime;
		if (position.x >= 6) position.x -= panningSpeed * deltaTime;
	}
	glm::vec3 cameraTranslatePos(glm::vec3(position.x, position.y, 0.0f));
	//scaling updates
	zoom = glm::clamp(zoom, 0.2f, 0.6f);
	//apply transformations
	glm::mat4 viewMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(zoom)) * glm::translate(glm::mat4(1.0f), cameraTranslatePos);
	shader.setUniformMat4("viewMatrix", viewMatrix);

	//zooms camera in and out
	if (glfwGetKey(Window::getWindow(), GLFW_KEY_Z) == GLFW_PRESS) zoomCamera(-zoomSpeed);
	else if (glfwGetKey(Window::getWindow(), GLFW_KEY_X) == GLFW_PRESS) zoomCamera(zoomSpeed);
}
