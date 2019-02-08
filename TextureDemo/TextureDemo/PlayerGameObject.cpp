#include "PlayerGameObject.h"

#include "Window.h"

/*
	PlayerGameObject inherits from GameObject
	It overrides GameObject's update method, so that you can check for input to change the velocity of the player
*/

PlayerGameObject::PlayerGameObject(glm::vec3 &entityPos, GLuint entityTexture,GLint entityNumElements)
	: GameObject(entityPos, entityTexture, entityNumElements)
{
	orientation = 0.0f;
	scale = glm::vec3(0.5f);
}

// Update function for moving the player object around
void PlayerGameObject::update(double deltaTime) {
	speed = glm::clamp(speed, -5.0f, 5.0f);

	// Checking for player input and changing velocity
	if (glfwGetKey(Window::getWindow(), GLFW_KEY_UP) == GLFW_PRESS) {
		speed += speedIncrement;
	}
	if (glfwGetKey(Window::getWindow(), GLFW_KEY_DOWN) == GLFW_PRESS) {
		speed -= speedIncrement;
	}
	if (glfwGetKey(Window::getWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS) {
		orientation -= rotationSpeed;
	}
	if (glfwGetKey(Window::getWindow(), GLFW_KEY_LEFT) == GLFW_PRESS) {
		orientation += rotationSpeed;
	}

	GameObject::update(deltaTime);
}

