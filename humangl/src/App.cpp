#include "App.hpp"

App::App(): camera(500, 500), is_error(false) {
	this->width = 500;
	this->height = 500;
	this->init("tmp");

	this->lastTime = glfwGetTime();

	this->textureIdx = 0;
	this->rotX = false;
	this->rotY = false;
	this->rotZ = false;

	this->is_textrue = false;
	this->is_fill = true;

	this->frame = 0;
	this->frameTime = glfwGetTime();
}

App::App(std::string const &title, int width, int height): camera(width, height), is_error(false) {
	this->width = width;
	this->height = height;
	this->init(title);

	this->lastTime = glfwGetTime();

	this->textureIdx = 0;
	this->rotX = false;
	this->rotY = false;
	this->rotZ = false;

	this->is_textrue = false;
	this->is_fill = true;

	this->frame = 0;
	this->frameTime = glfwGetTime();
}

void App::setfile(std::string const &asf, std::string const &amc) {
	this->sk.setASF(asf);
	this->sk.setAMC(amc);
}

App::~App() {
	for (std::vector<GLuint>::iterator it = this->texture.begin(); it != this->texture.end(); it++)
		glDeleteTextures(1, &(*it));
	glfwDestroyWindow(this->window);
	glfwTerminate();
}

void App::setError() {
	this->is_error = true;
}

bool App::isError() {
	return this->is_error;
}


void App::init(std::string const &title) {
	glfwSetErrorCallback(errorCallback);

	if (!glfwInit()) {
		std::cout << "Fail to init glfw" << std::endl;
		return this->setError();
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif
	this->window = glfwCreateWindow(this->width, this->height, title.c_str(), NULL, NULL);
	if (!this->window) {
		std::cout << "Fail to make window" << std::endl;
		glfwTerminate();
		return this->setError();
	}

	glfwSetWindowUserPointer(this->window, this);

	glfwMakeContextCurrent(this->window);
	glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseCallback);
	glfwSetScrollCallback(window, scrollCallback); 

	// glew 는 context 를 생성한 후 초기화
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cout << "Fail to init glew" << std::endl;
		return this->setError();
	}

	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void App::setProgram(std::string const &vs, std::string const &fs) {
	this->program.loadShader(GL_VERTEX_SHADER, vs);
	this->program.loadShader(GL_FRAGMENT_SHADER, fs);
	this->program.loadProgram();
	if (!this->program.is_set())
		return this->setError();
	else
		this->program.use();
}

GLuint App::getProgram() {
	return this->program.id();
}

void App::addTexture(std::string const &filename) {
	GLuint texture = 0;
	if (endsWith(filename, ".dds") || endsWith(filename, ".DDS"))
		texture = loadDDS(filename);
	else if (endsWith(filename, ".ppm") || endsWith(filename, ".PPM"))
		texture = loadPPM(filename);
	// else
	// 	texture = loadTexture(filename);

	if (texture == 0)
		std::cout << "texture error" << std::endl;
	else
		this->texture.push_back(texture);
}

void App::deleteTexture(size_t idx) {
	this->texture.erase(this->texture.begin() + idx);
}

void App::getUniformLocation(std::string s) {
	GLuint tmp = glGetUniformLocation(this->program.id(), s.c_str());
	this->uniform.insert(std::make_pair(s, tmp));
}

GLuint App::getUniformID(std::string s) {
	return this->uniform.find(s)->second;
}

void	App::renderCamera(double deltaTime) {
	double xpos, ypos;
	glfwGetCursorPos(this->window, &xpos, &ypos);
	glfwSetCursorPos(window, this->width/2, this->height/2);
	this->camera.render(deltaTime, xpos, ypos);
}

float App::transitionTexture(double delta) {
	static double ratio = 0;

	delta *= 100;

	if (this->is_textrue)
		ratio += delta;
	else
		ratio -= delta;
	if (ratio > 100)
		ratio = 100;
	else if (ratio < 0)
		ratio = 0;
	return ratio / 100.f;
}
void App::setTransition() {
	if (this->is_textrue)
		this->is_textrue = false;
	else
		this->is_textrue = true;
}

void App::changePolyMode() {
	if (this->is_fill)
		this->is_fill = false;
	else
		this->is_fill = true;
}
void App::toLine() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
};
void App::toFace() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
};

