#include "Unit.h"


Unit::Unit(int type, glm::vec3 scale, glm::vec3 &entityPosition, GLuint entityTexture, GLint entityNumElements) : GameObject (entityPosition,entityTexture,entityNumElements), type(type)
{
	scale = glm::vec3(1);
}

Unit::~Unit()
{
}

void Unit::update(double deltaTime)
{
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