#include "Camera.hpp"

Camera::Camera(int width, int height) {
	this->FoV = 45.0f;
	this->width = width;
	this->height = height;
	this->Projection = glm::perspective(glm::radians(this->FoV), width / static_cast<float>(height), 0.1f, 100.0f);
	this->Position = glm::vec3(-20, 20, 20);
	this->LookAt = glm::vec3(1, -1, 1);
	this->UP = glm::vec3(0, 1, 0);
	this->horizontalAngle = 0;
	this->horizontalAngle = 3.14 * 0.75;
	this->verticalAngle = 3.14 * -0.2;
	this->speed = 10.0f;
	this->mouseSpeed = 0.002f;

	this->frontState = false;
	this->backState = false;
	this->leftState = false;
	this->rightState = false;
	this->upState = false;
	this->downState = false;
}

glm::mat4 Camera::getView() {
	return this->View;
}

glm::mat4 Camera::getProjection() {
	return this->Projection;
}

void Camera::setFront(bool state) {
	this->frontState = state;
}

void Camera::setBack(bool state) {
	this->backState = state;
}

void Camera::setLeft(bool state) {
	this->leftState = state;
}

void Camera::setRight(bool state) {
	this->rightState = state;
}

void Camera::setUp(bool state) {
	this->upState = state;
}

void Camera::setDown(bool state) {
	this->downState = state;
}

void Camera::changeFov(int num) {
	this->FoV += num;
	if (this->FoV > 120)
		this->FoV = 120;
	else if (this->FoV < 15)
		this->FoV = 15;
}
void Camera::resetFov() {
	this->FoV = 45;
}

glm::vec3 Camera::getPosition() {
	return this->Position;
}

float Camera::getLookAt() {
	return this->horizontalAngle;
}


void Camera::render(double deltaTime, double xpos, double ypos) {
	// this->Projection = perspective(glm::radians(this->FoV), width, height, 0.1f, 100.0f);
	this->Projection = glm::perspective(glm::radians(this->FoV), width / static_cast<float>(height), 0.1f, 100.0f);
	// Compute time difference between current and last frame

	// Compute new orientation
	this->horizontalAngle += mouseSpeed * float(this->width/2 - xpos );
	if (this->horizontalAngle > glm::radians(360.f) || this->horizontalAngle < glm::radians(360.f) * -1)
		this->horizontalAngle = 0;
	this->verticalAngle   += mouseSpeed * float(this->height/2 - ypos );
	if (this->verticalAngle > glm::radians(90.f))
		this->verticalAngle = glm::radians(90.f);
	else if (this->verticalAngle < glm::radians(90.f) * -1)
		this->verticalAngle = glm::radians(90.f) * -1;

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 direction(
		glm::cos(verticalAngle) * glm::sin(horizontalAngle), 
		glm::sin(verticalAngle),
		glm::cos(verticalAngle) * glm::cos(horizontalAngle)
	);
	
	// Right vector
	glm::vec3 right = glm::vec3(
		glm::sin(horizontalAngle - glm::radians(90.f)), 
		0,
		glm::cos(horizontalAngle - glm::radians(90.f))
	);

	glm::vec3 front(
		glm::sin(horizontalAngle),
		0,
		glm::cos(horizontalAngle)
	);
	
	// Up vector
	this->UP = glm::cross(right, direction);

	// Move front
	if (this->frontState)
		// this->Position += glm::vec3(direction.x, 0, direction.z) * deltaTime * speed;
		this->Position += front * static_cast<float>(deltaTime) * speed;
	// Move back
	if (this->backState)
		// this->Position -= glm::vec3(direction.x, 0, direction.z) * deltaTime * speed;
		this->Position -= front * static_cast<float>(deltaTime) * speed;
	// Strafe right
	if (this->rightState)
		this->Position += right * static_cast<float>(deltaTime) * speed;
	// Strafe left
	if (this->leftState)
		this->Position -= right * static_cast<float>(deltaTime) * speed;
	// Move up
	if (this->upState)
		this->Position += glm::vec3(0, 0.015, 0) * speed;
	// Move down
	if (this->downState)
		this->Position -= glm::vec3(0, 0.015, 0) * speed;

	glm::vec3 center = this->Position + direction;

	this->View = glm::lookAt(
		this->Position,
		center,
		this->UP
	);
}