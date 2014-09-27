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
 * \file Camera.h
 * \class giselle::scene::Camera
 * \brief Describes a camera entity
 *
 * The camera establishes a view point and view volume for rendering. It can be
 * configured to produce an orthographic projection or a perspective projection. It
 * also defines the background color used by the graphical context.
 *
 * Like in other entities, the camera is affected by transformations of its parent entity,
 * and its absolute position and orientation is considered in the rendering process.
 *
 * A camera must be set to a graphical context before rendering, by using \a setCamera()
 */
#pragma once

#include "Entity.h"
#include "Mat4x4f.h"
#include "Vector4f.h"

namespace giselle
{

namespace scene
{

class Camera : public scene::Entity
{
	bool p;
	float fovy, view_height;
	float ratio, near, far;

	math::Mat4x4f proj;
	math::Vector4f back_color;

	public:
			/**
			 * The one constructor to rule them all. The position, orientation and
			 * list of child entities of the new entity are defined. All parameters are
			 * optional.
			 *
			 * \b Warning: The camera's projection attributes should be defined
			 * afterwards, using either \c ortho() or \c perspective()
			 *
			 * \param pos position
			 * \param ang orientation
			 * \param children list of pointers to all children entities
			 */
			Camera(const math::Vector4f& pos = math::Vector4f(),
					const math::Vector4f& ang = math::Vector4f(),
					const std::list<Entity*> & children = std::list<Entity*>() );

		/** Default destructor */
		virtual ~Camera();

		/** Copy constructor
		 *  \param other Object to copy from
		 */
		Camera(const Camera& other);

		/**
		 * \return whether the camera is currently using perspective
		 */
		 bool isPerspective(void) const;

		/** Gets the projection matrix object of this camera
		 * \return reference to the projection matrix
		 */
		const math::Mat4x4f& getProjectionMatrix(void) const;

		/**
		 * Sets an orthogonal view on the camera.
		 * \param view_height the height dimension of the camera's view volume
		 * \param near the near factor of the view volume
		 * \param far the far factor of the view volume
		 * \param aspect_ratio the view volume's aspect ratio
		 * \return whether the configuration was successful
		 */
		bool ortho( float view_height = Camera::DEFAULT_VIEW_HEIGHT,
					float near = Camera::DEFAULT_NEAR,
					float far = Camera::DEFAULT_FAR,
					float aspect_ratio = Camera::DEFAULT_RATIO);

		/**
		 * Sets an perspective view on the camera.
		 * \param fovy the Field of View on the Y coordinate of the camera
		 * \param near the near factor of the view volume
		 * \param far the far factor of the view volume
		 * \param aspect_ratio the view volume's aspect ratio
		 * \return whether the configuration was successful
		 */
		bool perspective(float fovy = Camera::DEFAULT_FOVY,
						 float near = Camera::DEFAULT_NEAR,
						 float far = Camera::DEFAULT_FAR,
						 float aspect_ratio = Camera::DEFAULT_RATIO);

		/**
		 * Sets orthogonal view on the camera using previously defined attributes.
		 * \return whether the configuration was successful
		 */
		bool ortho(void);

		/**
		 * Sets perspective view on the camera using previously defined attributes.
		 * \return whether the configuration was successful
		 */
		bool perspective(void);

		/**
		 * Redefines the view volume range of the camera.
		 * \param near the near factor of the view volume
		 * \param far the far factor of the view volume
		 * \return whether the configuration was successful
		 */
		bool setRange(float near, float far);

		/**
		 * Redefines the aspect ratio of the camera. The resulting aspect
		 * ratio value of \c w/h is used.
		 * \param w the width of the reference region
		 * \param h the height of the reference region
		 * \return whether the configuration was successful
		 */
		bool setAspectRatio(float w, float h);

		/**
		 * Redefines the aspect ratio of the camera.
		 * \param ratio the view volume's aspect ratio
		 * \return whether the configuration was successful
		 */
		bool setAspectRatio(float ratio);

		/**
		 * Redefines the FOV on the Y coordinate of the camera in perspective view.
		 * \param fovy the Field of View on the Y coordinate of the camera
		 * \return whether the configuration was successful
		 */
		bool setFOVy(float fovy);

		/**
		 * Redefines the height of the view volume in orthogonal view.
		 * \param fovy the Field of View on the Y coordinate of the camera
		 * \return whether the configuration was successful
		 */
		bool setHeight(float view_height);

		/**
		 * Sets the background color of the camera.
		 * \param r the red component of the color
		 * \param g the green component of the color
		 * \param b the blue component of the color
		 * \param a the alpha component of the color
		 */
		void setBackColor(float r, float g, float b, float a = 1.0f);
		/**
		 * Sets the background color of the camera.
		 * \param r the red component of the color
		 * \param g the green component of the color
		 * \param b the blue component of the color
		 * \param a the alpha component of the color
		 */
		void setBackColor(	unsigned char r, unsigned char g,
							unsigned char b, unsigned char a = 255);

		/**
		 * Gets the background color of the camera.
		 * \param r output reference to the red component of the color
		 * \param g output reference to the green component of the color
		 * \param b output reference to the blue component of the color
		 * \param a output reference to the alpha component of the color
		 */
		void getBackColor( float& r, float& g, float& b) const;

	protected:

	private:
		void calc_proj(void);

		static constexpr float DEFAULT_FOVY = 60.f;
		static constexpr float DEFAULT_VIEW_HEIGHT = 16.f;
		static constexpr float DEFAULT_RATIO = 1.f;
		static constexpr float DEFAULT_NEAR = 1.f;
		static constexpr float DEFAULT_FAR = 100.f;

	};

};

};
