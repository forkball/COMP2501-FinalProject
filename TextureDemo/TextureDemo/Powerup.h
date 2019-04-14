#pragma once
#include "GameObject.h"
#include "Graph.h"

class Powerup :
	public GameObject
{
public:
	Powerup(
		int type,
		glm::vec3 towerScale,
		glm::vec3 &entityPosition,
		GLuint entityTexture,
		GLint entityNumElements);
	~Powerup();
	void update(double deltaTime);
	void render(Shader &shader);
	inline int getType() { return type; }
	void setType(int i) { type = i; }
	void use();
private:
	GameObject* parent;
	int type = 0;
	glm::vec3 targetPosition;
	GLuint size;
};


