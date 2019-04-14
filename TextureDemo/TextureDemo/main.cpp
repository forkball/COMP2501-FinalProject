// COMP 2501 Final Project
// Eros Di Pede (101035030)
// Martin Nikolovski (101042483)

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <locale>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <SOIL/SOIL.h>
#include <chrono>
#include <thread>
#include "glm/ext.hpp"

#include "Shader.h"
#include "Window.h"
#include "Camera.h"
#include "Board.h"
#include "Graph.h"
#include "Projectile.h"
#include "ParticleSystem.h"

//static ParticleSystem particleSystem;
// Macro for printing exceptions
#define PrintException(exception_object)\
	std::cerr << exception_object.what() << std::endl

// Globals that define the OpenGL window and viewport
const std::string window_title_g = "Final Assignment - Tower Defense";
const unsigned int window_width_g = 800;
const unsigned int window_height_g = 600;
const glm::vec3 viewport_background_color_g(0.3, 0.5, 0.0);

// Global texture info
GLuint tex[30];

// Create the geometry for a square (with two triangles)
// Return the number of array elements that form the square
int CreateSquare(void) {
	// The face of the square is defined by four vertices and two triangles

	// Number of attributes for vertices and faces
//	const int vertex_att = 7;  // 7 attributes per vertex: 2D (or 3D) position (2), RGB color (3), 2D texture coordinates (2)
//	const int face_att = 3; // Vertex indices (3)

	GLfloat vertex[]  = {
		//  square (two triangles)
		   //  Position      Color             Texcoords
		-0.5f, 0.5f,	 1.0f, 0.0f, 0.0f,		0.0f, 0.0f, // Top-left
		0.5f, 0.5f,		 0.0f, 1.0f, 0.0f,		1.0f, 0.0f, // Top-right
		0.5f, -0.5f,	 0.0f, 0.0f, 1.0f,		1.0f, 1.0f, // Bottom-right
		-0.5f, -0.5f,	 1.0f, 1.0f, 1.0f,		0.0f, 1.0f  // Bottom-left
	};


	GLuint face[] = {
		0, 1, 2, // t1
		2, 3, 0  //t2
	};

	GLuint vbo, ebo;

	// Create buffer for vertices
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

	// Create buffer for faces (index buffer)
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(face), face, GL_STATIC_DRAW);

	// Return number of elements in array buffer (6 in this case)
	return sizeof(face) / sizeof(GLuint);
}


