#include "App.hpp"

App::App(): camera(500, 500) {
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
}

App::App(std::string const &title, int width, int height): camera(width, height) {
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
}

App::~App() {
	for (std::vector<GLuint>::iterator it = this->texture.begin(); it != this->texture.end(); it++)
		glDeleteTextures(1, &(*it));
	for (std::vector<Object>::iterator it = this->objects.begin(); it != this->objects.end(); it++)
		it->destroy();
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

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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

void App::addObject(std::string const &filename) {
	Object tmp(filename);
	if (tmp.isError())
		return this->setError();
	this->objects.push_back(tmp);
}

void App::deleteObject(size_t idx) {
	this->objects.erase(this->objects.begin() + idx);
}

void App::getUniformLocation(std::string s) {
	GLuint tmp = glGetUniformLocation(this->program.id(), s.c_str());
	this->uniform.insert(std::make_pair(s, tmp));
}

GLuint App::getUniformID(std::string s) {
	return this->uniform.find(s)->second;
}

void App::setLight() {
	glm::vec3 light(1, 1, 1);
	glm::vec3 lightPos(0, 6, 0);
	this->setVec3("light.position", lightPos);
	this->setVec3("light.ambient", light);
	this->setVec3("light.diffuse", light);
	this->setVec3("light.specular", light);
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

		// this->camera.render();
		this->renderCamera(delta);
		glm::mat4 view(this->camera.getView());
		glm::mat4 projection(this->camera.getProjection());
		this->setMat4("VIEW", view);
		this->setMat4("PROJECTION", projection);

		glm::vec3 viewPos = this->camera.getPosition();
		this->setVec3("VIEWPOS", viewPos);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, this->texture[this->textureIdx]);
		this->setInt("TEXTURE", 0);

		this->setFloat("TransitionTexture", this->transitionTexture(delta));

		if (this->is_fill)
			this->toFace();
		else
			this->toLine();
		
		for (std::vector<Object>::iterator it = this->objects.begin(); it != this->objects.end(); it++) {
			this->rotate(*it, delta);
			
			Material mat = it->getMaterial()[0];
			this->setMaterial(mat);

			glm::mat4 model = it->getModel();
			this->setMat4("MODEL", model);
			it->draw();
		}

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
void	App::setRotX(int state) {
	if (this->rotX == state)
		this->rotX = STOP;
	else
		this->rotX = state;
}
void	App::setRotY(int state) {
	if (this->rotY == state)
		this->rotY = STOP;
	else
		this->rotY = state;
}
void	App::setRotZ(int state) {
	if (this->rotZ == state)
		this->rotZ = STOP;
	else
		this->rotZ = state;
}

void App::rotate(Object &obj, double delta) {
	if (this->rotX == CW)
		obj.rotateX(delta);
	else if (this->rotX == CCW)
		obj.rotateX(-delta);
	if (this->rotY == CW)
		obj.rotateY(delta);
	else if (this->rotY == CCW)
		obj.rotateY(-delta);
	if (this->rotZ == CW)
		obj.rotateZ(delta);
	else if (this->rotZ == CCW)
		obj.rotateZ(-delta);
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
void App::setMaterial(Material &material) {
	this->setVec3("material.ambient", material.ambient);
	this->setVec3("material.diffuse", material.diffuse);
	this->setVec3("material.specular", material.specular);
	this->setFloat("material.shininess", material.shininess);
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
	
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		app->changeTexture();
	
	if (key == GLFW_KEY_U && action == GLFW_PRESS)
		app->setRotX(CW);
	if (key == GLFW_KEY_J && action == GLFW_PRESS)
		app->setRotX(CCW);
	if (key == GLFW_KEY_I && action == GLFW_PRESS)
		app->setRotY(CW);
	if (key == GLFW_KEY_K && action == GLFW_PRESS)
		app->setRotY(CCW);
	if (key == GLFW_KEY_O && action == GLFW_PRESS)
		app->setRotZ(CW);
	if (key == GLFW_KEY_L && action == GLFW_PRESS)
		app->setRotZ(CCW);
	if (key == GLFW_KEY_M && action == GLFW_PRESS)
		app->setTransition();
	if (key == GLFW_KEY_COMMA && action == GLFW_PRESS)
		app->changePolyMode();
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