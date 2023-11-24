#include "MtlFile.hpp"

using namespace std;

MtlFile::MtlFile():error(true) {}

MtlFile::MtlFile(std::string const &filename): filename(filename) {
	if (!matchMtl(this->filename))
		this->setError();

	this->setMtl();
	if (this->error)
		cout << "Fail to set mtl file" << endl;
}

MtlFile::~MtlFile() {}

void MtlFile::setFilename(string filename) {
	if (!error)
		return;
	this->filename = filename;
	this->error = false;
	
	this->setMtl();
	if (this->error)
		cout << "Fail to set mtl file" << endl;
}

void MtlFile::setMtl() {
	fstream file;

	if (this->error)
		return ;

	file.open(this->filename);
	if (!file.is_open())
		return this->setError();

	while(!file.eof()) {
		string line;

		if (this->error) {
			file.close();
			return ;
		}

		getline(file, line);
		if (line.empty())
			continue;

		stringstream st(line);
		string elem;

		getline(st, elem, ' ');

		if (elem == "newmtl")
			this->add_newmtl(st);
		else if (elem == "Ka")
			this->add_Ka(st);
		else if (elem == "Kd")
			this->add_Kd(st);
		else if (elem == "Ks")
			this->add_Ks(st);
		else if (elem == "Ns")
			this->add_Ns(st);
		else if (elem == "Tr")
			this->add_Tr(st);
		else if (elem == "d")
			this->add_d(st);
		else if (elem == "Tf")
			this->add_Tf(st);
		else if (elem == "illum")
			this->add_illum(st);
		else if (elem == "Ni")
			this->add_Ni(st);
		else if (elem == "map_Ka")
			this->add_map_Ka(st);
		else if (elem == "map_Kd")
			this->add_map_Kd(st);
		else if (elem == "map_Ks")
			this->add_map_Ks(st);
		else if (elem == "map_Ns")
			this->add_map_Ns(st);
		else if (elem == "map_d")
			this->add_map_d(st);
		else if (elem == "map_bump")
			this->add_map_bump(st);
		else if (elem == "bump")
			this->add_bump(st);
		else if (elem == "disp")
			this->add_disp(st);
		else if (elem == "decal")
			this->add_decal(st);
		else if (elem[0] == '#')
			continue;
		else {
			file.close();
			return this->setError();
		}
	}

	file.close();
}

void MtlFile::add_newmtl(std::stringstream &st) {
	string elem;
	int i = 0;
	for (string str; getline(st, str, ' '); ) {
		elem = str;
		i++;
	}
	if (i != 1)
		return this->setError();
	this->newmtl.push_back(Newmtl(elem));
}

void MtlFile::add_Ka(std::stringstream &st) {
	float elem[3];
	int i = 0;
	for (string str; getline(st, str, ' '); ) {
		if (!isNumber(str))
			return this->setError();
		elem[i] = stof(str);
		i++;
	}
	if (i != 3)
		return this->setError();
	this->newmtl.back().add_Ka(elem[0], elem[1], elem[2]);
}

void MtlFile::add_Kd(std::stringstream &st) {
	float elem[3];
	int i = 0;
	for (string str; getline(st, str, ' '); ) {
		if (!isNumber(str))
			return this->setError();
		elem[i] = stof(str);
		i++;
	}
	if (i != 3)
		return this->setError();
	this->newmtl.back().add_Kd(elem[0], elem[1], elem[2]);
}

void MtlFile::add_Ks(std::stringstream &st) {
	float elem[3];
	int i = 0;
	for (string str; getline(st, str, ' '); ) {
		if (!isNumber(str))
			return this->setError();
		elem[i] = stof(str);
		i++;
	}
	if (i != 3)
		return this->setError();
	this->newmtl.back().add_Ks(elem[0], elem[1], elem[2]);
}

void MtlFile::add_Ns(std::stringstream &st) {
	float elem;
	int i = 0;
	for (string str; getline(st, str, ' '); ) {
		if (!isNumber(str))
			return this->setError();
		elem = stof(str);
		i++;
	}
	if (i != 1)
		return this->setError();
	this->newmtl.back().add_Ns(elem);
}

void MtlFile::add_Tr(std::stringstream &st) {
	float elem;
	int i = 0;
	for (string str; getline(st, str, ' '); ) {
		if (!isNumber(str))
			return this->setError();
		elem = stof(str);
		i++;
	}
	if (i != 1)
		return this->setError();
	this->newmtl.back().add_Tr(elem);
}

void MtlFile::add_d(std::stringstream &st) {
	float elem;
	int i = 0;
	for (string str; getline(st, str, ' '); ) {
		if (!isNumber(str))
			return this->setError();
		elem = stof(str);
		i++;
	}
	if (i != 1)
		return this->setError();
	this->newmtl.back().add_Tr(1 - elem);
}

