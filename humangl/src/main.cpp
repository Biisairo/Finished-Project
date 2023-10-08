#include "App.hpp"

int main(int ac, char **av) {

	App app("test", 1024, 720);
	app.setProgram("./src/shader/vs.glsl", "./src/shader/fs.glsl");
	if (app.isError())
		return 1;

	if (ac == 3)
		app.setfile(av[1], av[2]);
	else if (ac == 2) {
		std::string num(av[1]);
		app.setfile("resource/skeleton/" + num + ".asf", "resource/motion/" + num + ".amc");
	} else
		app.setfile("02.asf", "02.amc");

	app.loop();
}

