#pragma once
#include "GameObject.h"

class Unit :
	public GameObject
{
public:
	Unit(int type, bool playerControlled, glm::vec3 unitScale, glm::vec3 &entityPosition, GLuint entityTexture, GLint entityNumElements);
	~Unit();
	void update(double deltaTime);
private:
	int type = 0;
	bool playerControlled;
	double health;
};

