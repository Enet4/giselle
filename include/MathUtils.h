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
 * \file MathUtils.h
 * \namespace giselle::math
 *
 * \brief Contains a collection of mathematical functions and classes
 *
 */
#pragma once

#include "Mat4x4f.h"
#include "Vector4f.h"

#include <ostream>

namespace giselle
{
	namespace math
	{
		/**
		 * Pi mathematical constant.
		 */
		constexpr double PI = 3.141592653589793238462643383279502884197169;

		/**
		 * Converts an angle in degrees to radians
		 * \param angle the angle in degrees
		 * \return the angle in radians
		 */
		constexpr float degrees2radians(float angle)
		{ return angle * PI / 180.0f; }

		/**
		 * Converts an angle in radians to degrees
		 * \param angle the angle in radians
		 * \return the angle in degrees
		 */
		constexpr float radians2degrees(float angle)
		{ return angle * 180.0f / (float)PI; }

		/**
		 * Multiplies a vector with a matrix.
		 * \param vec the affected vector
		 * \param mat the matrix for multiplication
		 * \return the modified vector
		 */
		Vector4f& multiply(Vector4f& vec, const Mat4x4f& mat);

		/**
		 * Perform a translation on the given matrix \b mat using a vector \b v
		 * \return the same matrix, modified by the function
		 */
		Mat4x4f& translate(Mat4x4f& mat, const Vector4f& v);

		/**
		 * Perform a translation on the given matrix \b mat using the list of
		 * coordinates \b x , \b y , \b z [, \b w ]
		 * \return the same matrix, modified by the function
		 */
		Mat4x4f& translate(Mat4x4f& mat, float x, float y, float z, float w = 1.0f);

		/**
		 * Perform a scale transformation on the given matrix \b mat using the list of
		 * coordinates \b x , \b y , \b z [, \b w ]
		 * \return the same matrix, modified by the function
		 */
		Mat4x4f& scale(Mat4x4f& mat, float x, float y, float z, float w = 1.0f);

		/**
		 * Performs a rotation around the X axis.
		 * \param ang the X angle value in radians
		 * \return the same matrix, modified by the function
		 */
		Mat4x4f& rotateAroundX(Mat4x4f& mat, float ang);

		/**
		 * Performs a rotation around the Y axis.
		 * \param ang the Y angle value in radians
		 * \return the same matrix, modified by the function
		 */
		Mat4x4f& rotateAroundY(Mat4x4f& mat, float ang);

		/**
		 * Performs a rotation around the Z axis.
		 * \param ang the Z angle value in radians
		 * \return the same matrix, modified by the function
		 */
		Mat4x4f& rotateAroundZ(Mat4x4f& mat, float ang);

		/**
		 * Performs a sequence of 3 rotations in this order: X, Y and Z.
		 * \param ang the vector containing the 3 angle values in radians
		 * \return the same matrix, modified by the function
		 */
		Mat4x4f& rotate(Mat4x4f& mat, const Vector4f& ang);

		/**
		 * Performs a sequence of 3 rotations in this order: pitch, yaw and roll.
		 * \param pitch the pitch component in radians
		 * \param yaw the yaw component in radians
		 * \param roll the roll component in radians
		 * \return the same matrix, modified by the function
		 */
		Mat4x4f& rotate(Mat4x4f& mat, float pitch, float yaw, float roll);

		/**
		 * Prints a simple textual presentation of a matrix to an output stream.
		 * The elements are arranged in a 4x4 grid, containing a full row in each line
		 * separated by spaces.
		 *
		 * \param stream the output stream to write to
		 * \param mat
		 * \return the same stream object
		 */
		std::ostream& operator<< (std::ostream& stream, const Mat4x4f& mat);

		/**
		 * Prints a simple textual presentation of a vector to an output stream.
		 * The output is given in the format "(x ,y ,z ,w )", without any new lines.
		 *
		 * \param stream the output stream to write to
		 * \param vec
		 * \return the same stream object
		 */
		std::ostream& operator<< (std::ostream& stream, const Vector4f& vec);

	};
};
