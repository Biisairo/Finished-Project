#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "pch.hpp"

GLuint loadTexture(std::string const &imagepath, bool Alpha, bool gamma);
GLuint loadTexture(std::vector<std::string> &faces, bool Alpha, bool gamma);

#endif