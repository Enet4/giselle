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
#include "ShaderProgram.h"

#include <GL/glew.h>
#include <GL/gl.h>

#if _GISELLE_DEBUG == 1
#include <iostream>
static char INFO_LOG_BUFFER[1024];
#define ShaderProgram_D(x,y) \
	glGetShaderInfoLog(x,1024,NULL,INFO_LOG_BUFFER); \
	std::cout << y
#define ShaderProgram_DP(x,y) \
	glGetProgramInfoLog(x,1024,NULL,INFO_LOG_BUFFER); \
	std::cout << y
#else
#define ShaderProgram_D(x,y)
#define ShaderProgram_DP(x,y)
#endif

using namespace giselle;

const char* const ShaderProgram::DEFAULT_VERTEX_SHADER =
"#version 130\n"
"attribute vec3 pos;\n"
"attribute vec3 vnorm;\n"
"uniform mat4x4 proj;\n"
//"uniform mat4x4 modelView;"
"uniform mat4x4 model;\n"
"uniform mat4x4 view;\n"
"out vec3 fN, fE, fL;\n"
"uniform vec4 light_pos;\n"

"void main() {\n"
	"mat4x4 modelview = view * model;\n"
	"vec4 worldpos = model * vec4(pos, 1.0);\n" // world position
	"vec4 viewpos = view * worldpos;\n"
	"fN = (transpose(inverse(model)) * vec4(vnorm,0)).xyz;\n"
	"fE = vec3(viewpos);\n"
	"fL = light_pos.xyz;\n"
	"if( light_pos.w != 0.0 ) fL = light_pos.xyz - worldpos.xyz;\n"
	"gl_Position = proj * viewpos;\n"
"}\n";

const char* const ShaderProgram::DEFAULT_FRAGMENT_SHADER =
"#version 130\n"
"in vec3 fN, fE, fL;\n"
"uniform vec4 ambient_prod, diffuse_prod, specular_prod; \n"
"uniform vec3 light_color;\n"
//"uniform mat4 modelView;"
"uniform float shininess;\n"

"void main()\n"
"{\n"
	"vec3 N = normalize(fN);\n"
	"vec3 E = normalize(fE);\n"
	"vec3 L = normalize(fL);\n"
	//"vec3 H = normalize(L + E);"
	"vec3 R = reflect(L, N);\n"

	"vec4 ambient = ambient_prod;\n"
	"float Kd = max(dot(L, N), 0.0);\n"
	"vec4 diffuse = Kd * diffuse_prod;\n"
	"float Ks = pow(max(dot(E, R), 0.0), shininess);\n"
	"vec4 specular = Ks * specular_prod;\n"
	"if( dot(L, N) < 0.0 ) specular = vec4(0.0, 0.0, 0.0, 1.0);\n"

	"gl_FragColor = ambient + (diffuse + specular) * vec4(light_color, 1.0);\n"
	"gl_FragColor.a = ambient.a;\n"
"}\n";

ShaderProgram::ShaderProgram( const char* vertex_shader_source,
							const char* fragment_shader_source)
:	program(0)
,	vs(0)
,	fs(0)
{
	if (!loadShaders(vertex_shader_source, fragment_shader_source)) {
            throw ShaderException();
	}
}

ShaderProgram::ShaderProgram(ShaderProgram&& other)
:	program(other.program)
,	vs(other.vs)
,	fs(other.fs)
{
	other.program = other.vs = other.fs = 0;
}

ShaderProgram::~ShaderProgram()
{
	if (vs > 0)
		glDeleteShader(vs);
	if (fs > 0)
		glDeleteShader(fs);
	if (program > 0)
		glDeleteProgram(program);
	program = vs = fs = 0;
}

bool ShaderProgram::loadShaders(const char* vertex_shader, const char* fragment_shader)
{
	int status;

	// create vertex shader
	this->vs = glCreateShader(GL_VERTEX_SHADER);
	if (vs == 0) return false;

	// build vertex shader
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);
	glGetShaderiv(vs, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		ShaderProgram_D(vs,"BAD VS\n" << INFO_LOG_BUFFER << "\n");
		glDeleteShader(GL_VERTEX_SHADER);
		glDeleteShader(GL_FRAGMENT_SHADER);
		return false;
	}

	// create fragment shader
	this->fs = glCreateShader(GL_FRAGMENT_SHADER);
	if (fs == 0)
	{
		glDeleteShader(GL_VERTEX_SHADER);
		return false;
	}

	// build fragment shader
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);
	glGetShaderiv(fs, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		ShaderProgram_D(fs, "BAD FS\n" << INFO_LOG_BUFFER << "\n");
		glDeleteShader(GL_VERTEX_SHADER);
		glDeleteShader(GL_FRAGMENT_SHADER);
		return false;
	}

	// build program
	this->program = glCreateProgram();
	glAttachShader(this->program, vs);
	glAttachShader(this->program, fs);

	// link program
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		ShaderProgram_DP(program,"Program:\n" << INFO_LOG_BUFFER << "\n");
		glDeleteProgram(program);
		glDeleteShader(GL_VERTEX_SHADER);
		glDeleteShader(GL_FRAGMENT_SHADER);
		return false;
	}

	return true;
}

ShaderProgram::operator bool(void) const
{ return this->program != 0; }

bool ShaderProgram::operator! (void) const
{ return this->program == 0; }

int ShaderProgram::getProgram(void) const
{ return this->program; }

int ShaderProgram::getVertexShader(void) const
{ return this->vs; }

int ShaderProgram::getFragmentShader(void) const
{ return this->fs; }

int ShaderProgram::getAttribute(const std::string& att_name) const
{
	if (program == 0) return -1;
	int att = glGetAttribLocation(program, att_name.c_str());
	return att;
}

int ShaderProgram::getUniform(const std::string& att_name) const
{
	if (program == 0) return -1;
	int att = glGetUniformLocation(program, att_name.c_str());
	return att;
}

size_t std::hash<ShaderProgram>::operator()(const ShaderProgram& obj) const
{
	return std::hash<int>()(obj.getProgram());
}
