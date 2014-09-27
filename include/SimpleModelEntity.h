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
 * \file SimpleModelEntity.h
 * \class giselle::scene::SimpleModelEntity
 * \brief An Entity with a model
 *
 * This class defines an entity with a fully contained model. The \c render() method was
 * overridden in order to render the model with its call.
 */
#pragma once

#include "Entity.h"
#include "Model.h"
#include "Renderer.h"

namespace giselle
{

namespace scene
{

class SimpleModelEntity : public Entity
{
	private:
		model::Model model;
	public:
		/** The one constructor to rule them all */
		SimpleModelEntity(	const model::Model& model,
				const math::Vector4f& pos = math::Vector4f(),
				const math::Vector4f& ang = math::Vector4f(),
				const std::list<Entity*> & children = std::list<Entity*>() );

		/** Default destructor */
		virtual ~SimpleModelEntity();

		/** Copy constructor
		 *  \param other entity to copy from
		 */
		SimpleModelEntity(const SimpleModelEntity& other);

		/** Getter for the entity's model
		 * \return reference to the current model
		 */
		model::Model& getModel() { return this->model; }

		/**
		 * Renders the entity. It will draw the contained model.
		 * \param renderer
		 */
		virtual void render(Renderer& renderer) const;
};

};

};
