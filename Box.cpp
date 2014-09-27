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
#include "Box.h"

#include <string.h>

using namespace giselle::model;

static const float VERTEX_ARRAY_TEMPLATE[] =
{
	0, 1, 0,   0, 1, 1,   1, 1, 1,   1, 1, 0,	//top
	1, 0, 0,   1, 0, 1,   0, 0, 1,   0, 0, 0,	//bottom

	0, 1, 1,   0, 0, 1,   1, 0, 1,   1, 1, 1,	//front
	1, 1, 0,   1, 0, 0,   0, 0, 0,	 0, 1, 0,	//back

	0, 1, 0,   0, 0, 0,   0, 0, 1,   0, 1, 1,	//left
	1, 1, 1,   1, 0, 1,   1, 0, 0,   1, 1, 0	//right
};

static const float VERTEX_NORMAL_ARRAY[] =
{
	0, 1, 0,   0, 1, 0,   0, 1, 0,   0, 1, 0,	//top
	0,-1, 0,   0,-1, 0,   0,-1, 0,   0,-1, 0,	//bottom
	0, 0, 1,   0, 0, 1,   0, 0, 1,   0, 0, 1,	//front
	0, 0,-1,   0, 0,-1,   0, 0,-1,   0, 0,-1,	//back
	-1,0, 0,  -1, 0, 0,  -1, 0, 0,  -1, 0, 0,	//left
	1, 0, 0,   1, 0, 0,   1, 0, 0,   1, 0, 0	//right
};

static const unsigned int INDEX_ARRAY[] =
{
	0, 1, 2,   2, 3, 0,	//top
	4, 5, 6,   6, 7, 4,	//bottom

	 8,  9, 10,    8, 10, 11,	// front
	13, 14, 12,   14, 15, 12,	// back

	16, 17, 18,   18, 19, 16,	// left
	20, 21, 22,   22, 23, 20 	// right
};

Model giselle::model::Box(float x1, float x2, float y1, float y2, float z1, float z2)
{
	if (x2 <= x1 || y2 <= y1 || z2 <= z1)
		return Model();

	constexpr unsigned int nVertices = 24;
	constexpr unsigned int nTriangles = 12;
	float* vertex_array = new float[nVertices*3];
	float* vertex_normal_array = new float[nVertices*3];
	unsigned int* index_array = new unsigned int[nTriangles*3];

	memcpy(vertex_array, VERTEX_ARRAY_TEMPLATE, nVertices*3*sizeof(float));

	for (auto i = 0u ; i < nVertices*3 ; i+=3)
	{
		vertex_array[i]   = (vertex_array[i]   >= 1.0f) ? x2 : x1;
		vertex_array[i+1] = (vertex_array[i+1] >= 1.0f) ? y2 : y1;
		vertex_array[i+2] = (vertex_array[i+2] >= 1.0f) ? z2 : z1;
	}

	memcpy(vertex_normal_array, VERTEX_NORMAL_ARRAY, nVertices*3*sizeof(float));
	memcpy(index_array, INDEX_ARRAY, nTriangles*3*sizeof(unsigned int));

	Model m(nVertices, nTriangles, vertex_array, vertex_normal_array, index_array);

	delete[] vertex_array;
	delete[] vertex_normal_array;
	delete[] index_array;
	return m;
}
