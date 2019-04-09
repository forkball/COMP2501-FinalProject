#pragma once
#include "GameObject.h"
#include "Graph.h"
#include "Projectile.h"

class Unit :
	public GameObject
{
public:
	Unit(GameObject* parent,
		 int type, 
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
	void update(double deltaTime, std::vector<Unit*> enemies);
	void render(Shader& shader, ParticleSystem &ps);
	void shoot(glm::vec3 target, GLuint projectileTexture, int damage);
	void removeProjectile(int index);
	inline void takeDamage(double dmg) { health -= dmg; }
	inline void freeze() { freezeSlow = true; }
	inline double getHealth() { return health; }
private:
	GLuint freezeTexture;
	GLuint size;
	int type = 0;
	bool playerControlled, freezeSlow, enemyNear;
	double health, damage, orgSpeed, movementSpeed, enemyDist, attackDelay, attackTimer = 0, freezeTimer = 0, freezeDelay = 3;
	GameObject* parent;
	Unit* enemy = NULL;
	Graph* graph;
	std::vector<glm::vec2> path;
	std::vector<Projectile*> projectiles;
};

