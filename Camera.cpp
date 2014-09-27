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
#include "Camera.h"

#include "MathUtils.h"
#include <cmath>

using namespace giselle;
using namespace math;
using namespace scene;

Camera::Camera(const Vector4f& pos, const Vector4f& ang,
				const std::list<Entity*>& children)
:	Entity(pos, ang, children)
,	p(false)
,	fovy(DEFAULT_FOVY)
,	view_height(DEFAULT_VIEW_HEIGHT)
,	ratio(DEFAULT_RATIO)
,	near(DEFAULT_NEAR)
,	far(DEFAULT_FAR)
{
	calc_proj();
}

Camera::~Camera()
{
}

Camera::Camera(const Camera& other)
:	Entity(other)
,	p(other.p)
,	fovy(other.fovy)
,	view_height(DEFAULT_VIEW_HEIGHT)
, 	ratio(other.ratio)
, 	near(other.near)
, 	far(other.far)
{
	calc_proj();
}

bool Camera::isPerspective(void) const
{
	return this->p;
}

const Mat4x4f& Camera::getProjectionMatrix(void) const
{
	return this->proj;
}

bool Camera::ortho(float view_height, float near, float far, float aspect_ratio)
{
	if (near <= 0.0f || far <= 0.f || near >= far
		 || view_height == 0.f || aspect_ratio <= 0.f)
		return false;

	this->near = near;
	this->far = far;
	this->view_height = view_height;
	this->ratio = aspect_ratio;
	this->p = false;

	calc_proj();
	return true;
}

bool Camera::ortho(void)
{
	this->p = false;
	calc_proj();
	return true;
}

bool Camera::perspective(float fovy, float near, float far, float aspect_ratio)
{
	if (near <= 0.f || far <= 0.f || near >= far
		 || fovy <= 0.f || aspect_ratio <= 0.f)
		return false;

	this->near = near;
	this->far = far;
	this->fovy = fovy;
	this->ratio = aspect_ratio;
	this->p = true;

	calc_proj();
	return true;
}

bool Camera::perspective(void)
{
	this->p = true;
	calc_proj();
	return true;
}

bool Camera::setRange(float near, float far)
{
	if (near <= 0.0f || far <= 0.0f || near >= far)
		return false;

	this->near = near;
	this->far = far;
	calc_proj();
	return true;
}

bool Camera::setAspectRatio(float w, float h)
{
	if (w <= 0.0f || h <= 0.0f)
		return false;
	this->ratio = w/h;
	calc_proj();
	return true;
}

bool Camera::setAspectRatio(float ratio)
{
	if (ratio <= 0.0f) return false;
	this->ratio = ratio;
	calc_proj();
	return true;
}

bool Camera::setFOVy(float fovy)
{
	if (fovy < 0.0f) return false;
	this->fovy = fovy;
	if (this->p) calc_proj();
	return true;
}

bool Camera::setHeight(float view_height)
{
	if (view_height == 0.0f) return false;
	this->view_height = view_height;
	if (!this->p) calc_proj();
	return true;
}

void Camera::setBackColor(float r, float g, float b, float a)
{
	if (r < 0) r = 0;
	else if (r > 1) r = 1;
	if (g < 0) g = 0;
	else if (g > 1) g = 1;
	if (b < 0) b = 0;
	else if (b > 1) b = 1;
	if (a < 0) a = 0;
	else if (a > 1) a = 1;

	this->back_color = Vector4f(r, g, b, a);
}

void Camera::setBackColor(	unsigned char r, unsigned char g,
					unsigned char b, unsigned char a)
{
	this->back_color = Vector4f(r/255.0, g/255.0, b/255.0, a/255.0);
}

void Camera::getBackColor( float& r, float& g, float& b) const
{
	r = this->back_color.x();
	g = this->back_color.y();
	b = this->back_color.z();
}

void Camera::calc_proj(void)
{
	if (!this->p)
	{ // FIXME
		const float view_width = abs(this->view_height) * this->ratio;
		const float sx = 2 / view_width;
		const float sy = 2 / view_height;
		const float sz = -2 / (far - near);
		const float tz = - (far + near) / (far - near);

		this->proj = {
			sx, 0, 0,  0,
			0, sy, 0,  0,
			0, 0, sz,  0,
			0, 0, tz,  1 };
	}
	else
	{
		const float ang = math::degrees2radians(this->fovy * 0.5f);
		const float y = 1.0f / tan(ang);
		const float x = y / this->ratio;
		const float f_len = this->far - this->near;
		const float l = -(this->far + this->near) / f_len;
		const float z = -2.0f * this->near * this->far / f_len;

		this->proj = {
			x, 0, 0, 0,
			0, y, 0, 0,
			0, 0, l,-1,
			0, 0, z, 0 };
	}
}
