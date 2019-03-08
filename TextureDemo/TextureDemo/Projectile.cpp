#include "Projectile.h"

Projectile::Projectile(glm::vec3 &entityPos, GLuint texture, GLint entityNumElements, float orientation, float speed)
	: GameObject(entityPos, texture, entityNumElements), speed(speed), orientation(orientation)
{
	scale = glm::vec3(1.0f);
}

void Projectile::update(double deltaTime) {
	// Update object position
	//direction.x = (float)glm::cos(orientation * (glm::pi<float>() / 180));
	//direction.y = (float)glm::sin(orientation * (glm::pi<float>() / 180));
	//direction = glm::normalize(direction);
	//position.x += (direction.x * speed) ;
	//position.y += (direction.y * speed);
}