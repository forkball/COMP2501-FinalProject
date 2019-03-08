#include "Tower.h"

Tower::Tower(int type, bool playerControlled, glm::vec3 towerScale, glm::vec3 &entityPosition, GLuint entityTexture, GLuint projectileTexture, GLint entityNumElements)
	: GameObject(entityPosition, entityTexture, entityNumElements), type(type), playerControlled(playerControlled), projectileTexture(projectileTexture)
{
	scale = towerScale;
}

Tower::~Tower()
{
}

void Tower::update(double deltaTime, vector<Unit*> enemies)
{
	//handles behavior of each tower type
	switch (type)
	{
	case 0:
		for (int i = 0; i < enemies.size(); i++) {
			if (glm::abs(enemies.at(i)->getPosition().x - position.x) <= shootingRange) {
				if ((glfwGetTime() - projectileTimer) > projectileDelay) {
					shoot(enemies.at(i)->getPosition());
					projectileTimer = glfwGetTime();
				}
			}
		}
		break;
	case 1:
		break;
	}

	for (int i = 0; i < projectiles.size(); i++)
	{
		projectiles.at(i)->update(deltaTime);
	}
}

void Tower::shoot(glm::vec3 target)
{
	float dot = position.x * target.x + position.y * target.y;
	float det = position.x * target.y - position.y * target.x;
	projectiles.push_back(new Projectile(glm::vec3(0, 0, 0), projectileTexture, size, 0, 0));
}
