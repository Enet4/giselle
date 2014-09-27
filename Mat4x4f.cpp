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
#include "Mat4x4f.h"
#include <utility>

using namespace giselle::math;

const Mat4x4f Mat4x4f::IDENTITY =
{	1,0,0,0,
	0,1,0,0,
	0,0,1,0,
	0,0,0,1 };

Mat4x4f::Mat4x4f(void)
{
	for (int i = 0 ; i < 4*4 ; i++)
		this->m[i] = 0.0f;
}

Mat4x4f::Mat4x4f(const Mat4x4f& other)
{
	for (int i = 0 ; i < 4*4 ; i++)
		this->m[i] = other.m[i];
}

Mat4x4f::Mat4x4f(const float* p_m)
{
	for (int i = 0 ; i < 4*4 ; i++)
		this->m[i] = p_m[i];
}

Mat4x4f::Mat4x4f(const std::initializer_list<float> & list)
{
	int i;
	auto it = begin(list);
	for (i = 0 ; it != end(list) && i < 4*4 ; it++, i++ )
		m[i] = *it;
	for ( ; i < 4*4 ; i++)
		m[i] = 0.0f;
}

Mat4x4f::operator const float* (void) const
{
	return this->m;
}

Mat4x4f& Mat4x4f::operator+= (const Mat4x4f& other)
{
	for (int i = 0 ; i < 4*4 ; i++)
		this->m[i] += other.m[i];
	return *this;
}

const Mat4x4f& Mat4x4f::operator+ (const Mat4x4f& other) const
{
	Mat4x4f out(*this);
	return out+=other;
}

Mat4x4f& Mat4x4f::operator-= (const Mat4x4f& other)
{
	for (int i = 0 ; i < 4*4 ; i++)
		this->m[i] -= other.m[i];
	return *this;
}

const Mat4x4f& Mat4x4f::operator- (const Mat4x4f& other) const
{
	Mat4x4f out(*this);
	return out-=other;
}

Mat4x4f& Mat4x4f::operator*= (const Mat4x4f& other)
{
	unsigned int r, c;

	Mat4x4f m1(*this);

	for (r = 0; r < 4; r++)
		for (c = 0; c < 4; c++)
			this->m[c * 4 + r] =
				(m1.m[r +  0] * other.m[c * 4 + 0]) +
				(m1.m[r +  4] * other.m[c * 4 + 1]) +
				(m1.m[r +  8] * other.m[c * 4 + 2]) +
				(m1.m[r + 12] * other.m[c * 4 + 3]);

	return *this;
}

const Mat4x4f& Mat4x4f::operator* (const Mat4x4f& other) const
{
	Mat4x4f out(*this);
	return out *= other;
}

Mat4x4f& Mat4x4f::operator*= (float fscalar)
{
	for (int i = 0 ; i < 4*4 ; i++)
		this->m[i] *= fscalar;
	return *this;
}

Mat4x4f& Mat4x4f::transpose(void)
{
	std::swap(m[1], m[4]);
	std::swap(m[2], m[8]);
	std::swap(m[3], m[12]);
	std::swap(m[6], m[9]);
	std::swap(m[7], m[13]);
	std::swap(m[11], m[14]);
	return *this;
}

float Mat4x4f::get(unsigned int index) const
{
	if (index >= 4*4) return 0.0f;
	return this->m[index];
}

float Mat4x4f::get(unsigned int row, unsigned int col) const
{
	if (row >= 4 || col >= 4) return 0.0f;
	return this->m[row + (col << 2)];
}

Vector4f& Mat4x4f::takeVector(Vector4f& vector) const
{
	vector.x() = m[12]; vector.y() = m[13];
	vector.z() = m[14]; vector.w() = m[15];
	return vector;
}
