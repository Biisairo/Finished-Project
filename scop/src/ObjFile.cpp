#include "ObjFile.hpp"

using namespace std;

Index::Index(string name, int index) : name(name), index(index) {}

ObjFile::ObjFile(): error(true) {}

ObjFile::ObjFile(std::string const &filename) : filename(filename), error(false) {
	if (!matchObj(this->filename))
		this->setError();
	this->o.push_back(Index("default", 0));
	this->g.push_back(Index("default", 0));

	this->setObj();
	if (this->error)
		cout << "Fail to set obj file" << endl;
};

ObjFile::~ObjFile() {};

void ObjFile::setObj() {
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
		
		if (elem == "v")
			this->add_v(st);
		else if (elem == "vt")
			this->add_vt(st);
		else if (elem == "vn")
			this->add_vn(st);
		else if (elem == "vp")
			this->add_vp(st);
		else if (elem == "f")
			this->add_f(st);
		else if (elem == "l")
			this->add_l(st);
		else if (elem == "usemtl")
			this->add_usemtl(st);
		else if (elem == "mtllib")
			this->add_mtllib(st);
		else if (elem == "o")
			this->add_o(st);
		else if (elem == "g")
			this->add_g(st);
		else if (elem == "s")
			this->add_s(st);
		else if (elem[0] == '#')
			continue;
		else {
			file.close();
			return this->setError();
		}
	}

	file.close();

	this->setV();
	this->setVT();
	this->setVN();
}

void ObjFile::add_v (stringstream &st) {
	float elem[4];
	elem[3] = 1.0;
	int i = 0;
	for(string str; getline(st, str, ' '); ) {
		if (!isNumber(str))
			return this->setError();
		elem[i] = stof(str);
		i++;
	}
	if (i != 3 && i != 4)
		return this->setError();
	else
		this->v.push_back(glm::vec4(elem[0], elem[1], elem[2], elem[3]));
}

void ObjFile::add_vt (stringstream &st) {
	float elem[3];
	elem[1] = 0;
	elem[2] = 0;
	int i = 0;
	for(string str; getline(st, str, ' '); ) {
		if (!isNumber(str))
			return this->setError();
		elem[i] = stof(str);
		if (elem[i] < 0 || elem[i] > 1)
			return this->setError();
		i++;
	}
	if (i != 1 && i != 2 && i != 3)
		return this->setError();
	else
		this->vt.push_back(glm::vec3(elem[0], elem[1], elem[2]));
}

void ObjFile::add_vn (stringstream &st) {
	float elem[3];
	int i = 0;
	for(string str; getline(st, str, ' '); ) {
		if (!isNumber(str))
			return this->setError();
		elem[i] = stof(str);
		i++;
	}
	if (i != 3)
		return this->setError();
	else
		this->vn.push_back(glm::vec3(elem[0], elem[1], elem[2]));
}

void ObjFile::add_vp (stringstream &st) {
	float elem[3];
	elem[1] = 0;
	elem[2] = 0;
	int i = 0;
	for(string str; getline(st, str, ' '); ) {
		if (!isNumber(str))
			return this->setError();
		elem[i] = stof(str);
		i++;
	}
	if (i != 1 && i != 2 && i != 3)
		return this->setError();
	else
		this->vp.push_back(glm::vec3(elem[0], elem[1], elem[2]));
}

void ObjFile::add_f (stringstream &st) {
	vector<FElem> tmp;

	for (string str; getline(st, str, ' '); ) {
		FElem tmpElem;

		stringstream elem(str);
		int i = 0;
		for (string v; getline(elem, v, '/'); ) {
			if (v.empty() && (i != 0 || i != 1 || i != 2))
				return this->setError();
			if (v.empty())
				v = "0";
			else if (!isNumber(v)) 
				return this->setError();
			
			if (i == 0)
				tmpElem.v = stoi(v);
			else if (i == 1)
				tmpElem.vt = stoi(v);
			else if (i == 2)
				tmpElem.vn = stoi(v);
			else 
				return this->setError();
			i++;
		}
		tmp.push_back(tmpElem);
	}
	for (int i = 0; i < tmp.size()-2; i++) {
		F ff;
    	ff.elem[0] = tmp[0];
		ff.elem[1] = tmp[i+1];
		ff.elem[2] = tmp[i+2];
		this->f.push_back(ff);
	}
}

