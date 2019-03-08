#pragma once
#include "GameObject.h"
#include "Unit.h"
#include "Tower.h"

using namespace std;
class Castle :
	public GameObject
{
public:
	Castle(bool playerControlled,
		   glm::vec3 &entityPosition,
		   glm::vec3 spriteScale,
		   GLuint entityTexture,
		   GLint entityNumElements,
		   vector<GLuint> projectileTextures,
		   vector<GLuint> unitTextures, 
		   vector<GLuint> towerTextures);
	~Castle();
	//render entities
	void render(Shader &shader);
	//updates entities
	void update(double deltaTime,glm::vec2 mousePosition, Castle* otherCastles);
	void createUnit(int type, bool playerControlled, glm::vec3 position);
	void createTower(int type, bool playerControlled, glm::vec3 position);
	inline vector<Unit*> getUnits() { return units; }
	inline vector<Tower*> getTower() { return towers; }
private:
	GLint numElem;
	//holds all units
	vector<Unit*> units;
	//holds textures of unit types
	vector<GLuint> unitTextures;
	//holds all towers
	vector<Tower*> towers;
	//holds textures of tower types
	vector<GLuint> towerTextures;
	//holds textures of projectiles
	vector<GLuint> projectileTextures;
	bool playerControlled;
	double health;
};

