#pragma once
#include "GameObject.h"

class Unit :
	public GameObject
{
public:
	Unit(int type, glm::vec3 scale, glm::vec3 &entityPosition, GLuint entityTexture, GLint entityNumElements);
	~Unit();
	void update(double deltaTime);
private:
	int type;
	double health;
};

