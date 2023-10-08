#include "Program.hpp"

using namespace std;

Program::Program() {
	this->types[0] = GL_VERTEX_SHADER;
	this->types[1] = GL_TESS_CONTROL_SHADER;
	this->types[2] = GL_TESS_EVALUATION_SHADER;
	this->types[3] = GL_GEOMETRY_SHADER;
	this->types[4] = GL_FRAGMENT_SHADER;
	this->types[5] = GL_COMPUTE_SHADER;
	this->programId = 0;
	for (int i = 0; i < 6; i++)
		this->shaderId[i] = 0;
}

Program::~Program() {
	glDeleteProgram(this->programId);
}

bool Program::loadShader(GLenum type, std::string const &filename) {
	int i = 0;
	for (; i < 6; i++) {
		if (this->types[i] == type)
			break;
	}
	if (i > 6) {
		cout << type << " is worng shader type" << endl;
		return false;
	}

	fstream file;
	file.open(filename);
	if (!file.is_open()) {
		cerr << filename << " not open" << endl;
		return false;
	}
	string str;
	file.seekg(0,ios::end);
	size_t size = file.tellg();
	str.resize(size);
	file.seekg(0, ios::beg);
	file.read(&str[0], size);
	file.close();

	// create shader object
	GLuint id = glCreateShader(type);
	const GLchar *source = str.c_str();
	const GLint length = str.length();
	glShaderSource(id, 1, &source, &length);

	glCompileShader(id);

	// check compile done
	GLint check;
	glGetShaderiv(id, GL_COMPILE_STATUS, &check);
	if (check == GL_FALSE) {
		glDeleteShader(id);
		cerr << filename << " not compiled" << endl;
		return false;
	};

	this->shaderId[i] = id;
	return true;
}

void Program::deleteShader(GLenum type) {
	int i = 0;
	for (; i < 6; i++) {
		if (this->types[i] == type)
			break;
	}
	if (i > 6) {
		cout << type << " is worng shader type" << endl;
		return ;
	}
	if (this->shaderId[i] == 0)
		return ;
	glDeleteShader(this->shaderId[i]);
	this->shaderId[i] = 0;
}

void Program::clearShader() {
	for (int i = 0; i < 6; i++) {
		if (this->shaderId[i]) {
			glDeleteShader(this->shaderId[i]);
			this->shaderId[i] = 0;
		}
	}
}

bool Program::loadProgram() {
	GLuint id = glCreateProgram();
	// put shader in program
	for (int i = 0; i < 6; i++) {
		if (this->shaderId[i])
			glAttachShader(id, this->shaderId[i]);
	}
	// link program
	glLinkProgram(id);

	for (int i = 0; i < 6; i++) {
		if (this->shaderId[i])
			glDetachShader(id, this->shaderId[i]);
	}

	// check link done
	GLint check;
	glGetProgramiv(id, GL_LINK_STATUS, &check);
	if (check == GL_FALSE) {
		glDeleteProgram(id);
		cout << "Program does not linked" << endl;
		return false;
	}

	this->clearShader();

	this->programId = id;
	return true;
}

GLuint Program::id() {
	return this->programId;
}

bool Program::is_set() {
	if (this->programId)
		return true;
	return false;
}

void Program::use() {
	glUseProgram(this->programId);
}