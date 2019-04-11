#include "GameObject.h"

/*
	GameObject is responsible for handling the rendering and updating of objects in the game world
	The update method is virtual, so you can inherit from GameObject and override the update functionality (see PlayerGameObject for reference)
*/
static int id = 0;

GameObject::GameObject(glm::vec3 &entityPosition, GLuint entityTexture, GLint entityNumElements)
{
	orientation = 0.0f;
	position = entityPosition;
	texture = entityTexture;
	numElements = entityNumElements;
	pid = id++;

}

// Updates the GameObject's state. Can be overriden for children
void GameObject::update(double deltaTime) {
}

// Renders the GameObject using a shader
void GameObject::render(Shader &shader) {
	//resets orientation
	if (orientation > 360) orientation = 0;
	if (orientation < 0) orientation = 360;
	// Bind the entities texture
	glBindTexture(GL_TEXTURE_2D, texture);

	// Setup the transformation matrix for the shader
	// TODO: Add different types of transformations
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), orientation, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);

	// Set the transformation matrix in the shader
	glm::mat4 transformationMatrix = translationMatrix * rotationMatrix * scaleMatrix;
	shader.setUniformMat4("transformationMatrix", transformationMatrix);

	// Draw the entity
	glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, 0);
}

// Renders the GameObject using a shader, also takes in scale
void GameObject::renderbig(Shader &shader, Camera *camera) {
	//resets orientation
	if (orientation > 360) orientation = 0;
	if (orientation < 0) orientation = 360;
	// Bind the entities texture
	glBindTexture(GL_TEXTURE_2D, texture);

	// Setup the transformation matrix for the shader
	// TODO: Add different types of transformations
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), orientation, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(50.0f), glm::vec3(3,3,3));

	// Set the transformation matrix in the shader
	glm::mat4 transformationMatrix = translationMatrix * rotationMatrix * scaleMatrix * camera->getViewMatrix();
	shader.setUniformMat4("transformationMatrix", transformationMatrix);

	// Draw the entity
	glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, 0);
}