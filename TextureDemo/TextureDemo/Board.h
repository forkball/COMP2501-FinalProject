#pragma once
#include "Castle.h"
#include "Unit.h"
#include "Tower.h"
#include "Camera.h"
#include "Graph.h"
#include "ParticleSystem.h"

using namespace std;
class Board
{
public:
	Board(Camera* camera, ParticleSystem* particleSystem, Graph* graph, vector<Castle*> castles);
	~Board();

	//updates entities
	void update(double deltaTime);

	// Renders the board entities using a shader
	void render(Shader &shader, ParticleSystem &ps);

	//creating entities
	void createUnit(int castleNumber, int type, bool playerControlled, glm::vec3 position);
	void createTower(int castleNumber, int type, bool playerControlled, glm::vec3 position);

	//getter
	inline vector<Castle*> getCastles() { return castles; }

private:
	ParticleSystem* particleSystem;
	Graph* graph;
	Camera* camera;
	vector<Castle*> castles;
	const static double heights[];
	float spawnDelay = 20,
		  spawnTimer = 0,
	      u1Cost = 25,
		  u2Cost = 25,
		  u3Cost = 25,
		  u4Cost = 25,
		  createTimer = 0,
		  createDelay = 1;
};

