#include "Board.h"

Board::Board(Camera* camera, ParticleSystem* particleSystem, Graph* graph, vector<Castle*> castles)
	: camera(camera), particleSystem(particleSystem), graph(graph) ,castles(castles)
{
	spawnTimer = glfwGetTime() - spawnDelay;
	srand(time(NULL));
	createTower(0,(int)rand() % 3, 0, glm::vec3(-4.0, 0.5, 0));
	createTower(0,(int)rand() % 3, 0, glm::vec3(-2.5, 0.5, 0));
	createTower(1,(int)rand() % 3, 1, glm::vec3(4.0, 0.5, 0));
	createTower(1,(int)rand() % 3, 1, glm::vec3(2.5, 0.5, 0));
}

const double Board::heights[] = {-0.32, -0.58, -0.84 };

Board::~Board()
{
	for (int i = 0; i < castles.size(); i++)
	{
		castles.at(0) = NULL;
		delete castles.at(0);
		castles.erase(castles.begin());
	}
}

void Board::update(double deltaTime)
{
	glm::vec2 mousePosition = camera->getMousePosition();
	glm::vec2 cameraPosition = glm::vec2(camera->getPosition().x, camera->getPosition().y);
	
	//calls castle updates
	for (int i = 0; i < castles.size(); i++)
	{
		castles.at(i)->update(deltaTime, (2.0f * mousePosition - cameraPosition), castles.at((i) ? 0 : 1));
	}

	if ((glfwGetTime() - spawnTimer) > spawnDelay)
	{
		spawnTimer = glfwGetTime();
		createUnit(0,(int)rand() % 4, 0, glm::vec3(-4.92, heights[(int)rand() % 3], 0));
	}

	#pragma region Key Control
	if (((glfwGetTime() - createTimer)) > createDelay) {
		if (glfwGetKey(Window::getWindow(), GLFW_KEY_1) == GLFW_PRESS) {
			if (castles.at(1)->spendFunds(u1Cost)) {
				createUnit(1, 0, 1, glm::vec3(4.92, heights[(int)rand() % 3], 0));
				createTimer = glfwGetTime();
			}
		}
		else if (glfwGetKey(Window::getWindow(), GLFW_KEY_2) == GLFW_PRESS) {
			if (castles.at(1)->spendFunds(u2Cost)) {
				createUnit(1, 1, 1, glm::vec3(4.92, heights[(int)rand() % 3], 0));
				createTimer = glfwGetTime();
			}
		}
		else if (glfwGetKey(Window::getWindow(), GLFW_KEY_3) == GLFW_PRESS) {
			if (castles.at(1)->spendFunds(u3Cost)) {
				createUnit(1, 2, 1, glm::vec3(4.92, heights[(int)rand() % 3], 0));
				createTimer = glfwGetTime();
			}
		}
		else if (glfwGetKey(Window::getWindow(), GLFW_KEY_4) == GLFW_PRESS) {
			if (castles.at(1)->spendFunds(u4Cost)) {
				createUnit(1, 3, 1, glm::vec3(4.92, heights[(int)rand() % 3], 0));
				createTimer = glfwGetTime();
			}
		}
	}
	#pragma endregion
}

//renders all board entities 
void Board::render(Shader &shader, ParticleSystem &ps)
{
	for (int i = 0; i < castles.size(); i++)
	{
		castles.at(i)->render(shader);
		//renders towers
		for (int j = 0; j < castles.at(i)->getTowers().size(); j++)
		{
			castles.at(i)->getTowers().at(j)->render(shader,ps);
		}

		//renders units
		for (int j = 0; j < castles.at(i)->getUnits().size(); j++)
		{
			castles.at(i)->getUnits().at(j)->render(shader,ps);
		}
	}
}

//creates a new unit
void Board::createUnit(int castleNumber, int type, bool playerControlled, glm::vec3 position)
{
	Castle* castle = castles.at(castleNumber);
	double health, movementSpeed;
	//sets unit stats based of type
	switch (type) {
	case 0:
		health = 75; movementSpeed = 0.15;
		break;
	case 1:
		health = 50; movementSpeed = 0.2;
		break;
	case 2:
		health = 100; movementSpeed = 0.1;
		break;
	case 3:
		health = 75; movementSpeed = 0.3;
		break;
	}

	castle->addUnit(new Unit(castle,
							 type,
		 			    	 health,
							 playerControlled,
							 movementSpeed,
							 graph,
							 glm::vec3((playerControlled) ? -0.1 : 0.1, 0.15, 1),
							 (playerControlled) ? glm::vec2(-6.06, -0.32) : glm::vec2(6.06, -0.32),
							 position,
							 castle->getUnitTextures().at(type),
							 castle->getNumElem()));
}

//creates a new tower
void Board::createTower(int castleNumber, int type, bool playerControlled, glm::vec3 position)
{
	Castle* castle = castles.at(castleNumber);
	castle->addTower(new Tower(castle,
		type,
		playerControlled,
		glm::vec3((playerControlled) ? 0.4 : -0.4, 0.7, 1),
		position,
		castle->getTowerTextures().at(type),
		castle->getProjectileTextures().at(type),
		castle->getNumElem()));
}
