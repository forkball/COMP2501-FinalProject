#include "Unit.h"
#include "Castle.h"

Unit::Unit(GameObject* parent,
	int type,
	double health,
	bool playerControlled,
	double movementSpeed,
	Graph* graph,
	glm::vec3 unitScale,
	glm::vec2 target,
	glm::vec3 &entityPosition,
	GLuint entityTexture,
	GLint entityNumElements)
	: GameObject(entityPosition, entityTexture, entityNumElements), parent(parent), type(type), target(target), playerControlled(playerControlled), orgSpeed(movementSpeed), graph(graph)
{
	scale = unitScale;
	this->health = health;
	health = 100;
	path = graph->pathfind(glm::vec2(position.x, position.y), target);

	switch (type) {
	//knight
	case 0: 
		enemyDist = 0.2;
		attackDelay = 1;
		orgDamage = 20;
		damage = orgDamage;
		break;
	//archer
	case 1: 
		enemyDist = 0.6;
		attackDelay = 2;
		orgDamage = 10;
		damage = orgDamage;
		break;
	//catapult
	case 2: 
		enemyDist = 0.8;
		attackDelay = 3;
		orgDamage = 50;
		damage = orgDamage;
		break;
	//cavalry
	case 3: 
		enemyDist = 0.25;
		attackDelay = 2;
		orgDamage = 25;
		damage = orgDamage;
		break;
	}
}

Unit::~Unit()
{
}

//renders unit and potential particles
extern GLuint tex[];

void Unit::update(double deltaTime, GameObject* enemyCastle)
{
		// buffs minions
	if (powerup) {
		damage = orgDamage * 1.5;
		if ((glfwGetTime() - powerupTimer) > powerupDuration)
			powerup = false;
	}
	else { damage = orgDamage; powerupTimer = glfwGetTime(); }

	//handles freeze status
	if (freezeSlow) {
		if (((glfwGetTime() - freezeTimer) / 1000) > freezeDelay)
			freezeSlow = false;
		movementSpeed = orgSpeed / 2;
	}
	else movementSpeed = orgSpeed;

	//movement control
	if (!enemyNear) {
		if ((path.size() > 0) && (playerControlled == 1)) {
			if (position.x >= path.at(0).x && position.y >= path.at(0).y)
				path.erase(path.begin());
			else if (position.x < path.at(0).x)
				position.x += movementSpeed * deltaTime;
			else if (position.y < path.at(0).y)
				position.y += movementSpeed * deltaTime;
		}
		else if ((path.size() > 0) && (playerControlled == 0)) {
			if (position.x <= path.at(0).x && position.y >= path.at(0).y)
				path.erase(path.begin());
			else if (position.x > path.at(0).x)
				position.x -= movementSpeed * deltaTime;
			else if (position.y < path.at(0).y)
				position.y += movementSpeed * deltaTime;
		}
	}

	//checks if there is an enemy near the unit
	for (int j = 0; j < ((Castle*)enemyCastle)->getUnits().size(); j++)
	{
		Unit* enem = ((Castle*)enemyCastle)->getUnits().at(j);
		double dist = sqrt(pow(enem->getPosition().x - position.x, 2) + pow(enem->getPosition().y - position.y, 2));
		if (dist <= enemyDist)
		{
			enemyNear = true;
			enemy = enem;
			break;
		}
		enemyNear = false;
		enemy = NULL;
	}

	//handles behavior of each unit type
	if (enemyNear) {
		if ((glfwGetTime() - attackTimer) > attackDelay) {
			attackTimer = glfwGetTime();
			switch (type)
			{
			//knight
			case 0:
				if (enemy->getHealth() - damage <= 0) {
					enemyNear = false;
				}
				enemy->takeDamage(damage);
				break;
			//archer
			case 1:
				shoot(enemy->getPosition(), tex[17], damage);
				break;
			//catapult
			case 2:
				shoot(enemy->getPosition(), tex[17], damage);
				break;
			//cavalry
			case 3:
				if (enemy->getHealth() - damage <= 0) {
					enemyNear = false;
				}
				enemy->takeDamage(damage);
				break;
			}
		}
	}

	#pragma region Projectile Collisions
	for (int i = 0; i < projectiles.size(); i++)
	{
		Projectile* proj = projectiles.at(i);
		proj->update(deltaTime);
		double unitDist = sqrt(pow(getPosition().x - proj->getPosition().x, 2) + pow(getPosition().y - proj->getPosition().y, 2));
		if (unitDist > 2)
		{
			removeProjectile(i);
		}
		else
		{
			double dist = sqrt(pow(enemy->getPosition().x - proj->getPosition().x, 2) + pow(enemy->getPosition().y - proj->getPosition().y, 2));
			if (dist < 0.2)
			{
				if (enemy->getHealth() - proj->getDamage() <= 0) {
					double totalFunds = 0;
					if (enemy != enemyCastle) {
						switch (((Unit*)enemy)->getType()) {
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
					}
					((Castle*)parent)->addFunds(totalFunds);
				}	
				enemy->takeDamage(proj->getDamage());
				removeProjectile(i);
				break;
			}
			
		}
	}
	#pragma endregion
}

void Unit::render(Shader& shader, ParticleSystem &ps)
{
	if (freezeSlow) {
		ps.enable();
		ps.setAttributes();
		ps.drawParticles(position, 1.0f, 0, tex[20], 5.0f);
	}

	shader.enable();
	shader.setAttributes(); 
	
	for (int i = 0; i < projectiles.size(); i++)
	{
		projectiles.at(i)->render(shader);
	}

	GameObject::render(shader);
}

//removes projectile from vector
void Unit::removeProjectile(int index)
{
	Projectile* proj = projectiles.at(index);
	proj = NULL;
	delete proj;
	projectiles.erase(projectiles.begin() + index);
}

//shoots projectiles at target
void Unit::shoot(glm::vec3 target, GLuint projectileTexture, int damage)
{
	double horDiff = (target.x - position.x);
	double verDiff = target.y - (position.y + 0.2);
	double dist = sqrt((horDiff * horDiff) + (verDiff * verDiff));
	double unitVectorX = horDiff / dist;
	double unitVectorY = verDiff / dist;
	projectiles.push_back(new Projectile(type, position + glm::vec3(0, 0.2, 0), projectileTexture, size, glm::vec2(unitVectorX, unitVectorY), 2, damage));
}
