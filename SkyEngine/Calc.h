#pragma once

#include "Character.h"

class Calc
{
public:
	static glm::vec3 Vel(glm::vec3 u, glm::vec3 a, float t);
	static glm::vec3 Euler(glm::vec3 s, glm::vec3 u, glm::vec3 a, float t);
};