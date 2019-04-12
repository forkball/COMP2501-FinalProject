#include "Castle.h"
#include <time.h>

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
		static int oldMouseState = GLFW_RELEASE;
		int newMouseState = glfwGetMouseButton(Window::getWindow(), GLFW_MOUSE_BUTTON_RIGHT);
		static int oldMouseStateleft = GLFW_RELEASE;
		int newMouseStateleft = glfwGetMouseButton(Window::getWindow(), GLFW_MOUSE_BUTTON_LEFT);
		if (newMouseState == GLFW_RELEASE && oldMouseState == GLFW_PRESS) {
			for (int i = 0; i < towers.size(); i++) {


				

				if ((towers[i]->getPosition().x - mousePosition.x) < 0.2 && (towers[i]->getPosition().x - mousePosition.x) > -0.2 && (towers[i]->getPosition().y + mousePosition.y) < 0.4 && (towers[i]->getPosition().y + mousePosition.y) > -0.4) {
					// only works for player controlled towers due to above condition
					
					if (towers[i]->getPosition().x == -4.0) {

						k = kone;
					}
					else if (towers[i]->getPosition().x == -2.5)  { k = ktwo; }

					if (towers[i]->getType() == 3) {
						switch (k) {

						case 0:
							k++;
							towers[i] = new Tower(this, 3, playerControlled, glm::vec3((playerControlled) ? 0.4 : -0.4, 0.7, 1), towers[i]->getPosition(), this->getTowerTextures().at(k), this->getProjectileTextures().at(0), this->getNumElem());
							
							break;
						case 1:
							k++;
							towers[i] = new Tower(this, 3, playerControlled, glm::vec3((playerControlled) ? 0.4 : -0.4, 0.7, 1), towers[i]->getPosition(), this->getTowerTextures().at(k), this->getProjectileTextures().at(1), this->getNumElem());
							
							break;
						case 2:
							k++;
							towers[i] = new Tower(this, 3, playerControlled, glm::vec3((playerControlled) ? 0.4 : -0.4, 0.7, 1), towers[i]->getPosition(), this->getTowerTextures().at(k), this->getProjectileTextures().at(2), this->getNumElem());
							
							break;
						case 3:
							k = 0;
							towers[i] = new Tower(this, 3, playerControlled, glm::vec3((playerControlled) ? 0.4 : -0.4, 0.7, 1), towers[i]->getPosition(), this->getTowerTextures().at(k), this->getProjectileTextures().at(3), this->getNumElem());
							
							break;
						}
					}


					if (towers[i]->getPosition().x == -4.0) {

						kone = k;
						std::cout << k;

					}
					else if (towers[i]->getPosition().x == -2.5) { ktwo = k; }
				
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

						towers[i] = new Tower(this, k, playerControlled, glm::vec3((playerControlled) ? 0.4 : -0.4, 0.7, 1), towers[i]->getPosition(), this->getTowerTextures().at(k), this->getProjectileTextures().at(k), this->getNumElem());
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
