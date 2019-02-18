#pragma once
#include "GameObject.h"
class Castle :
	public GameObject
{
public:
	Castle(glm::vec3 &entityPosition, GLuint entityTexture, GLint entityNumElements);
	~Castle();
};

