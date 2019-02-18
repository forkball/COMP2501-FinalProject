#pragma once
#include <GL/glew.h>
#include <GL/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <ctime>

#include "Shader.h"
#include "Window.h"

class Camera
{
public:
	Camera(Shader &shader, Window &window, glm::vec2 windowSize);
	~Camera();
	void update(double deltaTime);
	//zooms the camera in and out
	inline void zoomCamera(float zoomAmount) { zoom += zoomAmount; }
	//returns the mouse position in relation to the window
	glm::vec2 getMousePosition();
private:
	//holds the view
	glm::mat4 viewMatrix;
	//positional coordinates
	glm::vec3 position;
	//holds the size of the window
	glm::vec2 windowSize;

	//panning speed of camera
	float panningSpeed = 2;
	float panningThreshold = 0.7;
	
	//controls how zoomed in the camera is
	float zoom;
	float zoomSpeed;

	Shader shader;
	Window window;
};

