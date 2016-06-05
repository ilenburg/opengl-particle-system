#include "Physics.h"
#include "Calc.h"
#include <SDL.h>
#include <algorithm>

Physics::Physics()
{
	gravity.x = 0;
	gravity.y = 9;
	gravity.z = 0;
	friction = 0.9f;
}

void Physics::init()
{
	int thisTime = SDL_GetTicks();
	deltaTime = (float)(thisTime - lastTime) / 1000;
	lastTime = thisTime;
}

void Physics::update()
{
	int thisTime = SDL_GetTicks();
	deltaTime = (float)(thisTime - lastTime) / 1000;
	lastTime = thisTime;

	objects->update();

	for (std::vector<Particle>::iterator i = objects->particles.begin(); i != objects->particles.end();)
	{
		i->pos3D = Calc::Euler(i->pos3D, i->vel3D, i->acc3D + gravity, deltaTime);
		i->vel3D = Calc::Vel(i->vel3D, i->acc3D + gravity, deltaTime);
		i->life += deltaTime;
		if (i->life >= 1.5f) i = objects->particles.erase(i);
		else ++i;
	}

	for (int i = 0; i < deltaTime*3000; ++i) objects->particles.push_back(Particle());
	std::sort(objects->particles.begin(), objects->particles.end(), Particle::part_sort);
}