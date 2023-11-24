#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <cmath>

#include "pch.hpp"

class Camera {

	private:
		glm::mat4 Projection;

		glm::mat4 View;
		glm::vec3 Position;
		glm::vec3 LookAt;
		glm::vec3 UP;

		int width;
		int height;

		float horizontalAngle;
		float verticalAngle;
		float FoV;
		float speed;
		float mouseSpeed;

		bool frontState;
		bool backState;
		bool leftState;
		bool rightState;
		bool upState;
		bool downState;

	public:
		Camera() = delete;
		Camera(int width, int height);

		glm::mat4 getView();
		glm::mat4 getProjection();

		void setFront(bool state);
		void setBack(bool state);
		void setLeft(bool state);
		void setRight(bool state);
		void setUp(bool state);
		void setDown(bool state);
		void changeFov(int num);
		void resetFov();

		glm::vec3 getPosition();

		void render(double deltaTime, double xpos, double ypos);
};

#endif