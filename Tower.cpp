#include "Tower.h"
#include "ParticleSystem.h"

//extern ParticleSystem particleSystem;

Tower::Tower(int type, bool playerControlled, glm::vec3 towerScale, glm::vec3 &entityPosition, GLuint entityTexture, GLuint projectileTexture, GLint entityNumElements)
	: GameObject(entityPosition, entityTexture, entityNumElements), type(type), playerControlled(playerControlled), projectileTexture(projectileTexture), size(entityNumElements)
{
	scale = towerScale;
}

Tower::~Tower()
{
	for (int i = 0; i < projectiles.size(); i++)
	{
		removeProjectile(i);
	}
}

//update tower logic
void Tower::update(double deltaTime, vector<Unit*> enemies)
{
	#pragma region Tower Behaviors
	switch (type)
	{
	case 0:
		for (int i = 0; i < enemies.size(); i++) {
			if (glm::abs(enemies.at(i)->getPosition().x - position.x) <= shootingRange) {
				if ((glfwGetTime() - projectileTimer) > projectileDelay) {
					shoot(enemies.at(i)->getPosition(), 50);
					projectileTimer = glfwGetTime();
				}
			}
		}
		break;
	case 1:
		for (int i = 0; i < enemies.size(); i++) {
			if (glm::abs(enemies.at(i)->getPosition().x - position.x) <= shootingRange) {
				//particleSystem.drawParticles(position, projectileTexture, 1000);

				//particleSystem.drawParticles(glm::vec3(-2.0, 0.0, 0.0), tex[18], 1000);



			}
		}
		break;
	case 2:
		for (int i = 0; i < enemies.size(); i++) {
			if (glm::abs(enemies.at(i)->getPosition().x - position.x) <= shootingRange) {
				if ((glfwGetTime() - projectileTimer) > projectileDelay) {
					shoot(enemies.at(i)->getPosition(), 25);
					projectileTimer = glfwGetTime();
				}
			}
		}
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
				if (dist < 0.1)
				{
					enem->takeDamage(proj->getDamage());
					switch (type) {
						case 2:
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
void Tower::render(Shader& shader)
{
	for (int i = 0; i < projectiles.size(); i++)
	{
		projectiles.at(i)->render(shader);
	}

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
	double horDiff = target.x - position.x;
	double verDiff = target.y - (position.y + 0.2);
	double dist = sqrt((horDiff * horDiff) + (verDiff * verDiff));
	double unitVectorX = horDiff / dist;
	double unitVectorY = verDiff / dist;
	projectiles.push_back(new Projectile(type, position + glm::vec3(0,0.2,0), projectileTexture, size, glm::vec2(unitVectorX,unitVectorY), 2, damage));
}