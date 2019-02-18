#pragma once

#include <GL/glew.h>
#include <GL/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <ctime>

#include "Shader.h"

class GameObject {
public:
	GameObject(glm::vec3 &entityPosition, GLuint entityTexture, GLint entityNumElements);

	// Updates the GameObject's state. Can be overriden for children
	virtual void update(double deltaTime);

	// Renders the GameObject using a shader
	void render(Shader &shader);

	// Getters
	inline glm::vec3& getPosition() { return position; }
	inline float getOrientation() { return orientation; }

	// Setters
	inline void setPosition(glm::vec3& newPosition) { position = newPosition; }
protected:
	// Object's Transform Variables
	glm::vec3 position;
	glm::vec3 scale;
	//holds direction
	glm::vec2 direction = glm::vec2(0.0f);
	float orientation;

	// Object's details
	GLint numElements;
	float objectSize; // Not currently being used (will be needed for collision detection when objects have a different scale)

	// Object's texture
	GLuint texture;
};