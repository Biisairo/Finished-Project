#include "Newmtl.hpp"

using namespace std;

Newmtl::Newmtl(string &name): newmtl(name) {
	this->Ka = glm::vec3(0.1, 0.1, 0.1);
	this->Kd = glm::vec3(0.5, 0.5, 0.5);
	this->Ks = glm::vec3(1, 1, 1);
	this->Ns = 32;

	this->Tr = 0;
	this->Tf = glm::vec3(1, 1, 1);

	this->illum = 2;

	this->Ni = 1;
}

Newmtl::~Newmtl() {}

void Newmtl::add_Ka(float x, float y, float z){
	this->Ka = glm::vec3(x, y, z);
}

void Newmtl::add_Kd(float x, float y, float z){
	this->Kd = glm::vec3(x, y, z);
}

void Newmtl::add_Ks(float x, float y, float z){
	this->Ks = glm::vec3(x, y, z);
}

void Newmtl::add_Ns(float num){
	this->Ns = num;
}

void Newmtl::add_Tr(float num){
	this->Tr = num;
}

void Newmtl::add_Tf(float x, float y, float z){
	this->Tf = glm::vec3(x, y, z);
}

void Newmtl::add_illum(uint num){
	this->illum = num;
}

void Newmtl::add_Ni(float num){
	this->Ni = num;
}

void Newmtl::add_map_Ka(std::string &string){
	this->map_Ka = string;
}

void Newmtl::add_map_Kd(std::string &string){
	this->map_Kd = string;
}

void Newmtl::add_map_Ks(std::string &string){
	this->map_Ks = string;
}

void Newmtl::add_map_Ns(std::string &string){
	this->map_Ns = string;
}

void Newmtl::add_map_d(std::string &string){
	this->map_d = string;
}

void Newmtl::add_map_bump(std::string &string){
	this->map_bump = string;
}

void Newmtl::add_bump(std::string &string){
	this->bump = string;
}

void Newmtl::add_disp(std::string &string){
	this->disp = string;
}

void Newmtl::add_decal(std::string &string){
	this->decal = string;
}

void Newmtl::print(){
	cout << "==============================================" << endl;
	cout << this->newmtl << "\n\n" <<
			"Ka : " << this->Ka.x << " " << this->Ka.y << " " << this->Ka.z << "\n" <<
			"Kd : " << this->Kd.x << " " << this->Kd.y << " " << this->Kd.z << "\n" <<
			"Ks : " << this->Ks.x << " " << this->Ks.y << " " << this->Ks.z << "\n" <<
			"Ns : " << this->Ns << "\n" <<
			"Tr : " << this->Tr << "\n" <<
			"Tf : " << this->Tf.x << " " << this->Tf.y << " " << this->Tf.z << "\n" <<
			"illum : " << this->illum << "\n" <<
			"Ni : " << this->Ni << "\n" <<
			"map_Ka : " << this->map_Ka << "\n" <<
			"map_Kd : " << this->map_Kd << "\n" <<
			"map_Ks : " << this->map_Ks << "\n" <<
			"map_Ns : " << this->map_Ns << "\n" <<
			"map_d : " << this->map_d << "\n" <<
			"map_bump : " << this->map_bump << "\n" <<
			"bump : " << this->bump << "\n" <<
			"disp : " << this->disp << "\n" <<
			"decal : " << this->decal << endl;
	cout << "==============================================" << endl;
}

Material Newmtl::getMaterial() {
	Material res;
	res.ambient = this->Ka;
	res.diffuse = this->Kd;
	res.specular = this->Ks;
	res.shininess = this->Ns;
	return res;
}