#pragma once

#include "Entity.h"

class Character : public Entity
{
public:

	glm::vec3 pos3D;
	glm::vec3 vel3D;
	glm::vec3 acc3D;
	float radius;
	float mass;
};