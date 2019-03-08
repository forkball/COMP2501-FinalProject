#include "Unit.h"


Unit::Unit(int type, bool playerControlled, glm::vec3 unitScale, glm::vec3 &entityPosition, GLuint entityTexture, GLint entityNumElements) 
	: GameObject (entityPosition,entityTexture,entityNumElements), type(type)
{
	scale = unitScale;
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
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	}
}