void App::loop() {
	while(!glfwWindowShouldClose(this->window)) {
		// get delta time
		double time = glfwGetTime();
		double delta = time - this->lastTime;
		this->lastTime = time;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.1, 0.1, 0.1, 1);

		this->renderCamera(delta);
		glm::mat4 view(this->camera.getView());
		glm::mat4 projection(this->camera.getProjection());
		this->setMat4("VIEW", view);
		this->setMat4("PROJECTION", projection);
		glm::mat4 model(1);
		this->setMat4("MODEL", model);
		glm::vec3 pos = this->camera.getPosition();
		this->setVec3("POSITION", pos);

///////////////////////////////////////
		if (this->frame == 0 || glfwGetTime() - this->frameTime > 0.1) {
        	std::stringstream ss;
        	ss << " [" << this->frame / (glfwGetTime() - this->frameTime) << " FPS]";
        	glfwSetWindowTitle(this->window, ss.str().c_str());
			float fps = roundf((this->frame / (glfwGetTime() - this->frameTime)) * 100) / 100.f;
			this->frame = 0;
			this->frameTime = glfwGetTime();
		}
		this->frame++;

		this->sk.setLocal(time);
		this->sk.setGlobalTransform();

		std::vector<glm::vec3> lines = sk.getLines();
		std::vector<glm::vec3> points = sk.getPoints();
		std::vector<glm::vec3> cube = this->person.getCube();
		std::vector<glm::mat4> joints = this->sk.getcube();
		
		std::vector<glm::vec3> cor;
		for (int i = 0; i < 1000; i++) {
			cor.push_back(glm::vec3(i, 0, 0));
			cor.push_back(glm::vec3(0, i, 0));
			cor.push_back(glm::vec3(0, 0, i));
			cor.push_back(glm::vec3(-i, 0, 0));
			cor.push_back(glm::vec3(0, -i, 0));
			cor.push_back(glm::vec3(0, 0, -i));
		}

		GLuint VAO;
		GLuint LINES;
		GLuint POINTS;
		GLuint COR;
		GLuint CUBE;
		GLuint PERSON_MAT;

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &LINES);
		glGenBuffers(1, &POINTS);
		glGenBuffers(1, &COR);
		glGenBuffers(1, &CUBE);
		glGenBuffers(1, &PERSON_MAT);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, COR);
		this->setBool("GEO", false);
		glPointSize(5);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * cor.size(), cor.data(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
		this->setVec3("COLOR", 1, 0.8, 0.8);
		glDrawArrays(GL_POINTS, 0, cor.size());

		glBindBuffer(GL_ARRAY_BUFFER, LINES);
		this->setBool("GEO", false);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * lines.size(), lines.data(), GL_STREAM_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
		this->setVec3("COLOR", 0, 1, 1);
		glDrawArrays(GL_LINES, 0, lines.size());

		glBindBuffer(GL_ARRAY_BUFFER, POINTS);
		this->setBool("GEO", false);
		glPointSize(10);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * points.size(), points.data(), GL_STREAM_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
		this->setVec3("COLOR", 0, 1, 0);
		glDrawArrays(GL_POINTS, 0, points.size());





		glBindBuffer(GL_ARRAY_BUFFER, CUBE);
		this->setBool("GEO", true);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * cube.size(), cube.data(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

		glBindBuffer(GL_ARRAY_BUFFER, PERSON_MAT);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * joints.size(), joints.data(), GL_STREAM_DRAW);

		size_t vec4Size = sizeof(glm::vec4);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(0 * vec4Size));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(1 * vec4Size));
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(2 * vec4Size));
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(3 * vec4Size));

		glVertexAttribDivisor(1, 1);
		glVertexAttribDivisor(2, 1);
		glVertexAttribDivisor(3, 1);
		glVertexAttribDivisor(4, 1);

		// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		this->setVec3("COLOR", 0, 0, 1);
		glDrawArraysInstanced(GL_TRIANGLES, 0, cube.size(), joints.size());

		// err();

///////////////////////////////////////

		glfwSwapBuffers(this->window);
		glfwPollEvents();
	}
}

// for callback
void	App::setFront(bool status) {
	this->camera.setFront(status);
}
void	App::setBack(bool status) {
	this->camera.setBack(status);
}
void	App::setLeft(bool status) {
	this->camera.setLeft(status);
}
void	App::setRight(bool status) {
	this->camera.setRight(status);
}
void	App::setUp(bool status) {
	this->camera.setUp(status);
}
void	App::setDown(bool status) {
	this->camera.setDown(status);
}
void	App::changeFov(int num) {
	this->camera.changeFov(num);
}
void	App::resetFov() {
	this->camera.resetFov();
}
void	App::changeTexture() {
	if (this->textureIdx == this->texture.size() - 1)
		this->textureIdx = 0;
	else
		this->textureIdx++;
}