void ObjFile::add_l (stringstream &st) {
	L tmp;

	for (string str; getline(st, str, ' '); ) {
		if (!isNumber(str))
			return this->setError();
		tmp.elem.push_back(stoi(str));
	}
	this->l.push_back(tmp);
}

void ObjFile::add_usemtl (stringstream &st) {
	string elem;
	getline(st, elem, ' ');
	if (elem.empty())
		return this->setError();
	this->usemtl.push_back(Index(elem, this->f.size()));
	if (getline(st, elem, ' '))
		return this->setError();
}

void ObjFile::add_mtllib (stringstream &st) {
	string elem;
	getline(st, elem, ' ');
	if (elem.empty())
		return this->setError();
	this->mtllib = elem;
	if (getline(st, elem, ' '))
		return this->setError();
}

void ObjFile::add_o (stringstream &st) {
	string elem;
	getline(st, elem, ' ');
	if (elem.empty())
		return this->setError();
	this->o.push_back(Index(elem, this->f.size()));
	if (getline(st, elem, ' '))
		return this->setError();
}

void ObjFile::add_g (stringstream &st) {
	string elem;
	getline(st, elem, ' ');
	if (elem.empty())
		return this->setError();
	this->g.push_back(Index(elem, this->f.size()));
	if (getline(st, elem, ' '))
		return this->setError();
}

void ObjFile::add_s (stringstream &st) {
	string elem;
	getline(st, elem, ' ');
	if (elem.empty())
		return this->setError();
	this->s.push_back(Index(elem, this->f.size()));
	if (getline(st, elem, ' '))
		return this->setError();
}

bool ObjFile::is_open() {
	return !this->error;
}

void ObjFile::genVT() {
	// get boundary
	float minX, maxX, minY, maxY, minZ, maxZ;
	minX = numeric_limits<float>::max();
	minY = numeric_limits<float>::max();
	minZ = numeric_limits<float>::max();
	maxX = numeric_limits<float>::min();
	maxY = numeric_limits<float>::min();
	maxZ = numeric_limits<float>::min();
	for (vector<glm::vec4>::iterator it = this->v.begin(); it != this->v.end(); it++) {
		minX = min(minX, it->x);
		minY = min(minY, it->y);
		minZ = min(minZ, it->z);
		maxX = max(maxX, it->x);
		maxY = max(maxY, it->y);
		maxZ = max(maxZ, it->z);
	}
	// translate to uv
	vector<glm::vec2> res;
	// resX = x - minX / (maxX - minX)
	float span[3] = {maxX - minX, maxZ - minZ, maxY - minY};
	float min = numeric_limits<float>::max();
	int minidx = -1;
	for (int i = 0; i < 3; i++) {
		if (min > span[i]) {
			min = span[i];
			minidx = i;
		}
	}
	int uv[2];
	float minU, maxU, minV, maxV;
	if (minidx == 0) {
		uv[0] = 2;
		uv[1] = 1;
		minU = minZ;
		maxU = maxZ;
		minV = minY;
		maxV = maxY;
	} else if (minidx == 1) {
		uv[0] = 0;
		uv[1] = 1;
		minU = minX;
		maxU = maxX;
		minV = minY;
		maxV = maxY;
	} else if (minidx == 2) {
		uv[0] = 0;
		uv[1] = 2;
		minU = minX;
		maxU = maxX;
		minV = minZ;
		maxV = maxZ;
	}

	for (vector<F>::iterator it = this->f.begin(); it != this->f.end(); it++) {
		for (int i = 0; i < 3; i++) {
			float u = this->v[it->elem[i].v - 1][uv[0]];
			float v = this->v[it->elem[i].v - 1][uv[1]];
			float resU = (u - minU) / (maxU - minU);
			float resV = (v - minV) / (maxV - minV);
			res.push_back(glm::vec2(resU, resV));
		}
	}
	this->vtF = res;
}

