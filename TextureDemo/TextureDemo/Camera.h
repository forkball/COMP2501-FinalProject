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
	//gets the position of the camera
	inline glm::vec3 getPosition() { return position; }
	//zoom of camera
	inline float getZoom() { return zoom; }
	//zooms the camera in and out
	inline void zoomCamera(float zoomAmount) { zoom += zoomAmount; }
	//returns the mouse position in relation to the window
	static glm::vec2 getMousePosition();
	//returns view matrix
	inline glm::mat4 getViewMatrix() { return viewMatrix; }
private:
	//holds the view
	glm::mat4 viewMatrix;
	//positional coordinates
	glm::vec3 position;
	//holds the size of the window
	glm::vec2 windowSize;

	//panning speed of camera
	double panningSpeed = 3;
	double panningThreshold = 0.7;
	
	//controls how zoomed in the camera is
	float zoom = 0.5f;
	float zoomSpeed = 0.001f;

	Shader shader;
	Window window;
};

