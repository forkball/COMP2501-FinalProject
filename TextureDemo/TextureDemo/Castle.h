#pragma once
#include "GameObject.h"
#include "Unit.h"
#include "Tower.h"
#include "Graph.h"

class Castle :
	public GameObject
{
public:
	Castle(bool playerControlled,
		   glm::vec3 &entityPosition,
		   glm::vec3 spriteScale,
		   GLuint entityTexture,
		   GLint entityNumElements,
		   Graph* graph,
		   std::vector<GLuint> projectileTextures,
		   std::vector<GLuint> unitTextures,
		   std::vector<GLuint> towerTextures);
	~Castle();
	//render entities
	void render(Shader &shader);
	//updates entities
	void update(double deltaTime,glm::vec2 mousePosition, Castle* otherCastles);
	void createUnit(int type, bool playerControlled, glm::vec3 position);
	void createTower(int type, bool playerControlled, glm::vec3 position);
	inline std::vector<Unit*> getUnits() { return units; }
	inline std::vector<Tower*> getTower() { return towers; }
private:
	//holds pathplanning graph
	Graph* graph;
	GLint numElem;
	//holds all units
	std::vector<Unit*> units;
	//holds textures of unit types
	std::vector<GLuint> unitTextures;
	//holds all towers
	std::vector<Tower*> towers;
	//holds textures of tower types
	std::vector<GLuint> towerTextures;
	//holds textures of projectiles
	std::vector<GLuint> projectileTextures;
	//reference to the particle system
	ParticleSystem particleSystem;
	bool playerControlled;
	double health,
		funds = 100,
		spawnDelay = 5,
		spawnTimer = 0;
};

