#include "Resource.h"
#include <SOIL.h>

Resource::Resource()
{
	game_on = true;
	load_tex();
	init();
}

void Resource::init()
{
	set_particle();
}

void texLoader(GLuint &tex, const char *name)
{
	int width;
	int height;
	int channels;

	unsigned char *texData = SOIL_load_image(name,&width,&height,&channels,0);

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);

	glTexImage2D(GL_TEXTURE_2D, 0, channels == 4 ? GL_RGBA8 : GL_RGB8, width, height, 0, channels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, texData);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Resource::set_particle()
{
	texLoader(parTex, "Data/Textures/fire.jpg");

	glm::vec3 pos[4] = {
		glm::vec3(0.0f, 0.0f, -50.0f),
		glm::vec3(0.0f, 1.0f, -50.0f),
		glm::vec3(1.0f, 0.0f, -50.0f),
		glm::vec3(1.0f, 1.0f, -50.0f)};

	glm::vec2 tex[4] = {
		glm::vec2(0, 1),
		glm::vec2(0, 0),
		glm::vec2(1, 1),
		glm::vec2(1, 0) };

	glm::vec4 colour[4] = {
		glm::vec4(1, 1, 0, 0.1f),
		glm::vec4(1, 1, 0, 0.1f),
		glm::vec4(1, 1, 0, 0.1f),
		glm::vec4(1, 1, 0, 0.1f) };

	GLuint posVBO;
	GLuint texVBO;
	GLuint colourVBO;

	glGenVertexArrays(1, &particle_vao);

	glBindVertexArray(particle_vao);

	glGenBuffers(1, &posVBO);
	glBindBuffer(GL_ARRAY_BUFFER, posVBO);

	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(glm::vec3), pos, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &colourVBO);
	glBindBuffer(GL_ARRAY_BUFFER, colourVBO);

	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(glm::vec4), colour, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &texVBO);
	glBindBuffer(GL_ARRAY_BUFFER, texVBO);

	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(glm::vec3), tex, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}

void Resource::load_tex()
{

	texLoader(playerTex, "Data/Textures/player.jpg");
	texLoader(poinTex, "Data/Textures/cursor.jpg");

	pointer.texture = poinTex;
}

void Resource::update()
{
	for (std::vector<Particle>::iterator i = particles.begin(); i != particles.end(); ++i) i->update();
}