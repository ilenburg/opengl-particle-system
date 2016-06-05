#include "Interface.h"

Interface::Interface()
{
	SDL_ShowCursor(0);
}

void Interface::update()
{
	int x, y;
	int bias = 0;
	SDL_GetMouseState(&x,&y);
	y = -y+768;
	x +=bias;
	objects->pointer.update(x,y,bias);
	while (SDL_PollEvent(&input))
	{
		switch(input.type)
		{
			case SDL_KEYDOWN:
				if (input.key.keysym.sym == SDLK_q)
				{
					objects->game_on = false;
				}
				if (input.key.keysym.sym == SDLK_d || input.key.keysym.sym == SDLK_RIGHT)
				{
				}
				if (input.key.keysym.sym == SDLK_w || input.key.keysym.sym == SDLK_UP)
				{
				}
				if (input.key.keysym.sym == SDLK_s || input.key.keysym.sym == SDLK_DOWN)
				{
				}
				if (input.key.keysym.sym == SDLK_a || input.key.keysym.sym == SDLK_LEFT)
				{
				}
				break;
			case SDL_KEYUP:
				if (input.key.keysym.sym == SDLK_d || input.key.keysym.sym == SDLK_RIGHT)
				{
				}
				if (input.key.keysym.sym == SDLK_a || input.key.keysym.sym == SDLK_LEFT)
				{
				}
				if (input.key.keysym.sym == SDLK_w || input.key.keysym.sym == SDLK_UP)
				{
				}
				if (input.key.keysym.sym == SDLK_s || input.key.keysym.sym == SDLK_DOWN)
				{
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (input.button.button == SDL_BUTTON_LEFT)
				{
				}
				break;
			case SDL_MOUSEBUTTONUP:
				if (input.button.button == SDL_BUTTON_LEFT)
				{
				}
				break;
			default:
				break;
		}
	}
}

