#ifndef TEXTURE_HPPv
#define TEXTURE_HPPv

#include <iostream>
#include <fstream>
#include <vector>

#include "GL/glew.h"

GLuint loadDDS(std::string const &imagepath);
GLuint loadPPM(std::string const &filename);
GLuint loadTexture(std::string const &imagepath);

#endif