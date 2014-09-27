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
 * \file Example2.cpp
 */

#include <iostream>
#include <Giselle.h>
#include <GL/freeglut.h>

using namespace std;
using namespace giselle;
using namespace scene;
using namespace model;

void display(void);
void keyboard( unsigned char key, int x, int y );

GContext* p_context = nullptr;
Light *p_light = nullptr;
SimpleModelEntity *p_plane = nullptr, *p_ball = nullptr, *p_ball2 = nullptr, *p_crate = nullptr;
Entity *p_pivot = nullptr;
Camera *p_camera = nullptr, *p_camera2 = nullptr;
Scene *p_scene = nullptr;

void build_scene(void)
{
	p_light = new Light({-5, 8, -5, 1}, {0, 0, 0}, {}, {0.8, 0.8, 0.8});

	p_plane = new SimpleModelEntity(
			model::Box(-10, 10, -0.5, 0, -10, 10),
			{0,0,0}, {0,0,0}
			);
	p_plane->getModel().setMaterial(
			Material({0.1,0.1,0.1}, {0.6,0.4,0.2}, {0.1,0.1,0.1}, 8)); // material

	p_ball = new SimpleModelEntity(
			model::Sphere(1.0f,8,12),
			{0,2,0}, {0,0,0}
			);
	p_ball->getModel().setMaterial(
			Material({0.2,0.2,0.2}, {0.6,0.6,0.6}, {0.6,0.6,0.6}, 100)); // material

	p_ball2 = new SimpleModelEntity(
			model::Sphere(0.25f,4,8),
			{0,0.75f,0}, {0,0,0}
			);

	p_crate = new SimpleModelEntity(
			model::Box(-0.5, 0.5, -0.5, 0.5, -0.5, 0.5),
			{-4,2,0}, {math::degrees2radians(30),0,0},
			{p_ball2});
	p_crate->getModel().setMaterial(
			Material({0.0,0.4,0.1}, {0.0,0.5,0.2}, {0.4,0.4,0.4}, 50)); // material

	p_pivot = new Entity({0,0,0}, {0,0,0}, {p_crate});

	p_camera = new Camera( {0,3,10}, {0, 0, 0} ); // camera @ (0,3,8)
	p_camera->perspective(60.0f, 1.f, 25.f);
	p_camera->setBackColor(0.5f, 0.5f, 0.7f);

	p_camera2 = new Camera( {-5,2,0}, {0,math::degrees2radians(90),0} ); // camera @ (0,2,-5)
	p_camera2->ortho(15.0f, 1.f, 25.f);
	p_camera2->setBackColor(0.5f, 0.5f, 0.5f);

	p_scene = new Scene({p_light, p_camera, p_camera2, p_plane, p_pivot, p_ball});
	p_scene->setLight(*p_light);
}

int main(int argc, char** argv)
{
	// Init glut
	glutInit( &argc, argv );

	// DOUBLE-BUFFERING + DEPTH-TESTING
	glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
	glutInitWindowSize( 640, 400 );
	glutInitWindowPosition( 100, 80 );

	glutSetOption( GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS );

	// Create window
	int windowHandle = glutCreateWindow( "Giselle Test Chamber" );

	if( windowHandle < 1 )
	{
		cerr << "Could not create a new rendering window." << endl;
		return 1;
	}

	/* Scene Building */
	build_scene();

	p_context = new GContext(0,0,640, 400, *p_scene);
	if (!(*p_context))
	{
		cerr << "Graphical Context Error: " << p_context->getErrorMsg() << endl;
		return 2;
	}
	p_context->setCamera(*p_camera, true);

	// Set rendering function
	glutDisplayFunc( display );
	// Set keyboard function
	glutKeyboardFunc( keyboard );

	//Start GLUT main loop
	glutMainLoop();

	return 0;
}

void display(void)
{
	p_context->use(); // use context
	p_context->render(); //render

	// swap glut buffers
	glutSwapBuffers();
}

void keyboard( unsigned char key, int x, int y )
{
	switch( key )
	{
	  case 'Q' :
	  case 'q' :
	  case 27  :

		delete p_light;
		delete p_plane;
		delete p_ball;
		delete p_ball2;
		delete p_crate;
		delete p_pivot;
		delete p_camera;
		delete p_camera2;
		delete p_scene;

		exit( EXIT_SUCCESS );
	}
	glutPostRedisplay();
}

