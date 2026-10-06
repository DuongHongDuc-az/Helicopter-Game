#include "Helicopter.h"
Helicopter::Helicopter(float x, float y) {
	playerRect.x = x;
	playerRect.y = y;
	playerRect.w = 60;
	playerRect.h = 30;
}

void Helicopter::Update(const bool* state) {
	if (state[SDL_SCANCODE_SPACE]) {
		velocityY += lift;
	}
	else {
		velocityY += gravity;
	}
	playerRect.y += velocityY;

	if (playerRect.y < 0) {
		playerRect.y = 0;
		velocityY = 0;
	}
	else if (playerRect.y + playerRect.h > 600) {
		playerRect.y = 600 - playerRect.h;
		velocityY = 0;
	}
}

void Helicopter::render(SDL_Renderer* renderer, SDL_Texture* texture) {
	SDL_FRect destRect = { playerRect.x, playerRect.y, playerRect.w, playerRect.h };
	SDL_RenderTexture(renderer, texture, nullptr, &destRect);
}

void Helicopter::reset() {
	playerRect.x = 200;
	playerRect.y = 300;
	velocityY = 0;
}

SDL_FRect Helicopter::getSDL_FRect() {
	return playerRect;
}