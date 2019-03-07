#pragma once
#include "Castle.h"
#include "Unit.h"
#include "Tower.h"
#include "Shader.h"

using namespace std;
class Board
{
public:
	Board(vector<Castle*> castles);
	~Board();

	//updates entities
	void update(double deltaTime);
	// Renders the board entities using a shader
	void render(Shader &shader);
private:
	vector<Castle*> castles;
};

