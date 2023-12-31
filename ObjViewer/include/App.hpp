#ifndef APP_HPP
#define APP_HPP

#include "pch.hpp"

#include "Camera.hpp"
#include "Object.hpp"
#include "Program.hpp"
#include "texture.hpp"

#define STOP 0
#define CW 1
#define CCW 2

class App{

	private:
		GLFWwindow			*window;
		int					width;
		int					height;

		Camera camera;

		std::vector<Object>	objects;

		Program				program;
		std::vector<GLuint>	texture;

		std::map<std::string, GLuint> uniform;

		GLuint ModelID;
		GLuint ViewID;
		GLuint ProjectionID;
		GLuint TextureID;

		double lastTime;

		bool is_error;

		int textureIdx;
		int rotX;
		int rotY;
		int rotZ;

		bool is_textrue;
		bool is_fill;

	public:
		App();
		App(std::string const &title, int width, int height);
		~App();

		void	setError();
		bool	isError();

		void	init(std::string const &title);

		void	setProgram(std::string const &vs, std::string const &fs);
		GLuint	getProgram();

		void	addTexture(std::string const &filename);
		void	deleteTexture(size_t idx);

		void	addObject(std::string const &filename);
		void	deleteObject(size_t idx);

		void	setLight();
		void	getUniformLocation(std::string s);
		GLuint	getUniformID(std::string s);

		void	renderCamera(double deltaTime);

		float	transitionTexture(double delta);
		void	setTransition();

		
		void	loop();

		// for callback
		void	setFront(bool status);
		void	setBack(bool status);
		void	setLeft(bool status);
		void	setRight(bool status);
		void	setUp(bool status);
		void	setDown(bool status);
		void	changeFov(int num);
		void	resetFov();

		void	changeTexture();
		void	setRotX(int state);
		void	setRotY(int state);
		void	setRotZ(int state);
		void	rotate(Object &obj, double delta);

		void	changePolyMode();
		void	toLine();
		void	toFace();
		// for callback

		void setBool(std::string const &name, bool value);
		void setInt(std::string const &name, int value);
		void setFloat(std::string const &name, float value);
		void setVec2(std::string const &name, glm::vec2 value);
		void setVec2(std::string const &name, float x, float y);
		void setVec3(std::string const &name, glm::vec3 value);
		void setVec3(std::string const &name, float x, float y, float z);
		void setVec4(std::string const &name, glm::vec4 value);
		void setVec4(std::string const &name, float x, float y, float z, float w);
		void setMat3(std::string const &name, glm::mat3 &mat);
		void setMat4(std::string const &name, glm::mat4 &mat);
		void setMaterial(Material &material);
};


static void	keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
static void	mouseCallback(GLFWwindow* window, int button, int action, int mods);
static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
static void errorCallback(int error, const char *des);

static bool endsWith(std::string const &str, std::string const &suffix);

#endif