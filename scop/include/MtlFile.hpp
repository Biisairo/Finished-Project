#ifndef MTLFILE_HPP
#define MTLFILE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "Newmtl.hpp"

#include "glm/glm.hpp"

class MtlFile {
	private:
		std::string filename;

		bool error;

		std::vector<Newmtl> newmtl;

		void add_newmtl(std::stringstream &st);
		void add_Ka(std::stringstream &st);
		void add_Kd(std::stringstream &st);
		void add_Ks(std::stringstream &st);
		void add_Ns(std::stringstream &st);
		void add_Tr(std::stringstream &st);
		void add_d(std::stringstream &st);
		void add_Tf(std::stringstream &st);
		void add_illum(std::stringstream &st);
		void add_Ni(std::stringstream &st);
		void add_map_Ka(std::stringstream &st);
		void add_map_Kd(std::stringstream &st);
		void add_map_Ks(std::stringstream &st);
		void add_map_Ns(std::stringstream &st);
		void add_map_d(std::stringstream &st);
		void add_map_bump(std::stringstream &st);
		void add_bump(std::stringstream &st);
		void add_disp(std::stringstream &st);
		void add_decal(std::stringstream &st);

		void setMtl();

		void setError();

	public:
		MtlFile();
		MtlFile(std::string const &filename);
		~MtlFile();

		void setFilename(std::string filename);

		void print();
		bool is_open();

		std::vector<Material> getMaterial();
};

static bool isNumber(const std::string &s);
static bool matchMtl(const std::string &s);

#endif