#ifndef OBJFILE_HPP
#define OBJFILE_HPP

#include "pch.hpp"

typedef struct FElem{
	int	v;
	int	vt;
	int	vn;
} FElem;

typedef struct F {
	FElem elem[3];
} F;

typedef struct L {
	std::vector<int> elem;
} L;

typedef struct Index {
	std::string	name;
	int	index;

	Index(std::string name, int index);
} Index;

class ObjFile {
	private:
		std::string	filename;

		bool	error;

		std::string	mtllib;

		std::vector<glm::vec4>	v;
		std::vector<glm::vec3>	vt;
		std::vector<glm::vec3>	vn;
		std::vector<glm::vec3>	vp;

		std::vector<F>	f;
		std::vector<L>	l;
		std::vector<Index>	usemtl;

		std::vector<Index>	s;

		std::vector<Index>	o;
		std::vector<Index>	g;

		std::vector<glm::vec4> vF;
		std::vector<glm::vec2> vtF;
		std::vector<glm::vec3> vnF;

		void	setObj();

		void	add_v(std::stringstream &st);
		void	add_vt(std::stringstream &st);
		void	add_vn(std::stringstream &st);
		void	add_vp(std::stringstream &st);
		void	add_f(std::stringstream &st);
		void	add_l(std::stringstream &st);
		void	add_usemtl(std::stringstream &st);
		void	add_mtllib(std::stringstream &st);
		void	add_o(std::stringstream &st);
		void	add_g(std::stringstream &st);
		void	add_s(std::stringstream &st);

		void	setError();
		
		void	genVT();
		void	genVN();

		void	setV();
		void	setVT();
		void	setVN();

	public:
		ObjFile();
		ObjFile(std::string const &filename);
		~ObjFile();

		void print();
		bool is_open();
		
		std::vector<glm::vec4> getV();
		std::vector<glm::vec2> getVT();
		std::vector<glm::vec3> getVN();
		std::string getMtllib();
};

static	bool	isNumber(const std::string &s);
static	bool	matchObj(const std::string &s);
// static	

#endif