#include "Powerup.h"
#include "Castle.h"

Powerup::Powerup( int type, glm::vec3 towerScale, glm::vec3 &entityPosition, GLuint entityTexture, GLint entityNumElements)
	: GameObject(entityPosition, entityTexture, entityNumElements), parent(parent), type(type), size(entityNumElements)
{

}

Powerup::~Powerup()
{

}

//update tower logic
void Powerup::update(double deltaTime)
{

}

//renders tower and projectiles
void Powerup::render(Shader& shader)
{
	

	/*{
		ps.enable();
		ps.setAttributes();
		ps.drawParticles(position, 6, orientation - 80, projectileTexture, 250);
	}*/

	shader.enable();
	shader.setAttributes();

	GameObject::render(shader);
}


void Powerup::use() {

	switch (type) {
	case 0:
		((Castle*)parent)->addFunds(50);
		break;

	case 1:
		((Castle*)parent)->takeDamage(-20);
		break;	
	}
}