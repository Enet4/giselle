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
 * \file Cylinder.h
 */
#pragma once

#include "Model.h"

namespace giselle
{
namespace model
{
	/**
	 * Creates a cylinder with a certain \b radius, \b height and <b>longitude
	 * precision</b>.
	 *
	 * The resulting cylinder will stand on the origin (the bottom base will contain it).
	 * \param radius the radius of the cylinder's bases
	 * \param height the height of the cylinder
	 * \param longitude_precision precision of the longitude of the cylinder
	 * \return the resulting model, or an empty model if the arguments are invalid
	 */
	Model Cylinder(float radius, float height, int longitude_precision = 8);
};
};
