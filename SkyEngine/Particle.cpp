#include "Particle.h"
#include <iostream>

using namespace std;

float f_rand(){
	return (rand() % 2000 - 1000) / 100.0f;
}

Particle::Particle()
{
	life = 0;
	pos3D = glm::vec3(0, -15, 0);
	glm::vec3 nV(f_rand(), f_rand(), f_rand());
	//cout << glm::length(nV) << endl;
	while (glm::length(nV) > 10) nV = glm::vec3(f_rand(), f_rand(), f_rand());
	vel3D = nV;
	acc3D = glm::vec3(-1 * nV.x, 0, -1 * nV.z);
	modelMatrix = glm::translate(glm::mat4(), glm::vec3(pos3D.x, pos3D.y, pos3D.z));
}

Particle::Particle(float nx, float ny, float nz)
{
	life = 0;
	pos3D = glm::vec3(nx, ny, nz);
	vel3D = glm::vec3(-50, 50, 50);
	acc3D = glm::vec3(0, 0, 0);
	modelMatrix = glm::translate(glm::mat4(), glm::vec3(pos3D.x, pos3D.y, pos3D.z));
}

void Particle::update()
{
	modelMatrix = glm::translate(glm::mat4(), glm::vec3(pos3D.x, pos3D.y, pos3D.z));
}

bool Particle::part_sort(Particle f1, Particle f2)
{
	return f1.pos3D.z < f2.pos3D.z;
}