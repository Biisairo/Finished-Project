#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "pch.hpp"

#include "ObjFile.hpp"
#include "MtlFile.hpp"

#include <random>

class Object{

	private:
		glm::mat4	model;
		ObjFile		objFile;
		MtlFile		mtlFile;

		GLuint VAO;
		GLuint VERTEX;
		GLuint VERTEXTEXTURE;
		GLuint VERTEXNORMAL;
		GLuint VERTEXCOLOR;

		bool		is_error;

		std::vector<glm::vec4>	vertices;
		std::vector<glm::vec2>	verticesTexture;
		std::vector<glm::vec3>	verticesNormal;
		std::vector<glm::vec3>	verticesColor;

		void	putVerticesArray();

	public:
		Object();
		Object(std::string const &filename);
		~Object();
		void destroy();

		glm::mat4	getModel();
		std::vector<glm::vec4>	getVertices() const;
		std::vector<glm::vec2>	getVerticesTexture() const;
		std::vector<glm::vec3>	getVerticesNormal() const;
		std::vector<Material> getMaterial();

		glm::vec3 center();

		void genColor();

		void rotateX(float degree);
		void rotateY(float degree);
		void rotateZ(float degree);

		void draw();

		void printObj();

		bool isError();
};

#endif