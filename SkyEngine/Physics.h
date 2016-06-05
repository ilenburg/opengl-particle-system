#pragma once

#include "Resource.h"

class Physics
{
public:
	Physics();
	void update();
	void init();

	Resource *objects;
	glm::vec3 gravity;
	int lastTime;
	float deltaTime;
	float friction;
	float inv_count;
};