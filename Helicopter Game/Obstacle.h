#pragma once
#ifndef OBSTACLE_H
#define OBSTACLE_H
#include <SDL3/SDL.h>
#include <iostream>
#include <SDL3/SDL_image.h>

class Obstacle {
private:
	SDL_FRect wallRect;
	float speed = 3.0f;
public:
	Obstacle(float x, float y, float w, float h);
	void Update();
	void reset();
	void render(SDL_Renderer* renderer, SDL_Texture* texture);
	SDL_FRect getSDL_FRect();
};
#endif 