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
#include "Renderer.h"

#include <GL/glew.h>
#include <GL/gl.h>

#include "MathUtils.h"

#ifdef _GISELLE_DEBUG
#include <iostream>
static int _err;
#define RENDERER_DEBUG(x) std::cout << x
#define RENDERER_ERROR_CHECK(x) \
	_err = glGetError(); \
	if (_err != GL_NO_ERROR) \
	{ std::cout << "GL Error @ " << x << " - " << _err << std::endl; }
#else
#define RENDERER_DEBUG(x)
#define RENDERER_ERROR_CHECK(x)
#endif

using namespace giselle;
using namespace math;
using namespace model;

Renderer::Renderer()
:	p_prg(nullptr)
{
}

Renderer::~Renderer()
{
	if (p_prg)
		delete p_prg;
}

Renderer::Renderer(Renderer&& other)
:	p_prg(other.p_prg)
{
	other.p_prg = nullptr;
}

Renderer& Renderer::operator=(Renderer&& other)
{
    if (this == &other) return *this;
    this->p_prg = other.p_prg;
	other.p_prg = nullptr;
	return *this;
}

bool Renderer::operator!(void) const
{
	return this->p_prg == nullptr;
}

int Renderer::getAttribute(const std::string& att_name) const
{
	if (this->p_prg == nullptr) return -1;

	return this->p_prg->getAttribute(att_name);
}

int Renderer::getUniform(const std::string& att_name) const
{
	if (this->p_prg == nullptr) return -1;

	return this->p_prg->getUniform(att_name);
}

bool Renderer::initShaders(void)
{
    try {
        this->p_prg = new ShaderProgram;
        return true;
    } catch (ShaderException& e) {
        RENDERER_ERROR_CHECK("initShaders()");
        p_prg = nullptr;
        return false;
    }
}

void Renderer::use(void)
{
	if (this->p_prg == nullptr) return;
	GLint program = this->p_prg->getProgram();
	glUseProgram(program);
	RENDERER_ERROR_CHECK("use()");
}

void Renderer::passLightProperties( const math::Vector4f& light_pos,
				const math::Vector4f& light_color)
{
	GLint att_light_pos = this->getUniform("light_pos");
	GLint att_light_color = this->getUniform("light_color");

	glUniform4fv(att_light_pos, 1, light_pos);
	RENDERER_ERROR_CHECK("passLightProperties():light_pos");

	glUniform3fv(att_light_color, 1, light_color);
	RENDERER_ERROR_CHECK("passLightProperties():light_color");
}

void Renderer::passProjection(const math::Mat4x4f& proj)
{
	GLint att_proj = this->getUniform("proj");
	glUniformMatrix4fv(att_proj, 1, false, proj);
	RENDERER_ERROR_CHECK("passProjection()");
}

void Renderer::passViewMatrix(const math::Mat4x4f& view)
{
	GLint att_view = this->getUniform("view");
	glUniformMatrix4fv(att_view, 1, false, view);
	RENDERER_ERROR_CHECK("passViewMatrix()");
}

void Renderer::passModelMatrix(const math::Mat4x4f& model)
{
	this->model = model;
	GLint att_model = this->getUniform("model");
	glUniformMatrix4fv(att_model, 1, false, model);
	RENDERER_ERROR_CHECK("passModelMatrix()");
}

void Renderer::passModelView(const math::Mat4x4f& modelView)
{
	GLint att_modelView = this->getUniform("modelView");
	glUniformMatrix4fv(att_modelView, 1, false, modelView);
	RENDERER_ERROR_CHECK("passModelView()");
}

void Renderer::passMaterial(const Material& mat)
{
	GLint att_amb = this->getUniform("ambient_prod");
	RENDERER_ERROR_CHECK("passMaterial():ambient_prod");

	GLint att_diff = this->getUniform("diffuse_prod");
	RENDERER_ERROR_CHECK("passMaterial():diffuse_prod");

	GLint att_spec = this->getUniform("specular_prod");
	RENDERER_ERROR_CHECK("passMaterial():specular_prod");

	GLint att_shininess = this->getUniform("shininess");
	RENDERER_ERROR_CHECK("passMaterial():shininess");

	glUniform4fv(att_amb,  1, mat.ambient());
	glUniform4fv(att_diff, 1, mat.diffuse());
	glUniform4fv(att_spec, 1, mat.specular());
	glUniform1f(att_shininess, mat.shininess());
}

void Renderer::render(const scene::Entity& ent)
{
	Mat4x4f m = this->model; // using a separate matrix

	math::translate(m, ent.position());
	math::rotate(m, ent.orientation());

	GLint att_model = this->getUniform("model");
	glUniformMatrix4fv(att_model, 1, false, m);

	ent.render(*this);
	RENDERER_ERROR_CHECK("render()");
}

void Renderer::drawModel(const Model& model )
{
	GLint attribute_coord3d = this->getAttribute("pos");
	GLint attribute_normals = this->getAttribute("vnorm");

	const float* vertex_arr = model.getVertexArray();
	const float* vertex_normal_arr = model.getVertexNormalArray();
	const unsigned int* index_arr = model.getIndexArray();

	glEnableVertexAttribArray( attribute_coord3d );
	glEnableVertexAttribArray( attribute_normals );
        glVertexAttribPointer( attribute_coord3d,
                          3,                 // number of elements per vertex
						  GL_FLOAT,          // the type of each element
                          GL_FALSE,          // take our values as-is
                          0,                 // no extra data between each position
                          vertex_arr );   // pointer to the array

	glVertexAttribPointer( attribute_normals,
                          3,               // number of elements per vertex
                          GL_FLOAT,        // the type of each element
                          GL_FALSE,        // take our values as-is
                          0,               // no extra data between each position
                          vertex_normal_arr );  // pointer to the array

	glDrawElements( GL_TRIANGLES, model.getNTriangles()*3, GL_UNSIGNED_INT, index_arr );

	glDisableVertexAttribArray( attribute_coord3d );
	glDisableVertexAttribArray( attribute_normals );

	RENDERER_ERROR_CHECK("drawModel()");
}

#ifdef _GISELLE_DEBUG
#undef RENDERER_ERROR_CHECK
#endif
