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
/** \file Scene.h
 * \namespace giselle::scene
 * \brief Contains classes for describing a scene and underlying entities
 * \class giselle::scene::Scene
 * \brief Describes a graphical scene
 *
 * This class describes a graphical scene, composed as a tree of entities. All scenes
 * contain an invisible root node, to which other entities are attached in order to
 * produce the desirable scene.
 *
 * Each scene can also contain one active light at a time. A light must be set before
 * rendering, using \c setLight()
 */
#pragma once

#include "Entity.h"
#include "Light.h"

namespace giselle {
namespace scene {

	class Scene
	{
		public:
			/** Default constructor
			 * Builds an empty scene
			 */
			Scene();

			/**
			 * Builds a scene with the given list of entities
			 */
			Scene(const std::initializer_list<Entity*> list);
			virtual ~Scene();

			/**
			 * \return reference to root entity of the scene
			 */
			Entity& root(void);

			/**
			 * Defines the light being used for illuminating the scene
			 * \param light reference to the light entity
			 */
			void setLight(Light& light);

			/**
			 * Adds a new light being used for illuminating the scene
			 * \param light reference to the light entity
			 * \return \b false if the maximum number of lights has been reached
			 * (see <tt>MAX_LIGHTS</tt> ) \b true otherwise
			 */
			bool addLight(Light& light);

			/**
			 * \return reference to currently used light
			 */
			const Light& getLight(void) const;

			/** Maximum number of active lights in a scene */
			static constexpr int MAX_LIGHTS = 5;

		protected:
		private:
			Entity r;
			Light* p_light;
			std::list<Light*> lights;
	};

}; };
