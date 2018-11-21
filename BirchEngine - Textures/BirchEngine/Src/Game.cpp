#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"
#include "Player.h"
#include "time.h"
Player* player;

Map* map;
int cont = 0;


GameObject* portales[1000000];




SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
SDL_Rect Game::camera = { 0,0,9000,9000 };
/*SDL_Texture *playerTex;
SDL_Rect src, destR;*/
Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int width, int height, bool fullscreen)
{

	int flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		isRunning = true;
	}
	player = new Player("media/player.png", 600, 400);
	srand(time(NULL));
	int max= 10000;
	int min= 1;
	for (int i = 0; i < 100; i++) {
		int x= rand() % (max - min + 1) + min;
		int y= rand() % (max - min + 1) + min;
		portales[i] = new GameObject(x,y);
		
	}
	
	map = new Map();
	generateX = 830;
	
	
	
}

void Game::handleEvents()
{
	

	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT :
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update()
{
	
	camera.x = player->getRect().x;
	camera.y = player->getRect().y ;
	if (camera.x < 0)
		camera.x = 0;
	if (camera.y < 0)
		camera.y = 0;
	player->Move(cont);
	for (int i = 0; i < 100; i++) {



		portales[i]->Update();
		player->intersectWidth(portales[i]->returnRect());
		player->Update();
	}
	/*
	if (camera.x > camera.w)
		camera.x = camera.w;
	if (camera.y > camera.h)
		camera.y = camera.h;
		*/

	if (Game::event.key.keysym.sym == SDLK_c) {

		std::ifstream mapafile("mapa.txt");
		char cuadrados[9000];
		char cuadrado;
		int i = 0;
		while (!mapafile.eof()) {
			mapafile >> cuadrado;
			cuadrados[i] = cuadrado;
			i++;
		}


		/*int sig = 0;
		for (int row = 0; row < 20; row++) {
			for (int columm = 0; columm < 25; columm++) {
				map[row][columm] = cuadrados[i];
				sig++;

			}
		}
		*/
		map->LoadMap(cuadrados);

	}


	cont++;
	
	
	std::cout << player->getRect().x<< std::endl;
	std::cout << player->getRect().y<< std::endl;
	
	if (player->getRect().x == generateX) {
		map->addColumna();
	generateX += 32;
	}
	
	
	
}

void Game::render()
{

	SDL_RenderClear(renderer);
	map->DrawMap();
	map->saveMap();
	map->UpdateMap();
	player->Render();
	for (int i = 0; i < 100; i++) {

		portales[i]->Render();
	}
	//portal->Render();
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}