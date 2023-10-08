#include "Person.hpp"

Person::Person() {}
Person::~Person() {}

std::vector<glm::vec3> Person::getCube() {
	static std::vector<glm::vec3> cube = {
		{-0.5f, -0.5f, 0.5f},
		{0.5f, -0.5f, 0.5f},
		{0.5f,  0.5f, 0.5f},
		{-0.5f, -0.5f, 0.5f},
		{0.5f,  0.5f, 0.5f},
		{-0.5f,  0.5f, 0.5f},
		{-0.5f, -0.5f, -0.5f},
		{0.5f, -0.5f, -0.5f},
		{0.5f,  0.5f, -0.5f},
		{-0.5f, -0.5f, -0.5f},
		{0.5f,  0.5f, -0.5f},
		{-0.5f,  0.5f, -0.5f},
		{-0.5f, -0.5f, -0.5f},
		{-0.5f,  0.5f, -0.5f},
		{-0.5f,  0.5f, 0.5f},
		{-0.5f, -0.5f, -0.5f},
		{-0.5f,  0.5f, 0.5f},
		{-0.5f, -0.5f, 0.5f},
		{0.5f, -0.5f, -0.5f},
		{0.5f,  0.5f, -0.5f},
		{0.5f,  0.5f, 0.5f},
		{0.5f, -0.5f, -0.5f},
		{0.5f,  0.5f, 0.5f},
		{0.5f, -0.5f, 0.5f},
		{-0.5f,  0.5f, -0.5f},
		{0.5f,  0.5f, -0.5f},
		{0.5f,  0.5f, 0.5f},
		{-0.5f,  0.5f, -0.5f},
		{0.5f,  0.5f, 0.5f},
		{-0.5f,  0.5f, 0.5f},
		{-0.5f, -0.5f, -0.5f},
		{0.5f, -0.5f, -0.5f},
		{0.5f, -0.5f, 0.5f},
		{-0.5f, -0.5f, -0.5f},
		{0.5f, -0.5f, 0.5f},
		{-0.5f, -0.5f, 0.5f}
	};

	return cube;
}

std::vector<glm::mat4> Person::getPerson(std::vector<glm::vec3> points, std::vector<glm::vec3> lines) {
	std::vector<glm::mat4> res;

	for (std::vector<glm::vec3>::iterator it = points.begin(); it != points.end(); it++) {
		glm::mat4 model = glm::scale(glm::mat4(1), {0.1, 0.1, 0.1});
		model = glm::translate(glm::mat4(1), *it) * model;
		res.push_back(model);
	}

	return res;
}