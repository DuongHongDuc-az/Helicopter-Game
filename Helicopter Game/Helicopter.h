#pragma once
#ifndef HELICOPTER_H
#define HELICOPTER_H
#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <iostream>

class Helicopter {
private:
	float velocityY = 0.0;
	float gravity = 0.05f;
	float lift = -0.1f;
	SDL_FRect playerRect;
public:
	Helicopter(float , float);
	void Update(const bool* state );
	void render(SDL_Renderer* renderer, SDL_Texture* texture);
	void reset();
	SDL_FRect getSDL_FRect();
};
#endif