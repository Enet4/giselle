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
/** \file Giselle.h
 * \brief Main Giselle inclusion file
 *
 * \mainpage Giselle Index Page
 *
 * \section intro_sec Introduction
 *
 * Giselle is a 3D graphics library with the main purpose of covering a layer of
 * abstraction over the OpenGL API. End programmers will not need to use or understand
 * OpenGL programming, although a few concepts regarding 3D computer graphics may be
 * needed.
 *
 * \section install_sec Installation
 *
 * Giselle is a statically linked library.
 *
 * \subsection step1 Step 1: Compiling the library
 *
 * Compile it with the given Makefile in order to produce
 * the static library file \c libGiselle.a
 *
 * Please make sure that the compiler is willing to accept C++11 specifications. In GCC,
 * this can be done by adding the flag \c -std=c++0x . A version equal or greater than
 * GCC 4.6 is recommended.
 *
 * \subsection step2 Step 2: Including the library
 *
 * Simply include Giselle.h to access all features of the library. All declarations
 * of Giselle are situated in the \c giselle namespace.
 *
 * \subsection step3 Step 3: Linking the library with the program
 *
 * The dependencies with \a GLEW and \a GL libraries must be present, in this order, after
 * the Giselle library. This can be done in gcc using the following flags:
 *
 * \c -lGiselle \c -lGLEW \c -lGL
 *
 * \subsection license License
 *
 *  MIT
 */
#pragma once

// context
#include "GContext.h"
#include "Renderer.h"

// scene
#include "Scene.h"
#include "Entity.h"
#include "SimpleModelEntity.h"
#include "Camera.h"
#include "Light.h"

// model
#include "Model.h"
#include "Box.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Material.h"

// math
#include "Vector4f.h"
#include "Mat4x4f.h"
#include "MathUtils.h"
