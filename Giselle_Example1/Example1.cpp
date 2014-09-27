/*
 * Copyright (C) 2014 Eduardo Pinho (enet4mikeenet AT gmail.com)
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software
 * without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to
 * whom the Software is furnished to do so, subject to the
 * following conditions:
 *
 * The above copyright notice and this permission notice shall
 * be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY
 * KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
 /**
 * \file Example1.cpp
 */

#include <SDL.h>
#include <iostream>
#include <Giselle.h>

using namespace std;
using namespace giselle;
using namespace scene;  // giselle::scene
using namespace model;  // giselle::model
using namespace math;   // giselle::math

constexpr unsigned int FRAMES_PER_SECOND = 30;

int main(int argc, char** argv)
{
	// Init SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        cerr << "Failed to init SDL" << endl;
		return 1;
    }

	// Set SDL video mode (using OpenGL)
	if(SDL_SetVideoMode(640, 400, 32, SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL) == NULL){
        cerr << "Failed to set video mode" << endl;
		return 1;
    }
	SDL_WM_SetCaption( "Giselle Example 1", NULL );

	/* Scene Building */
	Light light({0, 6, 0}, {0, 0, 0}, {}, {0.8, 0.8, 0.8}); // light @ (0,8,0)

	SimpleModelEntity plane(
			model::Box(-10, 10, -0.5, 0, -10, 10),
			{0,0,0}, {0,0,0}
			);
	SimpleModelEntity ball(
			model::Sphere(1.0f,8,12),
			{0,2,0}, {0,0,0}
			);

	SimpleModelEntity ball2(
			model::Sphere(0.25f,4,8),
			{0,0.75f,0}, {0,0,0}
			);

	SimpleModelEntity crate(
			model::Box(-0.5, 0.5, -0.5, 0.5, -0.5, 0.5),
			{-4,2,0}, {degrees2radians(30),0,0},
			{&ball2});

	Camera camera( {0,3,10}, {0, 0, 0} ); // camera @ (0,3,10)
	camera.perspective(60.0f, 1.f, 25.f);
	camera.setBackColor(0.2f, 0.6f, 0.8f); // blueish background

	Entity pivot({0,0,0}, {0,0,0}, {&crate});
	Entity pivot2({0,0,0}, {0,0,0}, {&camera});

	Scene scene({&pivot, &pivot2, &light, &plane, &ball});
	scene.setLight(light); // set the light of the scene

	GContext context(640, 400, scene); // create a new graphical context

	if (!context)
	{
		cerr << "Graphical Context Error: " << context.getErrorMsg() << endl;
		return 2;
	}

	context.setCamera(camera, true); // set camera & fix aspect ratio

	context.use(); // always use this context

	bool running = true;
	do
	{
		//Event Handling (SDL)
		SDL_Event event;
		while( SDL_PollEvent( &event ) )
		{
			if( event.type == SDL_QUIT )
			{
				running = false;
			}
			else if( event.type == SDL_KEYDOWN )
			{
				switch(event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
					case SDLK_q:
						running = false; break;

					case SDLK_w:
						camera.rotate(degrees2radians(5), 0, 0);
						break;

					case SDLK_s:
						camera.rotate(degrees2radians(-5), 0, 0);
						break;

					default:
					break;
				}
			}
		}

		//Update scene status

		pivot.rotate(0, degrees2radians(1.0f), 0);
		pivot2.rotate(0, degrees2radians(-0.8f), 0);

		//Render (using Giselle)
		context.render();

		//swap SDL buffers
		SDL_GL_SwapBuffers();

		//Sleep for a bit (SDL)
		SDL_Delay(1000/FRAMES_PER_SECOND);
	}
	while(running);

	return 0;
}

