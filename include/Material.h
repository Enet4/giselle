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
 * \file Material.h
 * \class giselle::model::Material
 *
 * \brief Describes a material for a model
 *
 */
#pragma once

#include "Vector4f.h"

namespace giselle
{

namespace model
{

class Material
{
	private:
		math::Vector4f amb;
		math::Vector4f diff;
		math::Vector4f spec;
		float kSpec;

	public:
		/** Default constructor */
		Material(void);

		/** Standard constructor
	     *
	     * All components are in RGBA
		 * \param ambient the ambient component of the material
		 * \param diffuse the diffuse component of the material
		 * \param specular the specular component of the material
		 * \param shininess the specularity exponent of the material
		 */
		Material(const math::Vector4f& ambient,
				const math::Vector4f& diffuse,
				const math::Vector4f& specular, float shininess);

		/** Default destructor */
		virtual ~Material();

		/** Copy constructor
		 *  \param other Material to copy from
		 */
		Material(const Material& other);

		/** Const reference getter of the ambient component
		 * \return reference to the ambient component of the material
		 */
		const math::Vector4f& ambient(void) const;

		/** Const reference getter of the diffuse component
		 * \return reference to the diffuse component of the material
		 */
		const math::Vector4f& diffuse(void) const;

		/** Const reference getter of the specular component
		 * \return reference to the specular component of the material
		 */
		const math::Vector4f& specular(void) const;

		/** Const reference getter of the shininess property
		 * \return reference to the shininess of the material
		 */
		const float& shininess(void) const;

		static const Material BASE;
};

};
};
