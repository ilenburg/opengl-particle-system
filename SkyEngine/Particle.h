#pragma once

#include <gl\glew.h>
#include <glm\gtc\matrix_transform.hpp>

class Particle
{
public:
	Particle();
	Particle(float nx, float ny, float nz);
	void update();
	static bool part_sort(Particle f1, Particle f2);

	float life;
	glm::vec3 pos3D;
	glm::vec3 vel3D;
	glm::vec3 acc3D;
	glm::mat4 modelMatrix;
};