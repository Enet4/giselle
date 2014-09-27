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
/**
 * \file Renderer.h
 * \class giselle::Renderer
 *
 * \brief Describes the renderer
 *
 * The renderer contains the base process of rendering a scene. One is automatically
 * created in a <b>GContext</b>.
 *
 * During the \c render() method of the graphical context, several attributes are
 * passed and repassed to the renderer in order to be forwarded to the shader program.
 * Ultimately, the renderer can take a model and draw the elements contained, after
 * all other uniform attributes were passed.
 *
 * Direct usage of this class is unadvised, unless when creating a visible type of
 * entity subclass. The renderer can thus be used to pass particular models and attributes
 * for rendering the entity in particular.
 */
#pragma once

#include "Mat4x4f.h"
#include "Entity.h"
#include "ShaderProgram.h"
#include "Material.h"
#include "Model.h"
#include <string>

namespace giselle
{

	class GContext;

	class Renderer
	{
		friend class giselle::GContext;
		friend class giselle::scene::Entity;

	private:
		ShaderProgram* p_prg; // simple renderer, always use this shader
		math::Mat4x4f model; // holds current model transformation matrix

	public:
		/** Default constructor */
		Renderer();
		/** Default destructor */
		~Renderer();

		/** Copy constructor deleted */
		Renderer(const Renderer& other) = delete;

		/** Move constructor
		 * \param other renderer to move from
		 */
		Renderer(Renderer&& other);

		/** Move assignment
		 * \param other renderer to move from
		 */
		Renderer& operator=(Renderer&& other);

		/**
		 * Checks whether the renderer is not ready for rendering
		 */
		bool operator!(void) const;

		/**
		 * Retrieves the index of a given shader attribute, in the current shader program
		 * \param att_name the name of the attribute
		 * \return index of the attribute, -1 if unavailable
		 */
		int getAttribute(const std::string& att_name) const;

		/**
		 * Retrieves the index of a given shader uniform attribute,
		 * in the current shader program
		 * \param att_name the name of the attribute
		 * \return index of the attribute, -1 if unavailable
		 */
		int getUniform(const std::string& att_name) const;

		/**
		 * Passes a new material to the renderer, making the next rendered model
		 * use the given material properties.
		 * \param mat the material
		 */
		void passMaterial(const model::Material& mat);

		/**
		 * Creates a temporary model transformation state according to the given
		 * entity's position and orientation, and renders the entity by calling
		 * \c ent.render()
		 */
		void render(const scene::Entity& ent);

		/**
		 * Draws the given model
		 * \param model the model to draw
		 */
		void drawModel(const model::Model& model);

	private:
		bool initShaders(void);

		/** Use the renderer's contained shader program. */
		void use(void);

		/** Set light attributes */
		void passLightProperties( const math::Vector4f& light_pos,
								const math::Vector4f& light_color);

		/** Set projection matrix attribute. */
		void passProjection(const math::Mat4x4f& proj);

		/** Set view matrix attribute.
		 * \param view the new view matrix
		 */
		void passViewMatrix(const math::Mat4x4f& view);

		/** Set model matrix attribute.
		 * \param model the new model matrix
		 */
		void passModelMatrix(const math::Mat4x4f& model);

		/** Set modelview matrix attribute.
		 * \deprecated Giselle now uses two matrices for this transformation.
		 * This function will define an unused shader attribute.
		 * Use \c passModelMatrix() and \c passViewMatrix() instead.
		 * \param modelView the matrix
		 */
		void passModelView(const math::Mat4x4f& modelView);
	};

};
