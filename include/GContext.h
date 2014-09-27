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
 * \file GContext.h
 * \namespace giselle
 *
 * \brief The base Giselle namespace
 *
 * \class giselle::GContext
 * \brief Describes a graphical context.
 *
 * This class describes a graphical context. Applications must have at least one
 * functional context for rendering.
 *
 * In order to create a context, at least a width and height of the drawing region must
 * be specified. A context is bound to a particular scene and a camera (preferably of
 * the scene).
 *
 * The \a use() method instructs the underlying system to use that graphical context, and
 * must be called before any rendering call. The \a render() method will draw all
 * elements of the scene.
 *
 * \b Note: calling \a render() will not update the window's drawing region. This must
 * be done separately, according to the I/O API used in the end application.
 *
 */

#pragma once

#define GLEW_STATIC

#include <GL/glew.h>
#include <GL/gl.h>

#include <vector>

#include "Mat4x4f.h"
#include "Vector4f.h"
#include "Scene.h"
#include "Camera.h"
#include "Model.h"
#include "Entity.h"
#include "Renderer.h"

namespace giselle
{

	class GContext
	{

	private:
		int error;
		int x, y, w, h;
		scene::Scene* p_scene;
		scene::Camera* p_camera;
		Renderer renderer;

		void init(void);

	public:
		/**
		 * Builds an uninitialized graphical context. A context serves no purpose
		 * if it is not initialized
		 */
		GContext(void);

		/** Move constructor
		 * \param other GContext to move from
		 */
		GContext(GContext&& other);

		/**
		 * Builds a new graphical context using a window region and a scene
		 * \param x the x coordinate of the region
		 * \param y the y coordinate of the region
		 * \param width the width of the region
		 * \param height the height of the region
		 * \param scene reference to the scene
		 */
		GContext(int x, int y, int width, int height, scene::Scene& scene);
		/**
		 * Builds a new graphical context using a window region and a scene,
		 * defined in the origin: (x,y) = (0,0)
		 * \param width the width of the region
		 * \param height the height of the region
		 * \param scene reference to the scene
		 */
		GContext(int width, int height, scene::Scene& scene);

		/**
		 * Default Destructor
		 */
		~GContext(void);

		/**
		 * The \c ! operator checks whether the context's contained
		 * error code represents an error.
		 *
		 * A context cannot be used if this function returns \c true
		 *
		 * \return whether the context is in a bad state
		 */
		bool operator!(void) const;

		/**
		 * \return the contained error code of last context procedure
		 */
		int getError(void) const;

		/**
		 * \return the message associated to the last occurred error
		 */
		const char* getErrorMsg(void) const;

		/**
		 * Defines this as the current context.
		 */
		void use(void) const;

		/**
		 * Renders the whole scene.
		 * \param clear whether to clear the screen with the camera's
		 * background color, \b true by default
		 */
		void render(bool clear = true);

		/**
		 * Sets the camera used for rendering in the context. This must be done before
		 * any rendering. It is recommended that the camera entity being set is
		 * contained in the context's scene, but not mandatory.
		 * \param camera the camera object
		 * \param fix_aspect_ratio whether the camera's aspect ratio should be redefined
		 * according to the context's aspect ratio.
		 */
		void setCamera(scene::Camera& camera, bool fix_aspect_ratio = true);

		/**
		 * \return c-string representation of this machine's OpenGL version.
		 */
		static const unsigned char* getVersion(void);

		static constexpr int OK = 0;
		static constexpr int VAL_ERROR = 1;
		static constexpr int GLEW_ERROR = 2;
		static constexpr int SHADER_ERROR = 3;

	private:
		/** Recursively render an entity (and child entities) */
		void render_entity_rec(const scene::Entity* p_ent, const math::Mat4x4f& mat);

		static const char* const ERROR_MSGS[4];

		static bool Glew_Init;
	};

};
