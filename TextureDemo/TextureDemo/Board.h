#pragma once
#include "Castle.h"
#include "Unit.h"
#include "Tower.h"
#include "Shader.h"
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
private:
	ParticleSystem* particleSystem;
	Graph* graph;
	Camera* camera;
	vector<Castle*> castles;
	float spawnDelay = 5,
		  spawnTimer = 0;
};

