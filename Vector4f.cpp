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
#include "Vector4f.h"

#include <math.h>

using namespace giselle;
using namespace math;

Vector4f::Vector4f(const std::initializer_list<float> & list)
{
	int i;
	auto it = begin(list);
	for (i = 0 ; it != end(list) && i < 4 ; it++, i++ )
		v[i] = *it;
	for ( ; i < 3 ; i++)
		v[i] = 0.0f;
	if (i == 3) v[3] = 1.0f; //default w coordinate
}

Vector4f::Vector4f(const float* p_v)
: v{p_v[0], p_v[1], p_v[2], p_v[3]}
{
}

Vector4f::Vector4f(float x, float y, float z, float w)
: v{x,y,z,w}
{
}

Vector4f::~Vector4f(void)
{
}

Vector4f::operator const float* (void) const
{
	return this->v;
}

float Vector4f::lengthSqr(void) const
{
	return v[0]*v[0]+v[1]*v[1]+v[2]*v[2];
}

float Vector4f::length(void) const
{
	return sqrt(lengthSqr());
}

Vector4f& Vector4f::operator*=(const Vector4f& other)
{
	for (int i = 0 ; i < 4 ; i++)
		this->v[i] *= other.v[i];
	return *this;
}

float Vector4f::dot(const Vector4f& other) const
{
	return
		this->x() * other.x() + this->y() * other.y() +
		this->z() * other.z() + this->w() * other.w();
}

Vector4f& Vector4f::operator+=(const Vector4f& other)
{
	for (int i = 0 ; i < 4 ; i++)
		this->v[i] += other.v[i];
	return *this;
}

const Vector4f& Vector4f::operator+(const Vector4f& other) const
{
	Vector4f vec(*this);
	return vec += other;
}

Vector4f& Vector4f::operator-=(const Vector4f& other)
{
	for (int i = 0 ; i < 4 ; i++)
		this->v[i] -= other.v[i];
	return *this;
}

const Vector4f& Vector4f::operator-(const Vector4f& other) const
{
	Vector4f vec(*this);
	return vec -= other;
}

Vector4f& Vector4f::operator*=(float fscalar)
{
	for (int i = 0 ; i < 4 ; i++)
		this->v[i] *= fscalar;
	return *this;
}

Vector4f& Vector4f::normalize(void)
{
	float w = this->w();
	this->v[0] /= w;
	this->v[1] /= w;
	this->v[2] /= w;
	this->v[3] = 1.f;
	return *this;
}

Vector4f& Vector4f::clamp(void)
{
	for (int i = 0 ; i < 4 ; i++)
	{
		if (v[i] < 0) v[i] = 0;
		if (v[i] > 1) v[i] = 1;
	}
	return *this;
}

float& Vector4f::x(void) { return this->v[0]; }
float Vector4f::x(void) const { return this->v[0]; }

float& Vector4f::y(void) { return this->v[1]; }
float Vector4f::y(void) const { return this->v[1]; }

float& Vector4f::z(void) { return this->v[2]; }
float Vector4f::z(void) const { return this->v[2]; }

float& Vector4f::w(void) { return this->v[3]; }
float Vector4f::w(void) const { return this->v[3]; }


