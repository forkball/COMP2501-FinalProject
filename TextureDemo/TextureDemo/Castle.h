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
		   std::vector<GLuint> projectileTextures,
		   std::vector<GLuint> unitTextures,
		   std::vector<GLuint> towerTextures);
	~Castle();
	//render entities
	void render(Shader &shader, ParticleSystem &ps);
	//updates entities
	void update(double deltaTime,glm::vec2 mousePosition, Castle* otherCastles);
	//spend funds, return if funds were spent or not
	bool spendFunds(double funds);
	//increase funds
	inline void addFunds(double funds) { this->funds += funds; }
	//takes damage
	inline void takeDamage(double dmg) { health -= dmg;  }
	//shooting functions
	void shoot(glm::vec3 target, int damage);
	void removeProjectile(int index);
	inline std::vector<Projectile*> getProjectiles() { return projectiles; }
	//getters
	inline std::vector<Tower*> getTowers() { return towers; }
	inline std::vector<Unit*> getUnits() { return units; }
	inline std::vector<GLuint> getUnitTextures() { return unitTextures; }
	inline std::vector<GLuint> getTowerTextures() { return towerTextures; }
	inline std::vector<GLuint> getProjectileTextures() { return projectileTextures; }
	inline GLint getNumElem() { return numElem; }
	inline double getHealth() { return health; }
	inline double getFunds() { return funds; }
	inline bool getPowerup() { return powerup; }
	//add to vectors
	inline void addUnit(Unit* u) { units.push_back(u); }
	inline void addTower(Tower* t) { towers.push_back(t); }
private:
	//holds projectiles
	std::vector<Projectile*> projectiles;
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
	bool playerControlled;
	bool powerup = false;
	bool heal;
	double health,
		funds = 100,
		t1Cost = 150,
		t2Cost = 200,
		t3Cost = 250;
};

