#pragma once
#include "Game.h"
#include "TextureManager.h"
#include "time.h"
class GameObject {
public:
	GameObject(int x,int y) {
		
		objTexture = TextureManager::LoadTexture("media/portal.png");
		xpos = x;
		ypos = y;
		cont = 0;
		colRect.x = x;
		colRect.y = y;
		colRect.w = 50;
		colRect.h = 75;

		
	};
	~GameObject() {
	
	};
	void Update() {
		
		if (cont == 20) {
			ypos -= 5;
		}
		if (cont == 40) {
			ypos += 5;
		}
		if (cont == 41) {
			cont = 0;
		}
		srcRect.h = 75;
		srcRect.w = 50;
		srcRect.x = 0;
		srcRect.y = 0;
		
		 destRect.x = xpos - Game::camera.x;
		destRect.y = ypos - Game::camera.y;
		colRect.x = xpos - Game::camera.x;
		colRect.y = ypos - Game::camera.y;
		destRect.w = srcRect.w ;
		destRect.h = srcRect.h ;

		cont++;
	};
	void Render() {
		SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
	};
	SDL_Rect returnRect() {
		return this->colRect;
	}
private:
	int xpos;
	int ypos;
	int cont;
	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect,colRect;
	
	

};