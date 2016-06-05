#include "Calc.h"

glm::vec3 Calc::Vel(glm::vec3 u, glm::vec3 a, float t)
{
	return (u + a*t);
}

glm::vec3 Calc::Euler(glm::vec3 s, glm::vec3 u, glm::vec3 a, float t)
{
	glm::vec3 v1 = Vel(u, a, t);
	glm::vec3 c1 = Vel(s, v1, t);
	return c1;
}