#include "App.hpp"

void App::loop() {
	Object tmp("./map/42.obj");

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