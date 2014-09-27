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
#include "Cylinder.h"

#include <math.h>
#include "MathUtils.h"

#ifdef _GISELLE_DEBUG
#include <iostream>
#define Cylinder_D(x) std::cout << x
#else
#define Cylinder_D(x)
#endif

using namespace giselle;
using namespace model;
using namespace math;

Model model::Cylinder(float radius, float height, int lon)
{
	if (radius <= 0 || height <= 0 || lon < 3)
		return Model();

	unsigned int nVertices = 4 * lon;
	unsigned int nTriangles = 4 * (lon-1);

	float* vertex_array = new float[nVertices*3];
	float* vertex_normal_array = new float[nVertices*3];
	unsigned int* index_array = new unsigned int[nTriangles*3];

	int i = 0;

	Cylinder_D( "CYLINDER(" << radius << "," << height << "," << lon << "): " <<
				nVertices << " vertices | " << nTriangles << " triangles" << std::endl );

	const float col_step = 2*PI / lon;
	Vector4f v = {0,1,0,0};

	// build vertices : bottom base ; ring around base ; ring around top, top base
	float alpha = 0;
	for (int col = 0 ; col < lon ; col++)
	{
		float cos_alpha = cos(alpha);
		float sin_alpha = sin(alpha);

		vertex_array[i] = vertex_array[i+3*lon]
				= vertex_array[i+6*lon] = vertex_array[i+9*lon]
				= radius * sin_alpha;
		vertex_normal_array[i] = vertex_normal_array[i+9*lon] = 0.0f;
		vertex_normal_array[i+3*lon] = vertex_normal_array[i+6*lon] = sin_alpha;
		i++;

		vertex_array[i] = vertex_array[i+3*lon] = 0;
		vertex_array[i+6*lon] = vertex_array[i+9*lon] = height;
		vertex_normal_array[i] = -1.0f;
		vertex_normal_array[i+3*lon] = vertex_normal_array[i+6*lon] = 0.0f;
		vertex_normal_array[i+9*lon] = 1.0f;
		i++;

		vertex_array[i] = vertex_array[i+3*lon]
				= vertex_array[i+6*lon] = vertex_array[i+9*lon]
				= radius * cos_alpha;
		vertex_normal_array[i] = vertex_normal_array[i+9*lon] = 0.0f;
		vertex_normal_array[i+3*lon] = vertex_normal_array[i+6*lon] = cos_alpha;
		i++;
		alpha += col_step;
	}

	// build triangles
	i = 0;

	// build bottom base fan
	for (int col = 1 ; col < lon-1 ; col++)
	{
		index_array[i++] = (col==lon) ? 1 : col+1;
		index_array[i++] = col;
		index_array[i++] = 0;
	}

	// build ring
	unsigned int ring_base = lon;
	for (int col = 0 ; col < lon-1 ; col++)
	{
		// 2 triangles
		index_array[i++] = ring_base + lon + col;
		index_array[i++] = ring_base + col;
		index_array[i++] = ring_base + col + 1;

		index_array[i++] = ring_base + lon + col;
		index_array[i++] = ring_base + col + 1;
		index_array[i++] = ring_base + lon + col + 1;
	}
	// last 2 triangles
	index_array[i++] = ring_base + lon + lon - 1;
	index_array[i++] = ring_base + lon - 1;
	index_array[i++] = ring_base;

	index_array[i++] = ring_base + lon + lon - 1;
	index_array[i++] = ring_base;
	index_array[i++] = ring_base + lon;

	// build top base fan
	const unsigned int top_base = nVertices - lon;
	for (int col = 1 ; col < lon-1 ; col++)
	{
		index_array[i++] = top_base;
		index_array[i++] = top_base + col;
		index_array[i++] = top_base + col+1;
	}

	Cylinder_D( "CYLINDER: " << i/3 << " triangles built" << std::endl);

	// construct model
	Model m(nVertices, nTriangles, vertex_array, vertex_normal_array, index_array);

	delete[] vertex_array;
	delete[] vertex_normal_array;
	delete[] index_array;
	return m;
}
