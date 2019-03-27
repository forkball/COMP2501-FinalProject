#pragma once
#include "GameObject.h"
#include "Unit.h"
#include "Projectile.h"

using namespace std;
class Tower :
	public GameObject
{
public:
	Tower(int type, 
		  bool playerControlled, 
		  glm::vec3 towerScale, 
		  glm::vec3 &entityPosition, 
		  GLuint entityTexture, 
		  GLuint projectileTexture,
		  GLint entityNumElements);
	~Tower();
	void update(double deltaTime, vector<Unit*> enemies);
	void render(Shader &shader);
	void shoot(glm::vec3 target, int damage);
	void removeProjectile(int index);
	inline vector<Projectile*> getProjectiles() { return projectiles; }
private:
	int type = 0;	
	bool playerControlled;
	GLuint projectileTexture;
	GLuint size;
	vector<Projectile*> projectiles;
	double health, shootingRange = 0.7,
		  projectileTimer = glfwGetTime(), 
		  projectileDelay = 2;
};

