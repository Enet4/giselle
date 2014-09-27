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
 * \file ShaderProgram.h
 * \class giselle::ShaderProgram
 *
 * \brief Describes a compiled shader program in OpenGL Shading Language
 *
 * The shader program is used by a \b Renderer to render the given models.
 * Its direct usage is not advised. Creating a \b GContext will already create a
 * renderer, and consequently the needed shader program.
 */

#pragma once

#include <string>
#include <functional>
#include <exception>

namespace giselle
{

struct ShaderException : public std::exception {
    const char* what(void) const noexcept override {
        return "failed to load GLSL shaders";
    }
};

class ShaderProgram
{
	private:
		int program;
		int vs;
		int fs;

	public:
		/** Main constructor, with default ; builds a basic shader program
		 * \param vertex_shader_code the vertex shader's GLSL source code
		 * \param fragment_shader_code the fragment shader's GLSL source code
		 * \throw ShaderException if the loading process fails
		 */
		ShaderProgram(	const char* vertex_shader_source = DEFAULT_VERTEX_SHADER,
						const char* fragment_shader_source = DEFAULT_FRAGMENT_SHADER );
		/** Default destructor */
		virtual ~ShaderProgram();

		/** Move constructor
		 * \param other the shader program to move from
		 */
		ShaderProgram(ShaderProgram&& other);

		/**
		 * bool cast operator
		 * Checks whether the shader program is ready
		 */
		operator bool(void) const;

		/**
		 * ! operator
		 * Checks whether the shader program is not ready
		 */
		bool operator! (void) const;

		/** Calculates a has value of the program
		 * \return the hash value of the object
		 */
		size_t hash(void) const;

		/** Getter for shader program number */
		int getProgram(void) const;
		/** Getter for program vertex shader number */
		int getVertexShader(void) const;
		/** Getter for program fragment shader number */
		int getFragmentShader(void) const;

		/**
		 * Retrieves the index of a given shader attribute
		 * \param att_name the name of the attribute
		 * \return index of the attribute, -1 if unavailable
		 */
		int getAttribute(const std::string& att_name) const;

		/**
		 * Retrieves the index of a given uniform shader attribute
		 * \param att_name the name of the attribute
		 * \return index of the attribute, -1 if unavailable
		 */
		int getUniform(const std::string& att_name) const;

	protected:
	private:
		bool loadShaders(const char* vertex_shader, const char* fragment_shader);
		static const char* const DEFAULT_VERTEX_SHADER;
		static const char* const DEFAULT_FRAGMENT_SHADER;
};

};

namespace std {
template<>
struct hash<giselle::ShaderProgram> {
public:
    size_t operator()(const giselle::ShaderProgram& obj) const;
};
};
