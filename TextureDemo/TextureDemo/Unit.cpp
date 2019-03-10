#include "Unit.h"

Unit::Unit(int type, 
		   bool playerControlled, 
		   Graph* graph, 
		   glm::vec3 unitScale,
		   glm::vec2 target,
           glm::vec3 &entityPosition, 
	       GLuint entityTexture, 
	       GLint entityNumElements)
	: GameObject (entityPosition,entityTexture,entityNumElements), type(type), playerControlled(playerControlled), graph(graph)
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
	//handles behavior of each unit type
	switch (type)
	{
	case 0:
		if (position.x >= path.at(0).x && position.y >= path.at(0).y) {
			path.erase(path.begin());
		}
		else if (position.x < path.at(0).x)
			position.x += movementSpeed * deltaTime;
		else if (position.y < path.at(0).y)
			position.y += movementSpeed * deltaTime;
		std::cout << path.at(0).x << " " << position.x << std::endl;
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	}
}