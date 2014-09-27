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
 * \file Vector4f.h
 * \class giselle::math::Vector4f
 *
 * \brief This class defines a 4-dimensional vector of single precision
 * floating point values, used throughout the library.
 */

#pragma once

#include <initializer_list>

namespace giselle
{

namespace math
{

class Vector4f
{
private:
	float v[4];
public:
	/**
	 * Default Constructor
	 * Builds a blank homogeneous vector (0,0,0,1)
	 */
	constexpr Vector4f(): v{0,0,0,1}{}
	/**
	 * Copy Constructor
	 */
	constexpr Vector4f(const Vector4f& other):
		v{other.v[0],other.v[1],other.v[2],other.v[3]}{}

	/**
	 * Initializer List constructor
	 *
	 * The constructor will use the first 4 values of the list to produce the vector.
	 * If the size of the list is too short, the remaining unset components will be
	 * automatically set to 1 for the W component and 0 for the X, Y and Z components.
	 * \param list the initializer list
	 */
	Vector4f(const std::initializer_list<float> & list);
	/**
	 * Array pointer constructor
	 *
	 * \b Warning: unsafe. Other constructors should be preferred
	 */
	Vector4f(const float* p_v);

	/**
	 * Builds the vector using the given values of each dimension
	 *
	 * Only the x and y dimensions are required
	 */
	Vector4f(float x, float y, float z = 0.0f, float w = 1.0f);

	/**
	 * Destructor
	 */
	~Vector4f(void);

	/**
	 * const float * cast operator
	 *
	 * \return a const float pointer to the vector
	 */
	operator const float* (void) const;

	/**
	 * Calculates the squared length of the (x,y,z) vector
	 * \return the squared length of the vector
	 */
	 float lengthSqr(void) const;

	/**
	 * Calculates the length of the (x,y,z) vector
	 * \return the length of the vector
	 */
	 float length(void) const;

	/**
	 * normalizes the vector
	 * \return the vector itself
	 */
	Vector4f& normalize(void);

	/**
	 * clamps each component of the vector to [0,1]
	 * \return the vector itself
	 */
	Vector4f& clamp(void);

	/**
	 * performs a component-wise sum of the vectors, including
	 * the W component!
	 *
	 * \param other
	 * \return the vector itself
	 */
	Vector4f& operator+=(const Vector4f& other);
	/**
	 * performs a component-wise sum of the vectors,
	 * including the W component!
	 * \param other
	 * \return a temporary vector object containing the result
	 */
	const Vector4f& operator+(const Vector4f& other) const;
	/**
	 * performs a component-wise subtraction of the vectors,
	 * including the W component!
	 * \param other
	 * \return the vector itself
	 */
	Vector4f& operator-=(const Vector4f& other);
	/**
	 * performs a component-wise subtraction of the vectors,
	 * including the W component!
	 * \param other
	 * \return a temporary vector object containing the result
	 */
	const Vector4f& operator-(const Vector4f& other) const;
	/**
	 * Multiplies the vector with a scalar
	 * \param fscalar
	 * \return the vector itself
	 */
	Vector4f& operator*=(float fscalar);

	/**
	 * Performs a component-wise multiplication with another vector
	 * \param other
	 * \return the vector itself
	 */
	Vector4f& operator*=(const Vector4f& other);

	/**
	 * Performs the dot product with another vector
	 * \param other
	 * \return the dot product of the two vectors
	 */
	float dot(const Vector4f& other) const;

	/**
	 * Getter for the X component
	 * \return the X component of the vector
	 */
	float& x(void);
	/**
	 * Const getter for the X component
	 * \return the X component of the vector
	 */
	float x(void) const;

	/**
	 * Getter for the Y component
	 * \return the Y component of the vector
	 */
	float& y(void);
	/**
	 * Const getter for the Y component
	 * \return the Y component of the vector
	 */
	float y(void) const;

	/**
	 * Getter for the Z component
	 * \return the Z component of the vector
	 */
	float& z(void);
	/**
	 * Const getter for the Z component
	 * \return the Z component of the vector
	 */
	float z(void) const;

	/**
	 * Getter for the W component
	 * \return the W component of the vector
	 */
	float& w(void);
	/**
	 * Const getter for the W component
	 * \return the W component of the vector
	 */
	float w(void) const;

};

};

};
