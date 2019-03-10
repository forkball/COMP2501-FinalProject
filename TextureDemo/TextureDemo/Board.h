#pragma once
#include "Castle.h"
#include "Unit.h"
#include "Tower.h"
#include "Shader.h"
#include "Camera.h"
#include "Graph.h"

using namespace std;
class Board
{
public:
	Board(Camera* camera, vector<Castle*> castles);
	~Board();

	//updates entities
	void update(double deltaTime);
	// Renders the board entities using a shader
	void render(Shader &shader);
private:
	Camera* camera;
	vector<Castle*> castles;
};

