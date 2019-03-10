#include "Castle.h"
#include <time.h>

//constructor
Castle::Castle(bool playerControlled,
			   glm::vec3 &entityPosition, 
	           glm::vec3 spriteScale, 
			   GLuint entityTexture, 
			   GLint entityNumElements,
			   Graph* graph,
			   std::vector<GLuint> projectileTextures, 
			   std::vector<GLuint> unitTextures, 
			   std::vector<GLuint> towerTextures) 
	: GameObject(entityPosition, entityTexture, entityNumElements), 
	  graph(graph),
	  playerControlled(playerControlled), 
	  projectileTextures(projectileTextures), 
	  unitTextures(unitTextures), 
	  numElem(entityNumElements), 
	  towerTextures(towerTextures)
{
	scale = spriteScale;
	spawnTimer = glfwGetTime();
	if (!playerControlled) {
		createTower(0, playerControlled, position + glm::vec3(2.0, 0, 0));
		createTower(0, playerControlled, position + glm::vec3(3.5, 0, 0));
	} else {
		createTower(0, playerControlled, position + glm::vec3(-2.0, 0, 0));
		createTower(0, playerControlled, position + glm::vec3(-3.5, 0, 0));
	}
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

//creates a new unit
void Castle::createUnit(int type, bool playerControlled, glm::vec3 position)
{
	units.push_back(new Unit(type, 
							 playerControlled, 
							 graph,
							 glm::vec3((playerControlled) ? -0.1 : 0.1, 0.15, 1),
							 (playerControlled) ? glm::vec2(-6.06, -0.32) : glm::vec2(6.06, -0.32),
							 position, 
							 unitTextures[type], 
							 numElem));
}

//creates a new tower
void Castle::createTower(int type, bool playerControlled, glm::vec3 position)
{
	towers.push_back(new Tower(type, 
							   playerControlled, 
		                       glm::vec3((playerControlled) ? 0.4 : -0.4, 0.7, 1), 
							   position, 
							   towerTextures[type], 
							   projectileTextures[type], 
							   numElem));
}

//update function
void Castle::update(double deltaTime, glm::vec2 mousePosition, Castle* otherCastles)
{
	//player controls
	if (playerControlled)
	{
		static int oldState = GLFW_RELEASE;
		int newState = glfwGetMouseButton(Window::getWindow(), GLFW_MOUSE_BUTTON_LEFT);
		if (newState == GLFW_RELEASE && oldState == GLFW_PRESS) {
			std::cout << mousePosition.x << std::endl;
			std::cout << position.x << std::endl;
		}
		oldState = newState;
	}
	else 
	{
		if ((glfwGetTime() - spawnTimer) > spawnDelay) 
		{
			srand(time(NULL));
			double heights[] = { -0.32,-0.58,-0.84 };
			spawnTimer = glfwGetTime();
			createUnit(0, playerControlled, glm::vec3(-4.92, heights[(int)rand() % 3], 0));

		}
	}

	//update towers
	for (int i = 0; i < towers.size(); i++)
	{
		towers.at(i)->update(deltaTime,otherCastles->getUnits());
	}

	for (int i = 0; i < units.size(); i++)
	{
		Unit* unit = units.at(i);
		unit->update(deltaTime);
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
	//renders towers
	for (int i = 0; i < towers.size(); i++)
	{
		towers.at(i)->render(shader);
	}

	//renders units
	for (int i = 0; i < units.size(); i++)
	{
		units.at(i)->render(shader);
	}
	
	GameObject::render(shader);
}
