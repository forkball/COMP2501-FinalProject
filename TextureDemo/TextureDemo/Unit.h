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
	void update(double deltaTime, GameObject* enemyCastle);
	void render(Shader& shader, ParticleSystem &ps);
	void shoot(glm::vec3 target, GLuint projectileTexture, int damage);
	void removeProjectile(int index);
	inline void freeze() { freezeSlow = true; }
	inline int getType() { return type; }
private:
	GLuint freezeTexture;
	GLuint size;
	int type = 0;
	bool playerControlled, freezeSlow, enemyNear;
	double damage, orgSpeed, movementSpeed, enemyDist, attackDelay, attackTimer = 0, freezeTimer = 0, freezeDelay = 3;
	GameObject* parent;
	GameObject* enemy = NULL;
	Graph* graph;
	glm::vec2 target;
	std::vector<glm::vec2> path;
	std::vector<Projectile*> projectiles;
};

