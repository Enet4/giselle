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
#include "Material.h"

using namespace giselle;
using namespace math;
using namespace model;

const Material Material::BASE =
	Material({0.25f,0.25f,0.25f, 1}, {0.75f,0.75f,0.75f}, {0.25f,0.25f,0.25f}, 30.0f);

Material::Material(void)
:	amb({})
,	diff({})
,	spec({})
,	kSpec(0)
{
}

Material::Material(const Vector4f& ambient,
				const Vector4f& diffuse,
				const Vector4f& specular, float shininess)
:	amb(ambient)
,	diff(diffuse)
,	spec(specular)
,	kSpec(shininess)
{
}

Material::~Material()
{
}

Material::Material(const Material& other)
:	amb(other.amb)
,	diff(other.diff)
,	spec(other.spec)
,	kSpec(other.kSpec)
{
}

const Vector4f& Material::ambient(void) const
{ return this->amb; }

const Vector4f& Material::diffuse(void) const
{ return this->diff; }

const Vector4f& Material::specular(void) const
{ return this->spec; }

const float& Material::shininess(void) const
{ return this->kSpec; }
