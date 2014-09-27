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
#include "Model.h"

#include <GL/glew.h>
#include <GL/gl.h>
#include <cstring>

using namespace giselle;
using namespace giselle::model;

Model::Model()
:	nVertices(0)
,	nTriangles(0)
,	vertex_arr(nullptr)
,	vertex_normal_arr(nullptr)
,	index_arr(nullptr)
{}

Model::Model( unsigned int nVertices, unsigned int nTriangles, float* vertex_array,
		float* vertex_normal_array, unsigned int* index_array, const Material& material)
:	nVertices(0)
,	nTriangles(0)
,	vertex_arr(nullptr)
,	vertex_normal_arr(nullptr)
,	index_arr(nullptr)
,	material(material)
{
	if ((vertex_array != nullptr
		&& vertex_normal_array != nullptr
		&& index_array != nullptr) && nVertices >= 3 && nTriangles >= 1)
	{
		this->nVertices = nVertices;
		this->nTriangles = nTriangles;

		this->vertex_arr = new float[this->nVertices*3];
		memcpy(this->vertex_arr, vertex_array, this->nVertices*3*sizeof(float));

		this->vertex_normal_arr = new float[this->nVertices*3];
		memcpy(this->vertex_normal_arr, vertex_normal_array, this->nVertices*3*sizeof(float));

		this->index_arr = new unsigned int[this->nTriangles*3];
		memcpy(this->index_arr, index_array, this->nTriangles*3*sizeof(unsigned int));
	}
}

Model::~Model()
{
	if (this->vertex_arr != nullptr)
	{ delete[] this->vertex_arr; this->vertex_arr = nullptr; }

	if (this->vertex_normal_arr != nullptr)
	{ delete[] this->vertex_normal_arr; this->vertex_normal_arr = nullptr; }

	if (this->index_arr != nullptr)
	{ delete[] this->index_arr; this->index_arr = nullptr; }
}

Model::Model(const Model& other)
:	nVertices(other.nVertices)
,	nTriangles(other.nTriangles)
,	vertex_arr(nullptr)
,	vertex_normal_arr(nullptr)
,	index_arr(nullptr)
,	material(other.material)
{
	if (other.vertex_arr != nullptr)
	{
		this->vertex_arr = new float[nVertices*3];
		memcpy(this->vertex_arr,
				other.vertex_arr, nVertices*3*sizeof(float));
	}

	if (other.vertex_normal_arr != nullptr)
	{
		this->vertex_normal_arr = new float[nVertices*3];
		memcpy(this->vertex_normal_arr,
				other.vertex_normal_arr, nVertices*3*sizeof(float));
	}

	if (other.index_arr != nullptr)
	{
		this->index_arr = new unsigned int[nTriangles*3];
		memcpy(this->index_arr,
				other.index_arr, nTriangles*3*sizeof(unsigned int));
	}
}

Model::Model(Model&& other)
:	nVertices(other.nVertices)
,	nTriangles(other.nTriangles)
,	vertex_arr(other.vertex_arr)
,	vertex_normal_arr(other.vertex_normal_arr)
,	index_arr(other.index_arr)
,	material(other.material)
{
	other.vertex_arr = other.vertex_normal_arr = nullptr;
	other.index_arr = nullptr;
}

unsigned int Model::getNVertices(void) const
{ return this->nVertices; }

unsigned int Model::getNTriangles(void) const
{ return this->nTriangles; }

const float* Model::getVertexArray(void) const
{ return this->vertex_arr; }

const float* Model::getVertexNormalArray(void) const
{ return this->vertex_normal_arr; }

const unsigned int* Model::getIndexArray(void) const
{ return this->index_arr; }

bool Model::isConsistent(void) const
{
	if (this->vertex_arr == nullptr ||
		this->vertex_normal_arr == nullptr ||
		this->index_arr == nullptr)
		return false;

	for (unsigned int i = 0 ; i < this->nTriangles*3 ; i++)
		if (this->index_arr[i] >= nVertices) return false;

	return true;
}

const Material& Model::getMaterial(void) const
{
	return this->material;
}

void Model::setMaterial(const Material& material)
{
	this->material = material;
}