void MtlFile::add_Tf(std::stringstream &st) {
	float elem[3];
	int i = 0;
	for (string str; getline(st, str, ' '); ) {
		if (!isNumber(str))
			return this->setError();
		elem[i] = stof(str);
		i++;
	}
	if (i != 3)
		return this->setError();
	this->newmtl.back().add_Tf(elem[0], elem[1], elem[2]);
}

void MtlFile::add_illum(std::stringstream &st) {
	uint elem;
	int i = 0;
	for (string str; getline(st, str, ' '); ) {
		if (!isNumber(str))
			return this->setError();
		elem = stof(str);
		i++;
	}
	if (i != 1)
		return this->setError();
	this->newmtl.back().add_illum(elem);
}

void MtlFile::add_Ni(std::stringstream &st) {
	float elem;
	int i = 0;
	for (string str; getline(st, str, ' '); ) {
		if (!isNumber(str))
			return this->setError();
		elem = stof(str);
		i++;
	}
	if (i != 1)
		return this->setError();
	this->newmtl.back().add_Ni(elem);
}

void MtlFile::add_map_Ka(std::stringstream &st) {
	string elem;
	int i = 0;
	for (string str; getline(st, str, ' '); ) {
		elem = str;
		i++;
	}
	if (i != 1)
		return this->setError();
	this->newmtl.back().add_map_Ka(elem);
}

void MtlFile::add_map_Kd(std::stringstream &st) {
	string elem;
	int i = 0;
	for (string str; getline(st, str, ' '); ) {
		elem = str;
		i++;
	}
	if (i != 1)
		return this->setError();
	this->newmtl.back().add_map_Kd(elem);
}

void MtlFile::add_map_Ks(std::stringstream &st) {
	string elem;
	int i = 0;
	for (string str; getline(st, str, ' '); ) {
		elem = str;
		i++;
	}
	if (i != 1)
		return this->setError();
	this->newmtl.back().add_map_Ks(elem);
}

void MtlFile::add_map_Ns(std::stringstream &st) {
	string elem;
	int i = 0;
	for (string str; getline(st, str, ' '); ) {
		elem = str;
		i++;
	}
	if (i != 1)
		return this->setError();
	this->newmtl.back().add_map_Ns(elem);
}

void MtlFile::add_map_d(std::stringstream &st) {
	string elem;
	int i = 0;
	for (string str; getline(st, str, ' '); ) {
		elem = str;
		i++;
	}
	if (i != 1)
		return this->setError();
	this->newmtl.back().add_map_d(elem);
}

void MtlFile::add_map_bump(std::stringstream &st) {
	string elem;
	int i = 0;
	for (string str; getline(st, str, ' '); ) {
		elem = str;
		i++;
	}
	if (i != 1)
		return this->setError();
	this->newmtl.back().add_map_bump(elem);
}

void MtlFile::add_bump(std::stringstream &st) {
	string elem;
	int i = 0;
	for (string str; getline(st, str, ' '); ) {
		elem = str;
		i++;
	}
	if (i != 1)
		return this->setError();
	this->newmtl.back().add_bump(elem);
}

void MtlFile::add_disp(std::stringstream &st) {
	string elem;
	int i = 0;
	for (string str; getline(st, str, ' '); ) {
		elem = str;
		i++;
	}
	if (i != 1)
		return this->setError();
	this->newmtl.back().add_disp(elem);
}

void MtlFile::add_decal(std::stringstream &st) {
	string elem;
	int i = 0;
	for (string str; getline(st, str, ' '); ) {
		elem = str;
		i++;
	}
	if (i != 1)
		return this->setError();
	this->newmtl.back().add_decal(elem);
}

void MtlFile::setError() {
	this->error = true;
}

void MtlFile::print() {
	for (vector<Newmtl>::iterator it = this->newmtl.begin(); it != this->newmtl.end(); it++) {
		it->print();
	}
}

bool MtlFile::is_open() {
	return !this->error;
}

vector<Material> MtlFile::getMaterial() {
	vector<Material> res;
	for (vector<Newmtl>::iterator it = this->newmtl.begin(); it != this->newmtl.end(); it++)
		res.push_back(it->getMaterial());
	return res;
}






static bool isNumber(const string &s)
{
	bool dot = false;
    for (size_t i = 0; i < s.length(); i++) {
		if (i == 0 && s[i] == '-')
			continue;
		if (s[i] == '.' && dot == false) {
			dot = true;
			continue;
		}
        if (isdigit(s[i]) == 0) {
            return false;
		}
    }
    return true;
}

static bool matchMtl(const string &s) {
	if (s.length() < 5)
		return false;
	if (s[s.length() - 4] == '.' 
		&& s[s.length() - 3] == 'm' 
		&& s[s.length() - 2] == 't' 
		&& s[s.length() - 1] == 'l')
		return true;
	return false;
}