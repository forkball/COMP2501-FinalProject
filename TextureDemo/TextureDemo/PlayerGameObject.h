#pragma once

#include "GameObject.h"

// Inherits from GameObject
class PlayerGameObject : public GameObject {
public:
	PlayerGameObject(glm::vec3 &entityPos, GLuint entityTexture, GLint entityNumElements);
	// Update function for moving the player object around
	virtual void update(double deltaTime) override;

protected:
	//speed of the players' rotate
	float rotationSpeed = 0.1f;
	//speed increment - how fast speed increases/decreases
	float speedIncrement = 0.01f;
};
