#include "Board.h"

Board::Board(vector<Castle*> castles) : castles(castles)
{
}

Board::~Board()
{
}

void Board::update(double deltaTime)
{
	//calls castle updates
	for (int i = 0; i < castles.size(); i++)
	{
		castles.at(i)->update(deltaTime);
	}
}

//renders all board entities 
void Board::render(Shader &shader)
{
	for (int i = 0; i < castles.size(); i++)
	{
		castles.at(i)->render(shader);
	}
}
