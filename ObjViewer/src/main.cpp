#define STB_IMAGE_IMPLEMENTATION
#include "scop.hpp"

int main(int ac, char **av) {
	if (ac != 2)
		return 1;

	App app("Game", 1024, 720);
	app.setProgram("./src/shader/texture.vs", "./src/shader/texture.fs");
	if (app.isError())
		return 1;

	app.addTexture("./src/texture/kitty.jpeg");
	app.addTexture("./src/texture/house.jpeg");
	app.setLight();

	app.addObject(av[1]);
	if (app.isError())
		return 1;

	app.loop();

	return 0;
}