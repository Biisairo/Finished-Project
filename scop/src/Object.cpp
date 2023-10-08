#include "Object.hpp"

Object::Object(): is_error(true) {}

Object::Object(std::string const &filename): objFile(ObjFile(filename)), is_error(false) {
	if (!this->objFile.is_open()) {
		this->is_error = true;
		return;
	}
	if (this->objFile.getMtllib().empty()) {
		std::cout << "mtllib not exist" << std::endl;
		std::cout << "use default mtl file" << std::endl;
		this->mtlFile.setFilename("map/default.mtl");
	} else
		this->mtlFile.setFilename(this->objFile.getMtllib());
	if (!this->mtlFile.is_open()) {
		std::cout << "use default mtl file" << std::endl;
		this->mtlFile.setFilename("map/default.mtl");
	}
	this->model = glm::mat4(1.f);
	this->vertices = this->objFile.getV();
	this->verticesTexture = this->objFile.getVT();
	this->verticesNormal = this->objFile.getVN();
	this->genColor();
	this->putVerticesArray();
}

Object::~Object() {}

void Object::destroy() {
	glDeleteBuffers(1, &this->VERTEX);
	glDeleteBuffers(1, &this->VERTEXTEXTURE);
	glDeleteBuffers(1, &this->VERTEXNORMAL);
	glDeleteBuffers(1, &this->VERTEXCOLOR);
	glDeleteVertexArrays(1, &this->VAO);
}

glm::mat4	Object::getModel() {
	return this->model;
}

std::vector<glm::vec4>	Object::getVertices() const {
	return this->vertices;
}

std::vector<glm::vec2>	Object::getVerticesTexture() const {
	return this->verticesTexture;
}

std::vector<glm::vec3>	Object::getVerticesNormal() const {
	return this->verticesNormal;
}

std::vector<Material> Object::getMaterial() {
	return this->mtlFile.getMaterial();
}

void Object::putVerticesArray() {
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VERTEX);
	glGenBuffers(1, &this->VERTEXTEXTURE);
	glGenBuffers(1, &this->VERTEXNORMAL);
	glGenBuffers(1, &this->VERTEXCOLOR);

	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, this->VERTEX);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec4), vertices.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,
		4,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

	glBindBuffer(GL_ARRAY_BUFFER, this->VERTEXTEXTURE);
	glEnableVertexAttribArray(1);
	glBufferData(GL_ARRAY_BUFFER, verticesTexture.size() * sizeof(glm::vec2), verticesTexture.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(
		1,
		2,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

	glBindBuffer(GL_ARRAY_BUFFER, VERTEXNORMAL);
	glEnableVertexAttribArray(2);
	glBufferData(GL_ARRAY_BUFFER, verticesNormal.size() * sizeof(glm::vec3), verticesNormal.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(
		2,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

	glBindBuffer(GL_ARRAY_BUFFER, VERTEXCOLOR);
	glEnableVertexAttribArray(3);
	glBufferData(GL_ARRAY_BUFFER, verticesColor.size() * sizeof(glm::vec3), verticesColor.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(
		3,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

	glBindVertexArray(0);
}

glm::vec3 Object::center() {
	float minX, maxX, minY, maxY, minZ, maxZ;
	minX = std::numeric_limits<float>::max();
	minY = std::numeric_limits<float>::max();
	minZ = std::numeric_limits<float>::max();
	maxX = std::numeric_limits<float>::min();
	maxY = std::numeric_limits<float>::min();
	maxZ = std::numeric_limits<float>::min();
	for (std::vector<glm::vec4>::iterator it = this->vertices.begin(); it != this->vertices.end(); it++) {
		minX = std::min(minX, it->x);
		minY = std::min(minY, it->y);
		minZ = std::min(minZ, it->z);
		maxX = std::max(maxX, it->x);
		maxY = std::max(maxY, it->y);
		maxZ = std::max(maxZ, it->z);
	}
	return glm::vec3((maxX + minX) / 2, (maxY + minY) / 2, (maxZ + minZ) / 2);
}

void Object::genColor() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<float> dis(0, 255);

	std::vector<glm::vec3> res;
	uint face = this->vertices.size() / 3;
	uint div = face / 3;
	for (int i = 0; i < this->vertices.size(); i++) {
		res.push_back(glm::vec3(dis(gen), dis(gen), dis(gen)));
	}
	this->verticesColor = res;
}


void Object::rotateX(float degree) {
	glm::vec3 center = this->center();
	glm::vec3 revCenter = center * -1.f;

	glm::mat4 toCenter = glm::translate(glm::mat4(1), revCenter);
	glm::mat4 rot = glm::rotate(glm::mat4(1), degree, {1, 0, 0});
	glm::mat4 toOrigin = glm::translate(glm::mat4(1), center);
	this->model = toOrigin * rot * toCenter * this->model;
}

void Object::rotateY(float degree) {
	glm::vec3 center = this->center();
	glm::vec3 revCenter = center * -1.f;

	glm::mat4 toCenter = glm::translate(glm::mat4(1), revCenter);
	glm::mat4 rot = glm::rotate(glm::mat4(1), degree, {0, 1, 0});
	glm::mat4 toOrigin = glm::translate(glm::mat4(1), center);
	this->model = toOrigin * rot * toCenter * this->model;
}

void Object::rotateZ(float degree) {
	glm::vec3 center = this->center();
	glm::vec3 revCenter = center * -1.f;

	glm::mat4 toCenter = glm::translate(glm::mat4(1), revCenter);
	glm::mat4 rot = glm::rotate(glm::mat4(1), degree, {0, 0, 1});
	glm::mat4 toOrigin = glm::translate(glm::mat4(1), center);
	this->model = toOrigin * rot * toCenter * this->model;
}

void Object::draw() {
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	glBindVertexArray(0);
}

void Object::printObj() {
	this->objFile.print();
}

bool Object::isError() {
	return this->is_error;
}