void ObjFile::genVN() {
	vector<glm::vec3> tmp;
	tmp.resize(this->v.size());
	for (vector<F>::iterator it = this->f.begin(); it != this->f.end(); it++) {
		glm::vec3 a(this->v[it->elem[0].v - 1]);
		glm::vec3 b(this->v[it->elem[1].v - 1]);
		glm::vec3 c(this->v[it->elem[2].v - 1]);
		glm::vec3 A(a.x, a.y, a.z);
		glm::vec3 B(b.x, b.y, b.z);
		glm::vec3 C(c.x, c.y, c.z);
		glm::vec3 normal = glm::normalize(cross(A - B, A - C));

		tmp[it->elem[0].v - 1] += normal;
		tmp[it->elem[1].v - 1] += normal;
		tmp[it->elem[2].v - 1] += normal;
	}
	for (vector<glm::vec3>::iterator it = tmp.begin(); it != tmp.end(); it++)
		*it = glm::normalize(*it);
	vector<glm::vec3> res;
	for (vector<F>::iterator it = this->f.begin(); it != this->f.end(); it++) {
		for (int i = 0; i < 3; i++) 
			res.push_back(tmp[it->elem[i].v - 1]);
	}
	this->vnF = res;
	// for (int i = 0; i < res.size(); i++)
	// 	std::cout << res[i].x << " " << res[i].y << " " << res[i].z << std::endl;
}

void ObjFile::setV() {
	if (this->error)
		return ;
	this->vF.resize(this->f.size() * 3);
	for (size_t i = 0; i < this->f.size(); i++) {
		try {
			this->vF[i * 3] = (this->v.at(this->f[i].elem[0].v - 1));
			this->vF[i * 3 + 1] = (this->v.at(this->f[i].elem[1].v - 1));
			this->vF[i * 3 + 2] = (this->v.at(this->f[i].elem[2].v - 1));
		} catch (exception err) {
			return this->setError();
		}
	}
}

void ObjFile::setVT() {
	if (this->error)
		return ;
	this->vtF.resize(this->f.size() * 3);
	this->genVT();
	for (size_t i = 0; i < this->f.size(); i++) {
		for (int j = 0; j < 3; j++) {
			if (this->vt.size() > this->f[i].elem[j].vt - 1 && this->f[i].elem[j].vt != 0)
				this->vtF[i * 3 + j] = glm::vec2(this->vt.at(this->f[i].elem[j].vt - 1).x,
													this->vt.at(this->f[i].elem[j].vt - 1).y);
		}
	}
}

void ObjFile::setVN() {
	if (this->error)
		return ;
	this->vnF.resize(this->f.size() * 3);
	this->genVN();
	for (size_t i = 0; i < this->f.size(); i++) {
		for (int j = 0; j < 3; j++) {
			if (this->vn.size() > this->f[i].elem[j].vn - 1 && this->f[i].elem[j].vn != 0)
				this->vnF[i * 3 + j] = glm::vec3(this->vn[this->f[i].elem[j].vn - 1]);
		}
	}
}

vector<glm::vec4> ObjFile::getV() {
	return this->vF;
}

vector<glm::vec2> ObjFile::getVT() {
	vector<glm::vec2> res;
	for (vector<glm::vec2>::iterator it = this->vtF.begin(); it != this->vtF.end(); it++)
		res.push_back(glm::vec2(it->x, 1 - it->y));
	return res;
}

vector<glm::vec3> ObjFile::getVN() {
	return this->vnF;
}

string ObjFile::getMtllib() {
	return this->mtllib;
}

void ObjFile::setError() {
	this->error = true;
}

