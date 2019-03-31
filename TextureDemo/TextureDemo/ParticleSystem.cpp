#include "ParticleSystem.h"



ParticleSystem::ParticleSystem(const char *vertPath, const char *fragPath) 
	: Shader(vertPath,fragPath)
{
}


ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::setAttributes()
{
	// Set attributes for shaders
	// Should be consistent with how we created the buffers for the particle elements
	GLint vertex_att = glGetAttribLocation(shaderProgram, "vertex");
	glVertexAttribPointer(vertex_att, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(vertex_att);

	GLint dir_att = glGetAttribLocation(shaderProgram, "dir");
	glVertexAttribPointer(dir_att, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void *)(2 * sizeof(GLfloat)));
	glEnableVertexAttribArray(dir_att);

	GLint time_att = glGetAttribLocation(shaderProgram, "t");
	glVertexAttribPointer(time_att, 1, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void *)(4 * sizeof(GLfloat)));
	glEnableVertexAttribArray(time_att);

	GLint tex_att = glGetAttribLocation(shaderProgram, "uv");
	glVertexAttribPointer(tex_att, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void *)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(tex_att);
}

void ParticleSystem::createParticleArray(void)
{
	// Each particle is a square with four vertices and two triangles

	// Number of attributes for vertices and faces
	const int vertex_attr = 7;  // 7 attributes per vertex: 2D (or 3D) position (2), direction (2), 2D texture coordinates (2), time (1)
//	const int face_att = 3; // Vertex indices (3)

	GLfloat vertex[] = {
		//  square (two triangles)
		//  Position      Color             Texcoords
		-0.5f, 0.5f,	 1.0f, 0.0f, 0.0f,		0.0f, 0.0f, // Top-left
		0.5f, 0.5f,		 0.0f, 1.0f, 0.0f,		1.0f, 0.0f, // Top-right
		0.5f, -0.5f,	 0.0f, 0.0f, 1.0f,		1.0f, 1.0f, // Bottom-right
		-0.5f, -0.5f,	 1.0f, 1.0f, 1.0f,		0.0f, 1.0f  // Bottom-left
	};

	GLfloat particleatt[1000 * vertex_attr];
	float theta, r, tmod;

	for (int i = 0; i < 1000; i++)
	{
		if (i % 4 == 0)
		{
			theta = (0.28*(rand() % 1000) / 1000.0f);
			r = 1.0f + 0.8*(rand() % 10000) / 10000.0f;
			tmod = (rand() % 10000) / 10000.0f;
		}
		// position	
		particleatt[i*vertex_attr + 0] = vertex[(i % 4) * 7 + 0];
		particleatt[i*vertex_attr + 1] = vertex[(i % 4) * 7 + 1];

		// velocity
		particleatt[i*vertex_attr + 2] = sin(theta)*r;
		particleatt[i*vertex_attr + 3] = cos(theta)*r;

		// phase
		particleatt[i*vertex_attr + 4] = tmod;

		// texture coordinate
		particleatt[i*vertex_attr + 5] = vertex[(i % 4) * 7 + 5];
		particleatt[i*vertex_attr + 6] = vertex[(i % 4) * 7 + 6];
	}

	GLuint face[] = {
		0, 1, 2, // t1
		2, 3, 0  //t2
	};

	GLuint manyface[1000 * 6];

	for (int i = 0; i < 1000; i++)
	{
		for (int j = 0; j < 6; j++)
			manyface[i * 6 + j] = face[j] + i * 4;
	}

	GLuint vbo, ebo;

	// Create buffer for vertices
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(particleatt), particleatt, GL_STATIC_DRAW);

	// Create buffer for faces (index buffer)
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(manyface), manyface, GL_STATIC_DRAW);
}

void ParticleSystem::drawParticles(glm::vec3 position, float rotation, GLuint texture, int particlesize)
{
	glDepthMask(GL_FALSE);
	// Select proper shader program to use
	glUseProgram(getShaderID());

	//set displacement
	int matrixLocation = glGetUniformLocation(getShaderID(), "x");
	int timeLocation = glGetUniformLocation(getShaderID(), "time");

	glm::mat4 rot = glm::mat4();
	rot = glm::translate(rot, position);
	rot = glm::rotate(rot, rotation, glm::vec3(0, 0, 1));
	rot = glm::scale(rot, glm::vec3(0.1));

	// get ready to draw, load matrix
	glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, &rot[0][0]);
	float time = glfwGetTime();
	glUniform1f(timeLocation, time);
	glBindTexture(GL_TEXTURE_2D, texture);

	// Draw 
	glBlendFunc(GL_ONE, GL_ONE);
	glDrawElements(GL_TRIANGLES, 6 * particlesize, GL_UNSIGNED_INT, 0);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_TRUE);
}