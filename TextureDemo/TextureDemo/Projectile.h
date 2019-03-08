#pragma once
#include "GameObject.h"

class Projectile : public GameObject {
public:
	Projectile(glm::vec3 &entityPos, GLuint texture, GLint entityNumElements, float direction, float speed);
	void update(double deltaTime);
private:
	float speed, orientation;
	glm::vec2 direction = glm::vec2(0.0f);
};