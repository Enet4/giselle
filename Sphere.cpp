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
#include "Sphere.h"

#include <math.h>
#include "MathUtils.h"

#ifdef _GISELLE_DEBUG
#include <iostream>
#define Sphere_D(x) std::cout << x
#else
#define Sphere_D(x)
#endif

using namespace giselle;
using namespace model;
using namespace math;

Model model::Sphere(float radius, int lat, int lon)
{
	if (radius <= 0 || lat < 1 || lon < 3)
		return Model();

	unsigned int nVertices = 2 + lat * lon;
	unsigned int nTriangles = 2 * lat * lon;

	float* vertex_array = new float[nVertices*3];
	float* vertex_normal_array = new float[nVertices*3];
	unsigned int* index_array = new unsigned int[nTriangles*3];

	int i = 0;

	Sphere_D( "SPHERE: " << nVertices << " vertices | " << nTriangles << " triangles"
				<< std::endl );

	// build vertex 0 : top of sphere
	vertex_array[i] = 0.0f;
	vertex_normal_array[i++] = 0.0f;
	vertex_array[i] = radius;
	vertex_normal_array[i++] = 1.0f;
	vertex_array[i] = 0.0f;
	vertex_normal_array[i++] = 0.0f;

	// build rings of vertices [1 ; nVertices-1]
	// each ring has (lon) vertices

	for (int row = 0 ; row < lat ; row++)
	{
		float beta = PI/2 - (row+1) * (PI/(lat+1));
		float y = radius * sin(beta);
		float r = radius * cos(beta);
		for (int col = 0 ; col < lon ; col++)
		{
			float alpha = col * 2 * PI / lon;
			float cos_alpha = cos(alpha);
			float sin_alpha = sin(alpha);
			Vector4f v = {r*cos_alpha, y, r * sin_alpha, 0};
			vertex_array[i] = v.x();
			vertex_array[i+1] = v.y();
			vertex_array[i+2] = v.z();
			v *= (1/v.length());
			vertex_normal_array[i++] = v.x();
			vertex_normal_array[i++] = v.y();
			vertex_normal_array[i++] = v.z();
		}
	}

	// build last vertex : bottom of sphere
	vertex_array[i] = 0.0f;
	vertex_normal_array[i++] = 0.0f;
	vertex_array[i] = -radius;
	vertex_normal_array[i++] = -1.0f;
	vertex_array[i] = 0.0f;
	vertex_normal_array[i++] = 0.0f;

	Sphere_D( "SPHERE: " << i/3 << " vertices built" << std::endl);

	// build triangles
	i = 0;

	// build top fan
	for (int col = 1 ; col <= lon ; col++)
	{
		index_array[i++] = (col==lon) ? 1 : col+1;
		index_array[i++] = col;
		index_array[i++] = 0;
	}

	// build rings
	for (int row = 0 ; row < lat-1 ; row++)
	{
		unsigned int base = 1 + row*lon;
		for (int col = 0 ; col < lon-1 ; col++)
		{
			// 2 triangles
			index_array[i++] = base + lon + col;
			index_array[i++] = base + col;
			index_array[i++] = base + col + 1;

			index_array[i++] = base + lon + col;
			index_array[i++] = base + col + 1;
			index_array[i++] = base + lon + col + 1;
		}
		// last 2 triangles
		index_array[i++] = base + lon + lon - 1;
		index_array[i++] = base + lon - 1;
		index_array[i++] = base;

		index_array[i++] = base + lon + lon - 1;
		index_array[i++] = base;
		index_array[i++] = base + lon;
	}

	// build bottom fan

	const unsigned int bottom_base = 1 + (lat-1)*lon;
	for (int col = 0 ; col < lon ; col++)
	{
		index_array[i++] = bottom_base + ((col==lon-1) ? 0 : col+1);
		index_array[i++] = nVertices-1;
		index_array[i++] = bottom_base + col;
	}

	Sphere_D( "SPHERE: " << i/3 << " triangles built" << std::endl);

	// construct model
	Model m(nVertices, nTriangles, vertex_array, vertex_normal_array, index_array);

	delete[] vertex_array;
	delete[] vertex_normal_array;
	delete[] index_array;
	return m;
}
