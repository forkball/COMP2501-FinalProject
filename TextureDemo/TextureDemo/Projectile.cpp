#include "Projectile.h"

Projectile::Projectile(int type, glm::vec3 &entityPos, GLuint texture, GLint entityNumElements, glm::vec2 dir, float speed, double damage)
	: GameObject(entityPos, texture, entityNumElements), speed(speed), direction(dir), damage(damage)
{
	scale = glm::vec3(0.2f);
}

void Projectile::update(double deltaTime) {
	// Update object position
	position.x += (double) (direction.x * speed) * deltaTime;
	position.y += (double) (direction.y * speed) * deltaTime;
}