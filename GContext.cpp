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
#include "GContext.h"

#include "MathUtils.h"
#include <stack>

using namespace giselle;
using namespace scene;
using namespace model;
using namespace math;

const char* const GContext::ERROR_MSGS[4] =
{
	"OK",
	"Invalid Arguments",
	"GLEW Initialization Error",
	"Shader Loading Error"
};

bool GContext::Glew_Init = false;

GContext::GContext(void)
:	error(GContext::VAL_ERROR)
,	x(0)
,	y(0)
,	w(0)
,	h(0)
,	p_scene(nullptr)
,	p_camera(nullptr)
{
}

GContext::GContext(int x, int y, int width, int height, scene::Scene& scene)
:	error(GContext::OK)
,	x(x)
,	y(y)
,	w(width)
,	h(height)
,	p_scene(&scene)
,	p_camera(nullptr)
,	renderer()
{
	if (x < 0 || y < 0 || width <= 0 || height <= 0)
		error = GContext::VAL_ERROR;
	else
		init();
}

GContext::GContext(int width, int height, Scene& scene)
:	error(GContext::OK)
,	x(0)
,	y(0)
,	w(width)
,	h(height)
,	p_scene(&scene)
,	p_camera(nullptr)
{
	if (width <= 0 || height <= 0)
		error = GContext::VAL_ERROR;
	else
		init();
}

GContext::GContext(GContext&& other)
:	error(other.error)
,	x(other.x)
,	y(other.y)
,	w(other.w)
,	h(other.h)
,	p_scene(other.p_scene)
,	p_camera(other.p_camera)
{
	this->renderer = std::move(other.renderer);
	other.x = other.y = 0;
	other.w = other.h = 0;
	other.p_scene = nullptr;
	other.p_camera = nullptr;
	other.error = GContext::VAL_ERROR;
}

GContext::~GContext(void)
{
}

void GContext::init(void)
{
	if (!Glew_Init)
	{
		int s = glewInit();
		if (s != GLEW_OK)
		{
			error = GContext::GLEW_ERROR;
			return;
		}
		Glew_Init = true;
	}

	// Default Polygon drawing mode
	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

	// Back-Face Culling ON by default
	glCullFace( GL_BACK );
	glFrontFace( GL_CCW );
	glEnable( GL_CULL_FACE );

	glDepthFunc(GL_LESS);
	glEnable( GL_DEPTH_TEST );

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable( GL_BLEND );

	if (!renderer.initShaders())
		error = GContext::SHADER_ERROR;
}

bool GContext::operator!(void) const
{
	return this->error != GContext::OK;
}

int GContext::getError(void) const
{
	return this->error;
}

const char* GContext::getErrorMsg(void) const
{
	return GContext::ERROR_MSGS[this->error];
}

void GContext::use(void) const
{
	if (this->error != GContext::OK) return;

	// Set Viewport
	glViewport(x,y,w,h);
	// Set camera back color
	float r,g,b;
	this->p_camera->getBackColor(r,g,b);
	glClearColor(r,g,b,1.0f);
}

void GContext::render(bool clear)
{
	if (this->error != GContext::OK) return;

	if (clear)
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	else
		glClear(GL_DEPTH_BUFFER_BIT);

	this->renderer.use();

	// pass projection matrix to renderer
	renderer.passProjection(this->p_camera->getProjectionMatrix());

	// get camera absolute position + orientation
	Vector4f cam_pos, cam_ang;
	this->p_camera->absoluteVectors(cam_pos, cam_ang);

	// camera transformations (view matrix)
	Mat4x4f mat = Mat4x4f::IDENTITY;
	math::rotate(mat, -cam_ang.x(), -cam_ang.y(), -cam_ang.z());
	math::translate(mat, -cam_pos.x(), -cam_pos.y(), -cam_pos.z());

	renderer.passViewMatrix(mat);

	// pass light position and color to renderer
	Vector4f light_pos, light_ang;
	if (this->p_scene->getLight().position().w() == 0.0)
		light_pos = p_scene->getLight().position();
	else
	{
		this->p_scene->getLight().absoluteVectors(light_pos, light_ang);
		//math::multiply(light_pos, mat); // apply view transformation
	}

	renderer.passLightProperties(light_pos, this->p_scene->getLight().getColor());

	mat = Mat4x4f::IDENTITY;
	this->render_entity_rec(&(this->p_scene->root()), mat); // recursive render

	glFlush();
}

void GContext::setCamera(scene::Camera& camera, bool fix_aspect_ratio)
{
	if (this->error != GContext::OK) return;

	this->p_camera = &camera;
	if (fix_aspect_ratio)
		camera.setAspectRatio(w,h);
}

void GContext::render_entity_rec(const Entity* p_ent, const Mat4x4f& mat)
{
	if (p_ent == nullptr) return;
	Mat4x4f n_mat = mat;

	math::translate(n_mat, p_ent->position());
	math::rotate(n_mat, p_ent->orientation());

	renderer.passModelMatrix(n_mat); // update model transformation attribute

	p_ent->render(renderer);

	for (auto child : p_ent->getChildren())
		render_entity_rec(child, n_mat);
}

// ----- STATIC FUNCTIONS ----

const unsigned char* GContext::getVersion(void)
{
	return glGetString( GL_VERSION );
}
