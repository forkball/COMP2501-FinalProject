#include "Tower.h"

Tower::Tower(int type, bool playerControlled, glm::vec3 towerScale, glm::vec3 &entityPosition, GLuint entityTexture, GLuint projectileTexture, GLint entityNumElements)
	: GameObject(entityPosition, entityTexture, entityNumElements), type(type), playerControlled(playerControlled), projectileTexture(projectileTexture), size(entityNumElements)
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

	//projectile control
	for (int i = 0; i < projectiles.size(); i++)
	{
		Projectile* proj = projectiles.at(i);
		proj->update(deltaTime);
		double playerDist = sqrt(pow(getPosition().x - proj->getPosition().x, 2) + pow(getPosition().y - proj->getPosition().y, 2));
		if (playerDist > 2)
		{
			removeProjectile(i);
		}
		else
		{
			for (int j = 0; j < enemies.size(); j++)
			{
				Unit* enem = enemies.at(i);
				double dist = sqrt(pow(enem->getPosition().x - proj->getPosition().x, 2) + pow(enem->getPosition().y - proj->getPosition().y, 2));
				if (dist < 0.1)
				{
					enem->takeDamage(proj->getDamage());
					removeProjectile(i);
				}
			}
		}
	}
}

void Tower::render(Shader& shader)
{
	for (int i = 0; i < projectiles.size(); i++)
	{
		projectiles.at(i)->render(shader);
	}

	GameObject::render(shader);
}

void Tower::removeProjectile(int index)
{
	Projectile* proj = projectiles.at(index);
	proj = NULL;
	delete proj;
	projectiles.erase(projectiles.begin() + index);
}

void Tower::shoot(glm::vec3 target)
{
	double horDiff = target.x - position.x;
	double verDiff = target.y - (position.y + 0.2);
	double dist = sqrt((horDiff * horDiff) + (verDiff * verDiff));
	double unitVectorX = horDiff / dist;
	double unitVectorY = verDiff / dist;
	projectiles.push_back(new Projectile(position + glm::vec3(0,0.2,0), projectileTexture, size, glm::vec2(unitVectorX,unitVectorY), 2,25));
}