void App::setBool(std::string const &name, bool value) {         
	glUniform1i(glGetUniformLocation(this->program.id(), name.c_str()), (int)value); 
}
void App::setInt(std::string const &name, int value) { 
	glUniform1i(glGetUniformLocation(this->program.id(), name.c_str()), value); 
}
void App::setFloat(std::string const &name, float value) { 
	glUniform1f(glGetUniformLocation(this->program.id(), name.c_str()), value); 
}
void App::setVec2(std::string const &name, glm::vec2 value) { 
	glUniform2fv(glGetUniformLocation(this->program.id(), name.c_str()), 1, &value[0]); 
}
void App::setVec2(std::string const &name, float x, float y) { 
	glUniform2f(glGetUniformLocation(this->program.id(), name.c_str()), x, y); 
}
void App::setVec3(std::string const &name, glm::vec3 value) { 
	glUniform3fv(glGetUniformLocation(this->program.id(), name.c_str()), 1, &value[0]); 
}
void App::setVec3(std::string const &name, float x, float y, float z) { 
	glUniform3f(glGetUniformLocation(this->program.id(), name.c_str()), x, y, z); 
}
void App::setVec4(std::string const &name, glm::vec4 value) { 
	glUniform4fv(glGetUniformLocation(this->program.id(), name.c_str()), 1, &value[0]); 
}
void App::setVec4(std::string const &name, float x, float y, float z, float w)  { 
	glUniform4f(glGetUniformLocation(this->program.id(), name.c_str()), x, y, z, w); 
}
void App::setMat3(std::string const &name, glm::mat3 &mat) {
	glUniformMatrix3fv(glGetUniformLocation(this->program.id(), name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void App::setMat4(std::string const &name, glm::mat4 &mat) {
	glUniformMatrix4fv(glGetUniformLocation(this->program.id(), name.c_str()), 1, GL_FALSE, &mat[0][0]);
}




// for callback
static void	keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode) {
	App *app = static_cast<App*>(glfwGetWindowUserPointer(window));
	if (!app)
		return ;

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
		app->setFront(true);
	else if (key == GLFW_KEY_UP && action == GLFW_RELEASE)
		app->setFront(false);
		
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
		app->setBack(true);
	else if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE)
		app->setBack(false);

	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
		app->setLeft(true);
	else if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE)
		app->setLeft(false);

	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
		app->setRight(true);
	else if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE)
		app->setRight(false);
}

static void	mouseCallback(GLFWwindow* window, int button, int action, int mods) {
	App *app = static_cast<App*>(glfwGetWindowUserPointer(window));
	if (!app)
		return ;

	if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_PRESS)
		app->setUp(true);
	else if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_RELEASE)
		app->setUp(false);

	if (button == GLFW_MOUSE_BUTTON_2 && action == GLFW_PRESS)
		app->setDown(true);
	else if (button == GLFW_MOUSE_BUTTON_2 && action == GLFW_RELEASE)
		app->setDown(false);

	if (button == GLFW_MOUSE_BUTTON_3 && action == GLFW_PRESS)
		app->resetFov();
}

static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	App *app = static_cast<App*>(glfwGetWindowUserPointer(window));
	if (!app)
		return ;

	app->changeFov(static_cast<int>(-yoffset));
}

static void errorCallback(int error, const char *des) {
	std::cout << des << std::endl;
}

static bool endsWith(std::string const &str, std::string const &suffix) {
    if (str.length() < suffix.length()) {
        return false;
    }
    return str.compare(str.length() - suffix.length(), suffix.length(), suffix) == 0;
}

static void err() {
	GLenum err = glGetError();
	switch (err) {
		case GL_NO_ERROR:
			std::cout << "GL_NO_ERROR" << std::endl;
			break;
		case GL_INVALID_ENUM:
			std::cout << "GL_INVALID_ENUM" << std::endl;
			break;
		case GL_INVALID_VALUE:
			std::cout << "GL_INVALID_VALUE" << std::endl;
			break;
		case GL_INVALID_OPERATION:
			std::cout << "GL_INVALID_OPERATION" << std::endl;
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			std::cout << "GL_INVALID_FRAMEBUFFER_OPERATION" << std::endl;
			break;
		case GL_OUT_OF_MEMORY:
			std::cout << "GL_OUT_OF_MEMORY" << std::endl;
			break;
		case GL_STACK_UNDERFLOW:
			std::cout << "GL_STACK_UNDERFLOW" << std::endl;
			break;
		case GL_STACK_OVERFLOW:
			std::cout << "GL_STACK_OVERFLOW" << std::endl;
			break;
		default:
			std::cout << "no err" << std::endl;
			break;
	}
}