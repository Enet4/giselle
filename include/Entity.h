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
 * \file Entity.h
 * \class giselle::scene::Entity
 * \brief This class defines an entity of a scene.
 *
 * Entities are the basis for an instance of anything in a scene. They do not
 * necessarily perform a useful task, but even the simplest entity can be made useful
 * by attaching child entities on itself, thus grouping those entities. The parent
 * entity's position and orientation affects the effective position and orientation of
 * all its child entities.
 *
 * All entity objects hold a position (x,y,z), an orientation (pitch,yaw,rool), a
 * pointer to the parent entity and a list of pointers to its child entities.
 *
 * End programmers can create new types of entities by inheriting the base \a Entity class
 * (or other inheritable subclasses such as \a SimpleModelEntity ).
 *
 */
#pragma once

#include <list>

#include "Vector4f.h"

namespace giselle
{
	class GContext;
	class Renderer;

namespace scene
{
	class Entity
	{
		friend class giselle::GContext;

		protected:
			math::Vector4f pos;
			math::Vector4f ang;

		private:
			Entity* parent;
			std::list<Entity*> children;

		public:
			/**
			 * The one constructor to rule them all. The position, orientation and
			 * list of child entities of the new entity are defined. All parameters are
			 * optional.
			 * \param pos position
			 * \param ang orientation
			 * \param children list of pointers to all children entities
			 */
			Entity(const math::Vector4f& pos = math::Vector4f(),
					const math::Vector4f& ang = math::Vector4f(),
					const std::list<Entity*> & children = std::list<Entity*>() );

			/** Default destructor */
			virtual ~Entity();

			/**
			 * Sets the entity's position.
			 * \param x
			 * \param y
			 * \param z
			 */
			void setPosition(float x, float y, float z);

			/**
			 * Sets the entity's orientation.
			 * \param pitch
			 * \param yaw
			 * \param roll
			 */
			void setOrientation(float pitch, float yaw, float roll);

			/**
			 * Adds the given vector to the entity's position vector.
			 * \param mov translation vector
			 */
			void move(const math::Vector4f& mov);

			/**
			 * Rotates the entity according to the pitch, yaw and roll
			 * components of the given vector
			 * \param rot rotation vector
			 */
			void rotate(const math::Vector4f& rot);

			/**
			 * Rotates the entity according to the given
			 * pitch, yaw and roll components
			 * \param d_pitch additional pitch
			 * \param d_yaw additional yaw
			 * \param d_roll additional roll
			 */
			void rotate(float d_pitch, float d_yaw, float d_roll);

			/** Constant reference getter for the entity's position */
			const math::Vector4f& position(void) const;
			/** Constant reference getter for the entity's orientation */
			const math::Vector4f& orientation(void) const;

			/** Calculates the entity's absolute position according to the entity's
			 * inheritance sequence: the positions and orientations of all parent
			 * entities are considered in order to produce both vectors.
			 *
			 * \param pos reference to the position output vector
			 * \param ang reference to the orientation output vector
			 */
			void absoluteVectors(math::Vector4f& pos, math::Vector4f& ang) const;

			/**
			 * Makes ent a child entity of this entity.
			 * \param ent the child entity
			 * \return whether the operation was successful
			 */
			bool attach(Entity& ent);

			/**
			 * Detaches child entity ent from this entity.
			 * \param ent the child entity
			 * \return whether the operation was successful
			 */
			void detach(Entity& ent);

			/**
			 * Const getter for reference to the list of the
			 * entity's children.
			 * \return reference to the entity's children list
			 */
			const std::list<Entity*>& getChildren(void) const;

			virtual void render(Renderer& renderer) const;

		protected:
			virtual void setParent(Entity& parent_ent);
			void setParent(std::nullptr_t);

		private:
			const Entity* getParent(void) const;
	};
};
};
