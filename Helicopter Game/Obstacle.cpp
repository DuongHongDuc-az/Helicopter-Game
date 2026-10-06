#include "Obstacle.h"
Obstacle::Obstacle(float x, float y, float w, float h) {
	wallRect.x = x;
	wallRect.y = y;
	wallRect.w = w;
	wallRect.h = h;
}

void Obstacle::Update() {
	wallRect.x -= speed;
	if (wallRect.x + wallRect.w < 0) {
		wallRect.x = 800;
	}
}

void Obstacle::reset() {
	wallRect.x = 800;
}

void Obstacle::render(SDL_Renderer* renderer, SDL_Texture* texture) {
	SDL_FRect destRect = { wallRect.x, wallRect.y, wallRect.w, wallRect.h };
	SDL_RenderTexture(renderer, texture, nullptr, &destRect);
}

SDL_FRect Obstacle::getSDL_FRect() {
	return wallRect;
}