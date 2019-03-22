#pragma once
#include "Shader.h"

class ParticleSystem :
	public Shader
{
public:
	ParticleSystem(const char *vertPath, const char *fragPath);
	~ParticleSystem();

	//creates particle geometry
	void createParticleArray(void);
	//sets shader attributes
	void setAttributes ();

	//draws particles
	void drawParticles(glm::vec3 position, GLuint texture, int particlesize);
};

