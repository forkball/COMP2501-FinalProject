#pragma once
#include "GameObject.h"
#include "Unit.h"
#include "Tower.h"
#include "Window.h"

using namespace std;
class Castle :
	public GameObject
{
public:
	Castle(bool playerControlled, glm::vec3 &entityPosition, glm::vec3 spriteScale, GLuint entityTexture, GLint entityNumElements, vector<GLuint> unitTextures, vector<GLuint> towerTextures);
	~Castle();
	//updates entities
	void update(double deltaTime);
	void createUnit(int type, glm::vec3 position);
	void createTower(int type, glm::vec3 position);
	inline vector<Unit*> getUnits() { return units; }
	inline vector<Tower*> getTower() { return towers; }
	glm::vec2 getMousePosition();
private:
	GLint numElem;
	vector<Unit*> units;
	vector<GLuint> unitTextures;
	vector<Tower*> towers;
	vector<GLuint> towerTextures;
	bool playerControlled;
	double health;
};

