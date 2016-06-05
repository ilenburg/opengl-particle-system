#pragma once

#include "Cursor.h"
#include "Particle.h"
#include <vector>

class Resource
{
public:
	Resource();
	void init();
	void load_tex();
	void set_particle();
	void update();
	
	GLuint particle_vao;
	GLuint parTex;
	GLuint playerTex;
	GLuint poinTex;

	std::vector<Particle> particles;
	Cursor pointer;
	bool game_on;
};