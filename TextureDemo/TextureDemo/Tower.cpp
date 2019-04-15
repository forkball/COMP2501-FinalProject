#include "Tower.h"
#include "Castle.h"

Tower::Tower(GameObject* parent, int type, bool playerControlled, glm::vec3 towerScale, glm::vec3 &entityPosition, GLuint entityTexture, GLuint projectileTexture, GLint entityNumElements)
	: GameObject(entityPosition, entityTexture, entityNumElements), parent(parent), type(type), playerControlled(playerControlled), projectileTexture(projectileTexture), size(entityNumElements)
{
	scale = towerScale;
	health = 100;
}

Tower::~Tower()
{
	for (int i = 0; i < projectiles.size(); i++)
	{
		removeProjectile(i);
	}
}

//update tower logic
void Tower::update(double deltaTime, std::vector<Unit*> enemies)
{
	#pragma region Tower Behaviors
	switch (type)
	{
	case 0:
		for (int i = 0; i < enemies.size(); i++) {
			if (glm::abs(enemies.at(i)->getPosition().x - position.x) <= shootingRange) {
				if ((glfwGetTime() - projectileTimer) > projectileDelay) {
					shoot(enemies.at(i)->getPosition(), 25);
					projectileTimer = glfwGetTime();
				}
			}
		}
		break;
	case 1:
		for (int i = 0; i < enemies.size(); i++) {
			if (glm::abs(enemies.at(i)->getPosition().x - position.x) <= shootingRange) {
				if ((glfwGetTime() - projectileTimer) > projectileDelay) {
					shoot(enemies.at(i)->getPosition(), 50);
					projectileTimer = glfwGetTime();
				}
			}
		}
		break;
	case 2:
		for (int i = 0; i < enemies.size(); i++) {
			flame = (glm::abs(enemies.at(i)->getPosition().x - position.x) <= shootingRange);
			if (flame) {
				targetPosition = enemies.at(i)->getPosition();
				enemies.at(i)->takeDamage(0.1);
				break;
			}
		}
		break;
	case 3:

		break;
	}
	#pragma endregion
	
	#pragma region Projectile Collisions
	for (int i = 0; i < projectiles.size(); i++)
	{
		bool hit = false;
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
				if (dist <= 0.2)
				{
					//to-do different prices per unit
					if (enem->getHealth() - proj->getDamage() <= 0) {
						double totalFunds = 0;
						switch (enem->getType()) {
						case 0:
							totalFunds = 20;
							break;
						case 1:
							totalFunds = 10;
							break;
						case 2:
							totalFunds = 50;
							break;
						case 3: 
							totalFunds = 30;
							break;
						}
						((Castle*)parent)->addFunds(totalFunds);
					}
					enem->takeDamage(proj->getDamage());
					switch (type) {
						case 0:
							enemies.at(i)->freeze();
							break;
					}
					removeProjectile(i);
					break;
				}
			}
		}
	}
	#pragma endregion
}

//renders tower and projectiles
void Tower::render(Shader& shader, ParticleSystem &ps)
{
	for (int i = 0; i < projectiles.size(); i++)
	{
		projectiles.at(i)->render(shader);
	}

	if (flame) {
		glm::vec3 direction = glm::normalize(targetPosition - getPosition());
		float orientation = (atan2(direction.y, direction.x)) * (180 / glm::pi<float>());
		
		ps.enable();
		ps.setAttributes();
		ps.drawParticles(position, 6, orientation - 80, projectileTexture, 250);
	}

	shader.enable();
	shader.setAttributes();

	GameObject::render(shader);
}

//removes projectile from vector

void Tower::removeProjectile(int index)
{
	Projectile* proj = projectiles.at(index);
	proj = NULL;
	delete proj;
	projectiles.erase(projectiles.begin() + index);
}

//shoots projectiles at target
void Tower::shoot(glm::vec3 target,int damage)
{
	double horDiff = (target.x - position.x); 
	double verDiff = target.y - (position.y + 0.2);
	double dist = sqrt((horDiff * horDiff) + (verDiff * verDiff));
	double unitVectorX = horDiff / dist;
	double unitVectorY = verDiff / dist;
	projectiles.push_back(new Projectile(type, position + glm::vec3(0,0.2,0), projectileTexture, size, glm::vec2(unitVectorX,unitVectorY), 2, damage));
}


