#pragma once
#include "GameObject.h"
class Tower :
	public GameObject
{
public:
	Tower(glm::vec3 &entityPosition, GLuint entityTexture, GLint entityNumElements);
	~Tower();
};

