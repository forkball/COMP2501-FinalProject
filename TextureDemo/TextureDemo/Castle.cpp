#include "Castle.h"

//constructor
Castle::Castle(bool playerControlled ,glm::vec3 &entityPosition, glm::vec3 spriteScale, GLuint entityTexture, GLint entityNumElements, vector<GLuint> unitTextures, vector<GLuint> towerTextures) :
	GameObject(entityPosition, entityTexture, entityNumElements), playerControlled(playerControlled), unitTextures(unitTextures), numElem(entityNumElements), towerTextures(towerTextures)
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

//creates a new unit
void Castle::createUnit(int type, glm::vec3 position)
{
	units.push_back(new Unit(type, glm::vec3((playerControlled) ? -1 : 1, 1, 1), position, unitTextures[type], numElem));
}

//creates a new tower
void Castle::createTower(int type, glm::vec3 position)
{
	towers.push_back(new Tower(type, glm::vec3((playerControlled) ? -1 : 1, 1, 1), position, unitTextures[type], numElem));
}

//gets the mouse position
glm::vec2 Castle::getMousePosition()
{
	//holds the mouse positions
	double xpos, ypos;
	//gets the mouse positions
	glfwGetCursorPos(Window::getWindow(), &xpos, &ypos);
	//returns a vector with the mouse positions in relation to the window size
	return glm::vec2(xpos, ypos);
}

//update function
void Castle::update(double deltaTime)
{
	//player controls
	if (playerControlled)
	{
		static int oldState = GLFW_RELEASE;
		int newState = glfwGetMouseButton(Window::getWindow(), GLFW_MOUSE_BUTTON_LEFT);
		if (newState == GLFW_RELEASE && oldState == GLFW_PRESS) {
			std::cout << "left mouse" << std::endl;
		}
		oldState = newState;
	}
}
