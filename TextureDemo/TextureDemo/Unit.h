#pragma once
#include "GameObject.h"
#include "Graph.h"

class Unit :
	public GameObject
{
public:
	Unit(int type, 
		 double health,
		 bool playerControlled,
		 double movementSpeed,
		 Graph* graph,
		 glm::vec3 unitScale,
		 glm::vec2 target, 
		 glm::vec3 &entityPosition, 
		 GLuint entityTexture, 
		 GLint entityNumElements);
	~Unit();
	void update(double deltaTime);
	inline void takeDamage(double dmg) { health -= dmg; }
	inline double getHealth() { return health; }
private:
	int type = 0;
	bool playerControlled;
	double health, movementSpeed = 0.2;
	Graph* graph;
	std::vector<glm::vec2> path;
};

