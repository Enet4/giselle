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
#pragma once

/**
 * \file Model.h
 * \namespace giselle::model
 *
 * \brief Contains the means of describing models and materials.
 *
 * \class giselle::model::Model
 *
 * \brief Describes a geometric model composed of a triangle mesh.
 *
 * Instances of a Model contain the set of vertices, the respective vertex normals
 * and a list of vertex indices. Each 3 elements in the vertex array and the vertex
 * normals array describe a vertex position and a vertex normal, respectively.
 * The index array holds indices to the given vertices so that 3 indices describe a
 * triangle.
 *
 * A model is inconsistent when one of the arrays are undefined or
 * the index array references an unexistent vertex.
 */
#include "Material.h"

namespace giselle
{
	class GContext;

namespace model
{

	class Model
	{
		friend class giselle::GContext;

		private:
			unsigned int nVertices;
			unsigned int nTriangles;
			float* vertex_arr;
			float* vertex_normal_arr;
			unsigned int* index_arr;

			Material material;

		public:
			/** Default constructor
			 * Creates an empty model
			 */
			Model();

			/**
			 * Creates a model using the given vertex and index arrays
			 */
			Model( unsigned int nVertices, unsigned int nTriangles, float* vertex_array,
					float* vertex_normal_array, unsigned int* index_array,
					const Material& material = Material::BASE);

			/** Default destructor */
			virtual ~Model();

			/** Copy constructor
			*  \param other Model to copy from
			*/
			Model(const Model& other);

			/** Move constructor
			*  \param other Temporary Model to move from
			*/
			Model(Model&& other);

			/** Getter for the model's number of vertices */
			unsigned int getNVertices(void) const;

			/** Getter for the model's number of triangles */
			unsigned int getNTriangles(void) const;

			/** Getter for the model's vertex array */
			const float* getVertexArray(void) const;

			/** Getter for the model's vertex normal array */
			const float* getVertexNormalArray(void) const;

			/** Getter for the model's index array */
			const unsigned int* getIndexArray(void) const;

			/** Getter for the model's material */
			const Material& getMaterial(void) const;

			/** Sets a material to the model
			 * \param material
			 */
			 void setMaterial(const Material& material);

			/**
			 * Checks whether the model is consistent by observing the values of the
			 * index array
			 * \return whether the model is consistent
			 */
			bool isConsistent(void) const;

		protected:
		private:
	};

};

};
