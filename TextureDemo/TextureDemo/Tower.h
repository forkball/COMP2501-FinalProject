#pragma once
#include "GameObject.h"
#include "Unit.h"
#include "Projectile.h"
#include <vector>

class Tower :
	public GameObject
{
public:
	Tower(GameObject* parent,
		  int type, 
		  bool playerControlled, 
		  glm::vec3 towerScale, 
		  glm::vec3 &entityPosition, 
		  GLuint entityTexture, 
		  GLuint projectileTexture,
		  GLint entityNumElements);
	~Tower();
	void update(double deltaTime, std::vector<Unit*> enemies);
	void render(Shader &shader, ParticleSystem &ps);
	void shoot(glm::vec3 target, int damage);
	void removeProjectile(int index);
	inline std::vector<Projectile*> getProjectiles() { return projectiles; }
	inline double getHealth() { return health; }
	inline int getType() { return type; }
	void setType(int i) { type = i; }
private:
	GameObject* parent;
	int type = 0;	
	bool playerControlled, flame = false;
	glm::vec3 targetPosition;
	GLuint projectileTexture;
	GLuint size;
	std::vector<Projectile*> projectiles;
	double health, shootingRange = 1,
		  projectileTimer = glfwGetTime(), 
		  projectileDelay = 2;
};

