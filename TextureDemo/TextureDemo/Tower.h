#pragma once
#include "GameObject.h"
class Tower :
	public GameObject
{
public:
	Tower(int type, glm::vec3 scale, glm::vec3 &entityPosition, GLuint entityTexture, GLint entityNumElements);
	~Tower();
	void update(double deltaTime);
private:
	int type = 0;
	double health;
};

