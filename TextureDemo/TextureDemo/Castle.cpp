#include "Castle.h"
#include <time.h>
#include <chrono>
typedef std::chrono::high_resolution_clock Clock;

//constructor
Castle::Castle(bool playerControlled,
			   glm::vec3 &entityPosition, 
	           glm::vec3 spriteScale, 
			   GLuint entityTexture, 
			   GLint entityNumElements,
			   std::vector<GLuint> projectileTextures, 
			   std::vector<GLuint> unitTextures, 
			   std::vector<GLuint> towerTextures) 
	: GameObject(entityPosition, entityTexture, entityNumElements), 
	  playerControlled(playerControlled), 
	  projectileTextures(projectileTextures), 
	  unitTextures(unitTextures), 
	  numElem(entityNumElements), 
	  towerTextures(towerTextures)
{
	scale = spriteScale;
	health = 100;
}

//destructor
Castle::~Castle()
{
	//frees memory used for towers and units
	for (int i = 0; i < towers.size(); i++)
		delete towers[i];
	for (int i = 0; i < units.size(); i++)
		delete units[i];

	towers.clear();
	units.clear();
}

static auto t1 = Clock::now();
static auto t2 = Clock::now();
//update function
void Castle::update(double deltaTime, glm::vec2 mousePosition, Castle* otherCastles)
{
	//player controls
	if (playerControlled)
	{
		#pragma region Mouse Control
		// kone is for left tower, ktwo is for right tower
		static int kone = 3;
		static int ktwo = 3;
		static int k;
		static int lastchanged;
		//current time
		t2 = Clock::now();
		
		static int oldMouseState = GLFW_RELEASE;
		int newMouseState = glfwGetMouseButton(Window::getWindow(), GLFW_MOUSE_BUTTON_RIGHT);
		static int oldMouseStateleft = GLFW_RELEASE;
		int newMouseStateleft = glfwGetMouseButton(Window::getWindow(), GLFW_MOUSE_BUTTON_LEFT);

		
			for (int i = 0; i < towers.size(); i++) {
				if ((towers[i]->getPosition().x - mousePosition.x) < 0.2 && (towers[i]->getPosition().x - mousePosition.x) > -0.2 && (towers[i]->getPosition().y + mousePosition.y) < 0.4 && (towers[i]->getPosition().y + mousePosition.y) > -0.4) {

					//time of click
					t1 = Clock::now();
					if (newMouseState == GLFW_RELEASE && oldMouseState == GLFW_PRESS) {
					
						if (towers[i]->getPosition().x == -4.0) {

						k = kone;
					}
					else if (towers[i]->getPosition().x == -2.5)  { k = ktwo; }

					if (towers[i]->getType() == 3) {

						
						
						lastchanged = i;

						switch (k) {

						case 0:
							k++;
							towers[i] = new Tower(this, 3, playerControlled, glm::vec3(-0.4, 0.7, 1), towers[i]->getPosition(), this->getTowerTextures().at(k+4), this->getProjectileTextures().at(0), this->getNumElem());

							break;
						case 1:
							k++;
							towers[i] = new Tower(this, 3, playerControlled, glm::vec3(-0.4, 0.7, 1), towers[i]->getPosition(), this->getTowerTextures().at(k+4), this->getProjectileTextures().at(1), this->getNumElem());

							break;
						case 2:
							k++;
							towers[i] = new Tower(this, 3, playerControlled, glm::vec3(-0.4, 0.7, 1), towers[i]->getPosition(), this->getTowerTextures().at(k), this->getProjectileTextures().at(2), this->getNumElem());

							break;
						case 3:
							k = 0;
							towers[i] = new Tower(this, 3, playerControlled, glm::vec3(-0.4, 0.7, 1), towers[i]->getPosition(), this->getTowerTextures().at(k+4), this->getProjectileTextures().at(3), this->getNumElem());

							break;
						}

				
					}


					if (towers[i]->getPosition().x == -4.0) {
						kone = k;
						}
					else if (towers[i]->getPosition().x == -2.5) { ktwo = k; }
				}
			}
		}
	

		if (((towers[lastchanged]->getPosition().x - mousePosition.x) < 0.2 && (towers[lastchanged]->getPosition().x - mousePosition.x) > -0.2 && (towers[lastchanged]->getPosition().y + mousePosition.y) < 0.4 && (towers[lastchanged]->getPosition().y + mousePosition.y) > -0.4) == false) {
			
			if (towers[lastchanged]->getType() == 3) {
				if ((t2 - t1).count() > 1000000000) {
					kone = 3;
					ktwo = 3;
					towers[lastchanged] = new Tower(this, 3, playerControlled, glm::vec3(-0.4, 0.7, 1), towers[lastchanged]->getPosition(), this->getTowerTextures().at(3), this->getProjectileTextures().at(2), this->getNumElem());
				}
			}
		}
		for (int i = 0; i < towers.size(); i++) {
			if ((towers[i]->getPosition().x - mousePosition.x) < 0.2 && (towers[i]->getPosition().x - mousePosition.x) > -0.2 && (towers[i]->getPosition().y + mousePosition.y) < 0.4 && (towers[i]->getPosition().y + mousePosition.y) > -0.4) {
				if (towers[i]->getPosition().x == -4.0) {

					k = kone;
				}
				else if (towers[i]->getPosition().x == -2.5) { k = ktwo; }

				if (newMouseStateleft == GLFW_RELEASE && oldMouseStateleft == GLFW_PRESS) {
					if (towers[i]->getType() == 3) {
						switch (k) {
						case 0:
							if (spendFunds(t1Cost))
								towers[i] = new Tower(this, k, playerControlled, glm::vec3(-0.4, 0.7, 1), towers[i]->getPosition(), this->getTowerTextures().at(k), this->getProjectileTextures().at(k), this->getNumElem());
							break;
						case 1:
							if (spendFunds(t2Cost))
								towers[i] = new Tower(this, k, playerControlled, glm::vec3(-0.4, 0.7, 1), towers[i]->getPosition(), this->getTowerTextures().at(k), this->getProjectileTextures().at(k), this->getNumElem());
							break;
						case 2: 
							if (spendFunds(t3Cost))
								towers[i] = new Tower(this, k, playerControlled, glm::vec3(-0.4, 0.7, 1), towers[i]->getPosition(), this->getTowerTextures().at(k), this->getProjectileTextures().at(k), this->getNumElem());
							break;
						}
					}
				}

				if (towers[i]->getPosition().x == -4.0) {
					kone = k;
				}
				else if(towers[i]->getPosition().x == -2.5) { ktwo = k; }
		}
	}

		oldMouseState = newMouseState;
		oldMouseStateleft = newMouseStateleft;
		#pragma endregion
	}

	//update towers
	for (int i = 0; i < towers.size(); i++)
	{
		towers.at(i)->update(deltaTime, otherCastles->getUnits());
	}

	for (int i = 0; i < units.size(); i++)
	{
		Unit* unit = units.at(i);
		unit->update(deltaTime, otherCastles);
		if (abs(unit->getPosition().x - otherCastles->getPosition().x) <= 0.5)
		{
			otherCastles->takeDamage(unit->getDamage() * 0.5);
			unit->takeDamage(100);
		}
		if (unit->getHealth() <= 0)
		{
			unit = NULL;
			delete unit;
			units.erase(units.begin() + i);
		}
	}

	for (int i = 0; i < otherCastles->getUnits().size(); i++) {
		Unit* enemyUnit = otherCastles->getUnits().at(i);

		if (abs(enemyUnit->getPosition().x - position.x) < 1) {
			shoot(enemyUnit->getPosition(),15);
		}
	}
}

//renders entitys of castle
void Castle::render(Shader& shader)
{
	GameObject::render(shader);
}

//if possible, decrements available funds
bool Castle::spendFunds(double funds)
{
	if (this->funds - funds >= 0)
	{
		this->funds -= funds;
		return true;
	}
	return false;
}

//removes projectile from vector
void Castle::removeProjectile(int index)
{
	Projectile* proj = projectiles.at(index);
	proj = NULL;
	delete proj;
	projectiles.erase(projectiles.begin() + index);
}

//shoots projectiles at target
void Castle::shoot(glm::vec3 target, int damage)
{
	double horDiff = (target.x - position.x);
	double verDiff = target.y - (position.y + 0.2);
	double dist = sqrt((horDiff * horDiff) + (verDiff * verDiff));
	double unitVectorX = horDiff / dist;
	double unitVectorY = verDiff / dist;
	projectiles.push_back(new Projectile(0, position + glm::vec3(0, 0.2, 0), projectileTextures[0], numElements, glm::vec2(unitVectorX, unitVectorY), 2, damage));
}
