#include "Game.h"
#include "Obstacle.h"
#include "Helicopter.h"
int main(int argc, char* argv[]) {
	if (SDL_INIT_VIDEO < 0) {
		std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		return -1;
	}

	Game game;

	game.init("Helicopter Game", 800, 600);

	while (game.running()) {
		game.handleEvents();	

		game.Update();

		game.render();
	}

	game.clean();
	return 0;
}