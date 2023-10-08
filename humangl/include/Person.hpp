#ifndef PERSON_HPP
#define PERSON_HPP

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <iostream>
#include <vector>

class Person{

	private:


	public:
		Person();
		~Person();

		std::vector<glm::vec3> getCube();
		std::vector<glm::mat4> getPerson(std::vector<glm::vec3> points, std::vector<glm::vec3> lines);

};

#endif