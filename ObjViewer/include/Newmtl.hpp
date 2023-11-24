#ifndef NEWMTL_HPP
#define NEWMTL_HPP

#include "pch.hpp"

typedef struct Material {
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;
} Material;

class Newmtl {
	private:
		std::string newmtl;

		glm::vec3 Ka;		
		glm::vec3 Kd;		
		glm::vec3 Ks;		
		float Ns;

		float Tr;
		glm::vec3 Tf;

		uint illum;

		float Ni;

		std::string map_Ka;
		std::string map_Kd;
		std::string map_Ks;
		std::string map_Ns;
		std::string map_d;
		std::string map_bump;
		std::string bump;
		std::string disp;
		std::string decal;

	public:
		Newmtl() = delete;
		Newmtl(std::string &name);
		~Newmtl();

		void add_Ka(float x, float y, float z);
		void add_Kd(float x, float y, float z);
		void add_Ks(float x, float y, float z);
		void add_Ns(float num);
		void add_Tr(float num);
		void add_Tf(float x, float y, float z);
		void add_illum(uint num);
		void add_Ni(float num);
		void add_map_Ka(std::string &string);
		void add_map_Kd(std::string &string);
		void add_map_Ks(std::string &string);
		void add_map_Ns(std::string &string);
		void add_map_d(std::string &string);
		void add_map_bump(std::string &string);
		void add_bump(std::string &string);
		void add_disp(std::string &string);
		void add_decal(std::string &string);

		void print();

		Material getMaterial();
};

#endif