void setthisTexture(GLuint w, char *fname)
{
	glBindTexture(GL_TEXTURE_2D, w);

	int width, height;
	unsigned char* image = SOIL_load_image(fname, &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	// Texture Wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Texture Filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void setallTexture(void)
{
//	tex = new GLuint[4];
	glGenTextures(30, tex);
	setthisTexture(tex[0], "castle1.png");
	setthisTexture(tex[1], "castle2.png");
	setthisTexture(tex[2], "knight1.png");
	setthisTexture(tex[3], "knight2.png");
	setthisTexture(tex[4], "cavalry1.png");
	setthisTexture(tex[5], "cavalry2.png");
	setthisTexture(tex[6], "archer1.png");
	setthisTexture(tex[7], "archer2.png");
	setthisTexture(tex[8], "catapult1.png");
	setthisTexture(tex[9], "catapult2.png");
	setthisTexture(tex[10], "tower1.png");
	setthisTexture(tex[11], "tower2.png");
	setthisTexture(tex[12], "magma1.png");
	setthisTexture(tex[13], "magma2.png");
	setthisTexture(tex[14], "ice1.png");
	setthisTexture(tex[15], "ice2.png");
	setthisTexture(tex[16], "powerup.png");
	setthisTexture(tex[17], "proj1.png");
	setthisTexture(tex[18], "flame.png");
	setthisTexture(tex[19], "freeze.png");
	setthisTexture(tex[20], "freezeparticle.png");
	setthisTexture(tex[21], "text.png");
	setthisTexture(tex[22], "pause.png");
	setthisTexture(tex[23], "enter.png");
	setthisTexture(tex[24], "sand1.png");
	setthisTexture(tex[25], "tower3.png");
	setthisTexture(tex[26], "magma3.png");
	setthisTexture(tex[27], "ice3.png");
	setthisTexture(tex[28], "orb.png");
	setthisTexture(tex[29], "proj.png");

	glBindTexture(GL_TEXTURE_2D, tex[0]);
}

	// implemented from pinball assignment
void renderText(std::string &stringToRender, Shader &textShader, glm::vec3 color, glm::vec3 position, GLfloat size) {
	// Enable the shader and bind the proper text spritesheet texture
	textShader.enable();
	textShader.setAttributes();
	glBindTexture(GL_TEXTURE_2D, tex[21]);

	// Loop through each character and draw it
	for (int i = 0; i < stringToRender.size(); i++) {
		// We need to get the character and map it to a UV coordinate the represents where it is located in the text spritesheet texture
		// First get the character and make sure it is an upper case character (less cases to cover)
		int ascii = (int)std::toupper(stringToRender[i], std::locale());

		// Convert our ascii value into the range of [0, 35] (0, 1, 2, ... , A, B, C, .... , Z)
		if (ascii > 57)
			ascii -= 7;
		ascii -= 48;

		// Get the row and column of the character in our sprite sheet. Then we will let our vertex shader calculate the proper UVs
		int spritesheetSize = 6;
		float charUVSize = 1.0f / spritesheetSize;
		int charRow = ascii / spritesheetSize;
		int charCol = ascii % spritesheetSize;

		// Before we draw, we need to setup the transformation matrix for the text
		glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(position.x + (position.z * i), position.y, 0.0f));
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(size, size, 1.0f));
		glm::mat4 transformationMatrix = translation * scale;

		// Setup uniforms
		textShader.setUniform1f("UVSize", charUVSize);
		textShader.setUniform1i("charCol", charCol);
		textShader.setUniform1i("charRow", charRow);
		textShader.setUniformMat4("transformationMatrix", transformationMatrix);
		textShader.setUniform3f("textColour", color);

		// Finally draw the character
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
	
}

// Main function that builds and runs the game
int main(void){
	try {
		// Seed for generating random numbers with rand()
		srand((unsigned int)time(0));

		// Setup window
		Window window(window_width_g, window_height_g, window_title_g);

		// Set up z-buffer for rendering
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		// Enable Alpha blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Create geometry of the square
		int size = CreateSquare();

		// Set up shaders
		Shader shader("shader.vert", "shader.frag");
		Shader textShader("textShader.vert", "textShader.frag");

		ParticleSystem particleSystem("particle.vert", "particle.frag");

		particleSystem.createParticleArray();

		// Set up the textures
		setallTexture();
		vector<GLuint> castleOneUnitTextures = { tex[2], tex[6], tex[8], tex[4] };
		vector<GLuint> castleTwoUnitTextures = { tex[3], tex[7], tex[9], tex[5] };

		vector<GLuint> projectileTextures = { tex[19], tex[17], tex[18], tex[24], tex[24], tex[24], tex[24] };

		vector<GLuint> castleOneTowerTextures = { tex[14], tex[10], tex[12], tex[24], tex[27], tex[25], tex[26] };
		vector<GLuint> castleTwoTowerTextures = { tex[15], tex[11], tex[13], tex[24], tex[27], tex[25], tex[26] };

		Graph* graph = new Graph(68, 5, GameObject(glm::vec3(0.0f), tex[7], size));

		vector<Castle*> castles = { new Castle(0,glm::vec3(6,0.5,0),glm::vec3(-2,2,2),tex[1],size,projectileTextures,castleTwoUnitTextures,castleTwoTowerTextures),
									new Castle(1,glm::vec3(-6,0.5,0),glm::vec3(2,2,2),tex[0],size,projectileTextures,castleOneUnitTextures,castleOneTowerTextures) };

		//initialize timers
		double lastTime = glfwGetTime();
		double pauseTimer = glfwGetTime();
		double toMainTimer = glfwGetTime();
		double pauseDelay = 0.3;
		double toMainDelay = 0.3;

		static bool playtoggle = false;
		static int startState = 0;

		//initialize game objects
		Camera* camera = new Camera(shader, window, glm::vec2(window_width_g, window_height_g));
		Board* board = new Board(camera, &particleSystem, graph, castles);

		GameObject pause = GameObject(glm::vec3(0.0f, 0.0f, 0.0f), tex[22], 200);
		GameObject startscreen(glm::vec3(0.0f, 0.0f, 0.0f), tex[23], 200);

		// Run the main loop
		while (!glfwWindowShouldClose(window.getWindow()))
		{
			// Clear background
			window.clear(viewport_background_color_g);
			glDepthMask(GL_TRUE);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Calculate delta time
			double currentTime = glfwGetTime();
			double deltaTime = currentTime - lastTime;
			lastTime = currentTime;

			// Select proper shader program to use
			shader.enable();
			shader.setAttributes();
			switch (startState) {
			case 0: //start screen
			{
				camera->update(0);
				renderText(std::string("Kingdom Seige"), textShader, glm::vec3(1.0), glm::vec3(-0.60f, 0.65f, 0.1f), 0.12f);
				shader.enable();

				glBindTexture(GL_TEXTURE_2D, tex[0]);
				shader.setUniformMat4("transformationMatrix", glm::translate(glm::mat4(1.0f), glm::vec3(0)) * glm::scale(glm::mat4(1.0f), glm::vec3(2)));
				glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);

				renderText(std::string("Press SPACE to Start"), textShader, glm::vec3(1.0), glm::vec3(-0.65f, -0.65f, 0.07f), 0.1);
				shader.enable();

				if (glfwGetKey(window.getWindow(), GLFW_KEY_SPACE) == GLFW_PRESS) {
					if ((glfwGetTime() - toMainTimer) > toMainDelay)
					{
						toMainTimer = glfwGetTime();
						startState = 1;
						lastTime = glfwGetTime();
						castles = { new Castle(0,glm::vec3(6,0.5,0),glm::vec3(-2,2,2),tex[1],size,projectileTextures,castleTwoUnitTextures,castleTwoTowerTextures),
									new Castle(1,glm::vec3(-6,0.5,0),glm::vec3(2,2,2),tex[0],size,projectileTextures,castleOneUnitTextures,castleOneTowerTextures) };
						board = new Board(camera, &particleSystem, graph, castles);
					}
				}
				break;
			}
			case 1: //main game
			{
				#pragma region GUI Rendering
				//health
				int c1Health = (board->getCastles().at(1)->getHealth());
				int c2Health = (board->getCastles().at(0)->getHealth());
				renderText(std::string("Castle 1 Health " + std::to_string(c1Health)), textShader, glm::vec3(1.0), glm::vec3(-0.95f, 0.95f, 0.03f), 0.06f);
				renderText(std::string("Castle 2 Health " + std::to_string(c2Health)), textShader, glm::vec3(1.0), glm::vec3(0.40f, 0.95f, 0.03f), 0.06f);

				//funds
				int c1Funds = (board->getCastles().at(1)->getFunds());
				int c2Funds = (board->getCastles().at(0)->getFunds());
				renderText(std::string("Castle 1 Funds " + std::to_string(c1Funds)), textShader, glm::vec3(1.0), glm::vec3(-0.95f, 0.90f, 0.03f), 0.06f);
				renderText(std::string("Castle 2 Funds " + std::to_string(c2Funds)), textShader, glm::vec3(1.0), glm::vec3(0.40f, 0.90f, 0.03f), 0.06f);
				shader.enable();

				if (castles.at(1)->getPowerup()) {
					glBindTexture(GL_TEXTURE_2D, tex[16]);
					shader.setUniformMat4("transformationMatrix", glm::translate(glm::mat4(1.0f), -camera->getPosition()) * glm::translate(glm::mat4(1.0f), glm::vec3(-0.7, 1.85, 0.0)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.12, 0.17, 1)));
					glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);
				}

				glBindTexture(GL_TEXTURE_2D, tex[2]);
				shader.setUniformMat4("transformationMatrix", glm::translate(glm::mat4(1.0f), -camera->getPosition()) * glm::translate(glm::mat4(1.0f), glm::vec3(-1.80, 1.6, 0.0)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.1, 0.15, 1)));
				glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);

				glBindTexture(GL_TEXTURE_2D, tex[6]);
				shader.setUniformMat4("transformationMatrix", glm::translate(glm::mat4(1.0f), -camera->getPosition()) * glm::translate(glm::mat4(1.0f), glm::vec3(-1.80, 1.4, 0.0)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.1, 0.15, 1)));
				glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);

				glBindTexture(GL_TEXTURE_2D, tex[8]);
				shader.setUniformMat4("transformationMatrix", glm::translate(glm::mat4(1.0f), -camera->getPosition()) * glm::translate(glm::mat4(1.0f), glm::vec3(-1.80, 1.2, 0.0)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.1, 0.15, 1)));
				glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);

				glBindTexture(GL_TEXTURE_2D, tex[4]);
				shader.setUniformMat4("transformationMatrix", glm::translate(glm::mat4(1.0f), -camera->getPosition()) * glm::translate(glm::mat4(1.0f), glm::vec3(-1.80, 1.0, 0.0)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.1, 0.15, 1)));
				glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);

				glBindTexture(GL_TEXTURE_2D, tex[14]);
				shader.setUniformMat4("transformationMatrix", glm::translate(glm::mat4(1.0f), -camera->getPosition()) * glm::translate(glm::mat4(1.0f), glm::vec3(-1.90, -1.8, 0.0)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.1, 0.15, 1)));
				glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);

				glBindTexture(GL_TEXTURE_2D, tex[10]);
				shader.setUniformMat4("transformationMatrix", glm::translate(glm::mat4(1.0f), -camera->getPosition()) * glm::translate(glm::mat4(1.0f), glm::vec3(-1.90, -1.6, 0.0)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.1, 0.15, 1)));
				glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);

				glBindTexture(GL_TEXTURE_2D, tex[12]);
				shader.setUniformMat4("transformationMatrix", glm::translate(glm::mat4(1.0f), -camera->getPosition()) * glm::translate(glm::mat4(1.0f), glm::vec3(-1.90, -1.4, 0.0)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.1, 0.15, 1)));
				glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);

				renderText(std::string("1"), textShader, glm::vec3(1.0), glm::vec3(-0.95f, 0.80f, 0.03f), 0.06f);
				renderText(std::string("2"), textShader, glm::vec3(1.0), glm::vec3(-0.95f, 0.70f, 0.03f), 0.06f);
				renderText(std::string("3"), textShader, glm::vec3(1.0), glm::vec3(-0.95f, 0.60f, 0.03f), 0.06f);
				renderText(std::string("4"), textShader, glm::vec3(1.0), glm::vec3(-0.95f, 0.50f, 0.03f), 0.06f);

				renderText(std::string("25"), textShader, glm::vec3(1.0), glm::vec3(-0.85f, 0.80f, 0.03f), 0.06f);
				renderText(std::string("10"), textShader, glm::vec3(1.0), glm::vec3(-0.85f, 0.70f, 0.03f), 0.06f);
				renderText(std::string("100"), textShader, glm::vec3(1.0), glm::vec3(-0.85f, 0.60f, 0.03f), 0.06f);
				renderText(std::string("50"), textShader, glm::vec3(1.0), glm::vec3(-0.85f, 0.50f, 0.03f), 0.06f);

				renderText(std::string("150"), textShader, glm::vec3(1.0), glm::vec3(-0.9f, -0.90f, 0.03f), 0.06f);
				renderText(std::string("200"), textShader, glm::vec3(1.0), glm::vec3(-0.9f, -0.80f, 0.03f), 0.06f);
				renderText(std::string("250"), textShader, glm::vec3(1.0), glm::vec3(-0.9f, -0.70f, 0.03f), 0.06f);
				shader.enable();
				#pragma endregion

				// press esc to change pause toggle
				if ((glfwGetTime() - pauseTimer) > pauseDelay) {
					if (glfwGetKey(window.getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
					{
						playtoggle = !playtoggle;
						pauseTimer = glfwGetTime();
					}
				}

				// check pause toggle
				if (playtoggle)
				{
					camera->update(0);
					// Now render the text
					renderText(std::string("PAUSED"), textShader, glm::vec3(1.0), glm::vec3(-0.1f, 0.65f, 0.05f), 0.1f);
					shader.enable();
				}
				else
				{
					// Setup camera to focus on the player object (the first object in the gameObjects array) 
					camera->update(deltaTime);
					//game entity updating
					board->update(deltaTime);
				}

				//game entity rendering
				board->render(shader, particleSystem);

				//particle system set up//get ready to draw particles
				particleSystem.enable();
				particleSystem.setAttributes();
				particleSystem.setUniformMat4("viewMatrix", camera->getViewMatrix());

				//checks for defeated castle and changes state
				for (int i = 0; i < board->getCastles().size(); i++)
				{
					if (board->getCastles().at(0)->getHealth() <= 0)
					{
						startState = 3;
						toMainTimer = glfwGetTime();
					}
					else if (board->getCastles().at(1)->getHealth() <= 0)
					{
						startState = 2;
						toMainTimer = glfwGetTime();
					}
				}
				break;
			}
			case 2: //defeat screen
				camera->update(0);
				renderText(std::string("Kingdom Seige"), textShader, glm::vec3(1.0), glm::vec3(-0.60f, 0.65f, 0.1f), 0.12f);
				renderText(std::string("DEFEAT"), textShader, glm::vec3(1.0), glm::vec3(-0.22f, 0.45f, 0.1f), 0.12f);
				shader.enable();
				break;
			case 3: //victory screen
				camera->update(0);
				renderText(std::string("Kingdom Seige"), textShader, glm::vec3(1.0), glm::vec3(-0.60f, 0.65f, 0.1f), 0.12f);
				renderText(std::string("VICTORY"), textShader, glm::vec3(1.0), glm::vec3(-0.3f, 0.45f, 0.1f), 0.12f);
				shader.enable(); 
				break;
			}

			// Update other events like input handling
			glfwPollEvents();

			// Push buffer drawn in the background onto the display
			glfwSwapBuffers(window.getWindow());
		}
	}
	catch (std::exception &e){
		// print exception and sleep so error can be read
		PrintException(e);
		std::this_thread::sleep_for(std::chrono::milliseconds(100000));
	}

	return 0;
}
