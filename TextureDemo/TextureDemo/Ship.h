#pragma once
#include "GameObject.h"

class Ship : public GameObject {
public:
	Ship(glm::vec3 &entityPosition, GLuint entityTexture, GLint entityNumElements) : GameObject(entityPosition, entityTexture, entityNumElements) {};
};