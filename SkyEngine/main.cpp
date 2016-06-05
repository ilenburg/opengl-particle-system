#include "Renderer.h"
#include "Interface.h"
#include "Physics.h"

int main(int argc, char* args[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	Renderer scene;
	Interface input;
	Physics logic;
	Resource *init_obj;
	init_obj = new Resource;
	scene.objects = init_obj;
	input.objects = init_obj;
	logic.objects = init_obj;
	while(init_obj->game_on){
		scene.update();
		input.update();
		logic.update();
	}
	delete init_obj;
	SDL_Quit();

	return 0;
}