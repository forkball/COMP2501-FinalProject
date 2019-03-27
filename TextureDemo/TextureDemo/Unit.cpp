#include "Unit.h"

Unit::Unit(int type,
	double health,
	bool playerControlled,
	double movementSpeed,
	Graph* graph,
	glm::vec3 unitScale,
	glm::vec2 target,
	glm::vec3 &entityPosition,
	GLuint entityTexture,
	GLint entityNumElements)
	: GameObject(entityPosition, entityTexture, entityNumElements), type(type), health(health), playerControlled(playerControlled), orgSpeed(movementSpeed), graph(graph)
{
	scale = unitScale;
	health = 100;
	path = graph->pathfind(glm::vec2(position.x, position.y), target);
}

Unit::~Unit()
{
}

void Unit::update(double deltaTime)
{
	//handles freeze status
	if (freezeSlow) {
		if (((glfwGetTime() - freezeTimer) / 1000) > freezeDelay)
			freezeSlow = false;
		movementSpeed = orgSpeed / 2;
	}
	else movementSpeed = orgSpeed;

	//movement control
	if (path.size() > 0) {
		if (position.x >= path.at(0).x && position.y >= path.at(0).y)
			path.erase(path.begin());
		else if (position.x < path.at(0).x)
			position.x += movementSpeed * deltaTime;
		else if (position.y < path.at(0).y)
			position.y += movementSpeed * deltaTime;
	}

	//handles behavior of each unit type
	switch (type)
	{
	//knight
	case 0:
		break;
	//archer
	case 1:
		break;
	//catapult
	case 2:
		break;
	//cavalry
	case 3:
		break;
	}
}