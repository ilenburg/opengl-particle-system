#include "Renderer.h"

Renderer::Renderer()
{
	numFrames = 0;
	lastTime = SDL_GetTicks();
}

void Renderer::update()
{
	glClear(GL_COLOR_BUFFER_BIT);
	draw_particles();
	draw(objects->pointer);
	SDL_GL_SwapWindow(view.window);
	get_fps();
}

void Renderer::draw(Entity ent)
{
	glBindVertexArray(ent.vao);
	glBindTexture(GL_TEXTURE_2D, ent.texture);
	glUniformMatrix4fv(view.shaderModelMat, 1, GL_FALSE,(float*)&ent.modelMatrix);
	if (ent.fixed) glUniformMatrix4fv(view.shaderProjMat, 1, GL_FALSE, (float*)&view.ortho);
	else glUniformMatrix4fv(view.shaderProjMat, 1, GL_FALSE, (float*)&view.perspect);
	glUniform1f(view.pFixed, ent.fixed);
	glUniform1f(view.colourVar, 0);
	glDrawArrays(GL_TRIANGLE_STRIP,0,4);
	glUniformMatrix4fv(view.shaderModelMat, 1, GL_FALSE, (float*)&glm::mat4());
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::draw_particles()
{
	glUniform1f(view.pFixed, false);

	glBindVertexArray(objects->particle_vao);
	glBindTexture(GL_TEXTURE_2D, objects->parTex);
	glUniformMatrix4fv(view.shaderProjMat, 1, GL_FALSE, (float*)&view.perspect);
	for (std::vector<Particle>::iterator i = objects->particles.begin(); i != objects->particles.end(); ++i)
	{
		glUniformMatrix4fv(view.shaderModelMat, 1, GL_FALSE, (float*)&i->modelMatrix);
		glUniform1f(view.colourVar, (float)i->life / 1.5f);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::get_fps()
{
	++numFrames;
	if ((SDL_GetTicks() - lastTime) >= 1000)
	{
		std::stringstream name;
		lastTime = SDL_GetTicks();
		name << "SkyEngine - FPS: " << numFrames;
		SDL_SetWindowTitle(view.window, name.str().c_str());
		numFrames = 0;
	}
}