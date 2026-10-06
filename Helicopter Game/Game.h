#pragma once
#ifndef  GAME_H
#define GAME_H
#include <SDL3/SDL_ttf.h>
#include <SDL3/SDL_image.h>
#include "Helicopter.h"
#include "Obstacle.h"
#include <vector>
#include<string>
enum GameState {
	MENU,
	PLAYING,
	GAME_OVER
};

class Game {
private:
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
	GameState currentState;
	Helicopter helicopter;
	std::vector <Obstacle> walls;
	int spawnTimer;
	TTF_Font* font;
	int score;
	SDL_Texture* heliTex;
	SDL_Texture* wallTex;
	SDL_Texture* bgTex = nullptr;
	SDL_FRect bgRect;
public:
	Game();
	void init(const char* tile, int width, int height);
	void handleEvents();
	bool running();
	void Update();
	void render();
	void clean();
};
#endif