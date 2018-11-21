#pragma once
#include "Game.h"

class TextureManager {

public:
	static SDL_Texture* LoadTexture(const char* filename) {
		SDL_Surface* tempSurface = tempSurface = IMG_Load(filename);
		SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
		SDL_FreeSurface(tempSurface);
		return tex;
	};
	static void Draw(SDL_Texture * tex, SDL_Rect src, SDL_Rect dest) {
		SDL_RenderCopy(Game::renderer, tex, &src, &dest);

	}
};