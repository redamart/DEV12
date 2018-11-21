#pragma once

#include "Game.h"
#include "TextureManager.h"
#include <cstdlib>
#include <ctime>
#include <fstream>

class Map
{
public:
	
	void rule(double& val, double x, double y, int row, int columm) {
		if (val < x) {       //  3% que sea roca
			map[row][columm] = 0 + 48;

		}
		else if (val < y)  //  3% + 20% que sea planta
			map[row][columm] = 1 + 48;
		else   //  5% + 20% + 30% que sea pasto
			map[row][columm] = 2 + 48;
	}
	
	void generateMap() {
		int con = -1;
		for (int row = 0; row < 90; row++) {
			for (int columm = 0; columm < 95; columm++) {



				double val = (double)rand() / RAND_MAX;


				/*if (val < 0.03)       //  3% que sea roca
					map[row][columm] = 0 + 48;
				else if (val < 0.25)  //  3% + 20% que sea planta
					map[row][columm] = 1 + 48;
				else   //  5% + 20% + 30% que sea pasto
					map[row][columm] = 2 + 48;
				//*/

				
				switch(con){
				case '-1': rule(val, 0.03, 0.25, row, columm); break;

				
				}
				


			}
		}

	}
	Map() {
		srand(time(NULL));
		dirt = TextureManager::LoadTexture("media/plant.png");
		grass = TextureManager::LoadTexture("media/grass.png");
		water = TextureManager::LoadTexture("media/rock.png");
		//LoadMap(lvl1);
		generateMap();
		src.x = src.y = 0;
		src.w = dest.w = 32;
		src.h = dest.h= 32;
		dest.x = dest.y = 0;
	};
	~Map() {};
	void LoadMap(char cuadrados[]) {
		int i=0;
		for (int row = 0; row < fila; row++) {
			for (int columm = 0; columm < columna; columm++) {
				map[row][columm] = cuadrados[i];
				i++;
			}
		}
	}
	void UpdateMap() {
		moveX = 0 - Game::camera.x;
		moveY = 0 - Game::camera.y;

	}
	void DrawMap() {
		int type = 0;

		for (int row = 0; row < fila; row++) {
			for (int columm = 0; columm < columna; columm++) {
				type = map[row][columm];
				dest.x = (columm * 32) + moveX;
				dest.y = (row * 32) + moveY;
				switch (type) {
				case '0':
					TextureManager::Draw(water, src, dest);
					break;
				case '1':
					TextureManager::Draw(dirt, src, dest);
					break;
				case '2':
					TextureManager::Draw(grass, src, dest);
					break;
				}
			}
		}
	}
	void saveMap() {
		if (Game::event.key.keysym.sym == SDLK_s) {
		std::ofstream  mapa("mapa.txt");

		for (int row = 0; row < 50; row++) {
			for (int columm = 0; columm < 55; columm++) {
				mapa << map[row][columm];
			}
		}
	}
		num++;
	}
	void addColumna() {
		/*
			for (int columm = 0; columm < columna; columm++) {



				double val = (double)rand() / RAND_MAX;


				if (val < 0.03)       //  3% que sea roca
					map[fila][columna+1] = 0 + 48;
				else if (val < 0.25)  //  3% + 20% que sea planta
					map[fila][columna+1] = 1 + 48;
				else   //  5% + 20% + 30% que sea pasto
					map[fila][columna+1] = 2 + 48;
				//

			}*/
			columna++;
		
	}
	void addFila() {
		/*
		for (int columm = 0; columm < columna; columm++) {



			double val = (double)rand() / RAND_MAX;


			if (val < 0.03)       //  3% que sea roca
				map[fila + 1][columm] = 0 + 48;
			else if (val < 0.25)  //  3% + 20% que sea planta
				map[fila + 1][columm] = 1 + 48;
			else   //  5% + 20% + 30% que sea pasto
				map[fila + 1][columm] = 2 + 48;
			//

		}*/
		fila++;

	}

private:
	int fila = 50;
	int columna = 55;
	SDL_Rect src, dest;
	SDL_Texture* dirt;
	SDL_Texture* grass;
	SDL_Texture* water;
	char map[90][95];
	int num = 1;
	int moveX = 0;
	int moveY = 0;

};