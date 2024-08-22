#ifndef PCH_HPP
#define PCH_HPP

#define ASF "143.asf"
#define AMC "143.amc"

// std
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>

// imgui
#if IMGUI_USE
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#endif

// opengl
#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// glm
#if GLM_USE
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/compatibility.hpp>
#endif

// assimp
#if ASSIMP_USE
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#endif

// spdlog
#if SPDLOG_USE
#include <spdlog/spdlog.h>
#endif

// stb
#if STB_IMAGE_USE
#include <stb/stb_image.h>
#endif

#endif