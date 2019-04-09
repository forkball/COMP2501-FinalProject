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
	  particleSystem(particleSystem),
	  playerControlled(playerControlled), 
	  projectileTextures(projectileTextures), 
	  unitTextures(unitTextures), 
	  numElem(entityNumElements), 
	  towerTextures(towerTextures)
{
	scale = spriteScale;
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
		std::cout << funds << std::endl;
		#pragma region Mouse Control
		static int oldMouseState = GLFW_RELEASE;
		int newMouseState = glfwGetMouseButton(Window::getWindow(), GLFW_MOUSE_BUTTON_LEFT);
		if (newMouseState == GLFW_RELEASE && oldMouseState == GLFW_PRESS) {
			std::cout << mousePosition.x << std::endl;
			std::cout << position.x << std::endl;

			for (int i = 0; i < towers.size(); i++) {

				if ((towers[i]->getPosition().x - mousePosition.x) < 0.2 && (towers[i]->getPosition().x - mousePosition.x) > -0.2) {
				
					// only works for player controlled towers due to above condition
					std::cout << towers[i]->getId() << " yes " << mousePosition.x;
				}
			
			}

		}
		oldMouseState = newMouseState;
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
		unit->update(deltaTime, otherCastles->getUnits());
		if (unit->getHealth() <= 0)
		{
			unit = NULL;
			delete unit;
			units.erase(units.begin() + i);
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