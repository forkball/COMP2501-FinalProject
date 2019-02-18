#pragma once
#include "GameObject.h"
class Unit :
	public GameObject
{
public:
	Unit(glm::vec3 &entityPosition, GLuint entityTexture, GLint entityNumElements);
	~Unit();
};

