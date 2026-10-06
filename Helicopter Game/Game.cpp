#include "Game.h"
#include <SDL3/SDL_image.h> // Make sure this is at the top

Game::Game() : helicopter(200, 300){
	Obstacle wall(800, rand() % 400, 50, 200);
	walls.push_back(wall);
	isRunning = true;
	window = nullptr;
	renderer = nullptr;
	currentState = PLAYING;
	spawnTimer = 0;
}

void Game::init(const char* title, int width, int height) {
	if (SDL_CreateWindowAndRenderer(title, width, height, 0, &window, &renderer) < 0) {
		std::cout << "Window or Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return;
	}
	
	score = 0;
	//TTF_Init();
	// = TTF_OpenFont("arial.ttf", 24);

	if (font == nullptr) {
		SDL_Log("Cannot open font: %s", SDL_GetError());
	}

	heliTex = IMG_LoadTexture(renderer, "helicopter.png");
	wallTex = IMG_LoadTexture(renderer, "wall.png");
	bgTex = IMG_LoadTexture(renderer, "background.png");
}

bool Game::running() {
	return isRunning;
}

void Game::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_EVENT_QUIT) {
			isRunning = false;
		}
	}
}

void Game::Update() {
	if (currentState == PLAYING) {
		const bool* state = SDL_GetKeyboardState(nullptr);
		helicopter.Update(state);
		
		spawnTimer++;
		bgRect = { 0, 0, 800, 600 };
		for (int i = 0; i < walls.size(); i++) {
			walls[i].Update();
			SDL_FRect helicopterRect = helicopter.getSDL_FRect();
			SDL_FRect wallRect = walls[i].getSDL_FRect();

			if (SDL_HasRectIntersectionFloat(&helicopterRect, &wallRect)) {
				currentState = GAME_OVER;
			}
			if (walls[i].getSDL_FRect().x + walls[i].getSDL_FRect().w < 0) {
				score++;
				walls.erase(walls.begin() + i);
				i--;
			}
		}
		if (spawnTimer >= 180) {
			Obstacle wall(800, rand() % 400, 50, 200);
			walls.push_back(wall);
			spawnTimer = 0;
		}

	}
	else if (currentState == GAME_OVER) {
		const bool* state = SDL_GetKeyboardState(nullptr);
		if (state[SDL_SCANCODE_RETURN]) {
			score = 0;
			helicopter.reset();
			walls.clear();
			currentState = PLAYING;
			spawnTimer = 0;
			Obstacle wall(800, rand() % 400, 50, 200);
			walls.push_back(wall);
		}
	}
}

void Game::render() {
	//if(font == nullptr){
	//	SDL_Log("Font not loaded!");
	//	return;
	//}
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	//std::string scoreText = "Score: " + std::to_string(score);
	//SDL_Color textColor = { 255, 255, 255, 255 };
	//SDL_Surface* surfaceScore = TTF_RenderText_Solid(font, scoreText.c_str(), scoreText.length(), textColor);
	//if (surfaceScore == nullptr) {
	//	SDL_Log("Unable to render text surface! SDL_ttf Error: %s", SDL_GetError());
	//}

    //SDL_Texture* textureScore = SDL_CreateTextureFromSurface(renderer, surfaceScore);
	//if(textureScore == nullptr) {
		//SDL_Log("Unable to create texture from rendered text! SDL Error: %s", SDL_GetError());
	//}

	//SDL_DestroySurface(surfaceScore);
	//
	//SDL_FRect scoreRect; 	scoreRect.x = 100; scoreRect.y = 100; scoreRect.w = 100; scoreRect.h = 30;
	//SDL_RenderTexture(renderer, textureScore, nullptr, &scoreRect);
	//SDL_DestroyTexture(textureScore);
	SDL_RenderTexture(renderer, bgTex, nullptr, &bgRect);

	helicopter.render(renderer, heliTex);

	for (int i = 0; i < walls.size(); i++) {
		walls[i].render(renderer, wallTex);
	}


	SDL_RenderPresent(renderer);

	SDL_Delay(16);
}

void Game::clean() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	//TTF_CloseFont(font);
	//TTF_Quit();
}