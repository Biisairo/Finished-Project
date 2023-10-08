#ifndef SHADER_HPP
#define SHADER_HPP

#include <iostream>
#include <fstream>

#include "GL/glew.h"

class Program {
	private:
		GLenum types[6];
		GLuint shaderId[6];
		GLuint programId;

		void deleteShader(GLenum type);
		void clearShader();

	public:
		Program();
		~Program();
		Program(const Program &other) = delete;
		Program &operator=(const Program &other) = delete;

		bool loadShader(GLenum type, std::string const &filename);
		bool loadProgram();

		GLuint id();

		bool is_set();
		void use();
};

#endif