void ObjFile::print() {
	if (this->error) {
		cout << "=====================================================================" << endl;
		cout << "ERROR===ERROR===ERROR===ERROR===ERROR===ERROR===ERROR===ERROR===ERROR" << endl;
		cout << "=====================================================================" << endl;
		return ;	
	}

	cout << "=====================================================================" << endl;
	cout << "mtllib===============================================================\n" << endl;
	cout << "mtllib name : " << this->mtllib << endl;
	cout << "\nv     ===============================================================\n" << endl;
	for (size_t i = 0; i < this->v.size(); i++)
		cout << "index " << i + 1
				<< "\n	x : " << this->v[i].x << " "
				<< "\n	y : " << this->v[i].y << " "
				<< "\n	z : " << this->v[i].z << " "
				<< "\n	w : " << this->v[i].w << endl;
	cout << "\nvt    ===============================================================\n" << endl;
	for (size_t i = 0; i < this->vt.size(); i++)
		cout << "index " << i + 1
				<< "\n	u : " << this->vt[i].x << " "
				<< "\n	v : " << this->vt[i].y << " "
				<< "\n	w : " << this->vt[i].z << endl;
	cout << "\nvn    ===============================================================\n" << endl;
	for (size_t i = 0; i < this->vn.size(); i++)
		cout << "index " << i + 1
				<< "\n	x : " << this->vn[i].x << " "
				<< "\n	y : " << this->vn[i].y << " "
				<< "\n	z : " << this->vn[i].z << endl;
	cout << "\nvp    ===============================================================\n" << endl;
	for (size_t i = 0; i < this->vp.size(); i++)
		cout << "index " << i + 1
				<< "\n	u : " << this->vp[i].x << " "
				<< "\n	v : " << this->vp[i].y << " "
				<< "\n	w : " << this->vp[i].z << endl;
	cout << "\nf     ===============================================================\n" << endl;
	for (size_t i = 0; i < this->f.size(); i++) {
		cout << "index " << i << endl;
		for (int j = 0; j < 3; j++) {
			cout << "	v : " << this->f[i].elem[j].v
				<< " vt : " << this->f[i].elem[j].vt
				<< " vn : " << this->f[i].elem[j].vn << endl;
		}
	}
	cout << "\nl     ===============================================================\n" << endl;
	for (size_t i = 0; i < this->l.size(); i++) {
		cout << "index " << i << endl << "	";
		for (auto it = this->l[i].elem.begin(); it != this->l[i].elem.end(); it++) {
			cout << *it << " ";
		}
	}
	cout << "\nusemtl===============================================================\n" << endl;
	for (size_t i = 0; i < this->usemtl.size(); i++) {
		cout << "index " << i << endl
			<< "	mtl name : " << this->usemtl[i].name
			<< "\n	index start : " << this->usemtl[i].index << endl;
	}
	cout << "\ns     ===============================================================\n" << endl;
	for (size_t i = 0; i < this->s.size(); i++) {
		cout << "index " << i << endl
			<< "	s name : " << this->s[i].name
			<< "\n	index start : " << this->s[i].index << endl;
	}
	cout << "\no     ===============================================================\n" << endl;
	for (size_t i = 0; i < this->o.size(); i++) {
		cout << "index " << i << endl
			<< "	object name : " << this->o[i].name
			<< "\n	index start : " << this->o[i].index << endl;
	}
	cout << "\ng     ===============================================================\n" << endl;
	for (size_t i = 0; i < this->g.size(); i++) {
		cout << "index " << i << endl
			<< "	g name : " << this->g[i].name
			<< "\n	index start : " << this->g[i].index << endl;
	}
	cout << "\n=====================================================================" << endl;
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

static bool matchObj(const string &s) {
	if (s.length() < 5)
		return false;
	if (s[s.length() - 4] == '.' 
		&& s[s.length() - 3] == 'o' 
		&& s[s.length() - 2] == 'b' 
		&& s[s.length() - 1] == 'j')
		return true;
	return false;
}