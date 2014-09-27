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
 * \file Light.h
 * \class giselle::scene::Light
 * \brief Describes an entity for illuminating the scene
 *
 * A light is an entity for illuminating the whole scene. Once the light is set to the
 * scene using \c setLight() (not just attached), its properties will be used in the
 * rendering process of all entities.
 *
 * Like in other entities, the light is affected by transformations of its parent entity,
 * and its absolute position is considered in the rendering process.
 *
 */
#pragma once

#include "Entity.h"

namespace giselle
{

namespace scene
{

	class Light : public Entity
	{
		private:
			math::Vector4f color;

		public:
			/**
			 * The one constructor to rule them all. The position, orientation and
			 * list of child entities of the new light entity are defined.
			 * All parameters are optional.
			 *
			 * By default, the light's intensity is set to full white.
			 *
			 * \param pos position of the light (or direction if w coord is 0)
			 * \param ang orientation, not applicable to a light
			 * \param children list of pointers to all children entities
			 */
			Light(const math::Vector4f& pos = math::Vector4f(),
					const math::Vector4f& ang = math::Vector4f(),
					const std::list<Entity*> & children = std::list<Entity*>(),
					const math::Vector4f& light_color = math::Vector4f{1,1,1,1} );

			/** Default destructor */
			virtual ~Light();

			/** Setter for the light's color intensity
			 * \param color
			 */
			void setColor(const math::Vector4f& color);

			/** Getter for the light's color intensity
			 * \return RGBA vector containing the light's color intensity
			 */
			const math::Vector4f& getColor(void) const;

		protected:
		private:
	};

};

};
