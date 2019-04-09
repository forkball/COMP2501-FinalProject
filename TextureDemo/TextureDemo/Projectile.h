#pragma once
#include "GameObject.h"

class Projectile : public GameObject {
public:
	Projectile(int type, glm::vec3 &entityPos, GLuint texture, GLint entityNumElements, glm::vec2 dir, float speed, double damage);
	void update(double deltaTime);
	inline double getDamage() { return damage; }

private:
	int type;
	double damage;
	float speed;
	glm::vec2 direction = glm::vec2(0.0f);
};