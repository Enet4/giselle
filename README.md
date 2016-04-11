# Giselle - 3D graphics library

[![No Maintenance Intended](http://unmaintained.tech/badge.svg)](http://unmaintained.tech/)

Giselle is a 3D graphics library with the main purpose of covering a layer of abstraction over the OpenGL API. End programmers will not need to use or understand OpenGL programming, although knowing a few concepts about 3D computer graphics is recommended.

# Installation

Giselle is a statically linked library.

## Compiling the library

Compile it with the given Makefile in order to produce the static library file `libGiselle.a`. Please make sure that the compiler is willing to accept C++11 specifications. In GCC, this can be done by adding the flag `-std=c++11` (or `-std=c++0x` on older versions).
A version of GCC equal or greater than 4.6 is recommended.

## Including the library

Simply include Giselle.h to access all features of the library. All declarations of Giselle are situated in the `giselle` namespace.

## Linking the library with the program

The dependencies with GLEW and GL libraries must be present, in this order, after the Giselle library. This can be done in gcc using the following flags:
`-lGiselle -lGLEW -lGL`

## License

MIT
