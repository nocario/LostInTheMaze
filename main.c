
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <math.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "mixer.h"
#include "init.h"
#include "loadLevel.h"
#include "draw.h"


#define MapWidth 10
#define MapHeight 8
#define MapBlock 64

#define PI 3.14
#define ScreenWidth 320
#define ScreenHeight 320

int changedLevel = 0;

void initImage() {
	SDL_Surface* img = IMG_Load("bluestone.png");
	SDL_Surface* img2 = IMG_Load("sta.png");
	SDL_Surface* img3 = IMG_Load("gun.png");
	textureWall.blueWall= SDL_CreateTextureFromSurface(app.ren, img);
	textureSprite.staHead = SDL_CreateTextureFromSurface(app.ren, img2);
	textureSprite.pistol = SDL_CreateTextureFromSurface(app.ren, img3);
	SDL_FreeSurface(img);
	SDL_FreeSurface(img2);
	SDL_FreeSurface(img3);
}

float py, px, pdx, pdy;
float pa = 2 * PI;


int initSDL() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("ERROR INIT");
		return -1;
	}

	app.win = SDL_CreateWindow("Maze", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 320, 320, 0);

	if (!app.win) {
		printf("ERROR WIN");
		return -1;
	}

	app.ren = SDL_CreateRenderer(app.win, 0, SDL_RENDERER_ACCELERATED);
	if (!app.ren) {
		printf("ERROR REN");
		return -1;
	}

	return 0;
}

void Close() {
	if (app.win) {
		SDL_DestroyWindow(app.win);
	}
	if (app.ren) {
		SDL_DestroyRenderer(app.ren);
	}
	SDL_Quit();
}

void playerMove() {
	if (player.left) {
		if (player.angle > 2 * PI) {
			player.angle -= 2 * PI;
		}
		player.angle += 0.1;
		player.dirX = cos(player.angle);
		player.dirY = -sin(player.angle);
	}
	if (player.up) {
		int nextPosX = (int)(((player.x + (player.dirX * 30)))) >> 6;
		int nextPosY = (int)(((player.y + (player.dirY * 30)))) >> 6;

		if (Level1[(int)(player.y) >> 6][nextPosX] < 1) player.x += player.dirX * 3;
		if (Level1[nextPosY][(int)(player.x) >> 6] < 1) player.y += player.dirY * 3;

	}
	if (player.right) {
		if (player.angle < 0) {
			player.angle += 2 * PI;
		}
		player.angle -= 0.1;
		player.dirX = cos(player.angle);
		player.dirY = -sin(player.angle);
	}
	if (player.down) {
		int nextPosX = (int)((player.x - (player.dirX * 30))) >> 6;
		int nextPosY = (int)((player.y - (player.dirY * 30))) >> 6;

		if (Level1[(int)(player.y) >> 6][nextPosX] < 1) player.x -= player.dirX * 3;
		if (Level1[nextPosY][(int)(player.x) >> 6] < 1) player.y -= player.dirY * 3;
	}
}




int main() {
	if (initSDL() != 0) {
		Close();
		return -1;
	}
	player.gun = 0;
	player.x = 96;
	player.y = 96;
	player.angle = 2 * PI;
	px = 96;
	player.y = 96;
	player.dirX = 1;
	player.dirY = 0;
	player.dirX = 1;
	player.dirY = 0;
	player.down = 0;
	player.up = 0;
	player.right = 0;
	player.left = 0;

	int musicPos = 0;


	SDL_Event event;
	initImage();
	int run = 1;

	initMixer();
	int frame = 0;


	while (run) {

		SDL_SetRenderDrawColor(app.ren, 0, 0, 0, 255);
		SDL_RenderClear(app.ren);
		playerMove();
		SDL_SetRenderDrawColor(app.ren, 0, 0, 0, 255);
		SDL_Rect plafond = { 0, 0, 320, 160 };
		SDL_RenderFillRect(app.ren, &plafond);
		SDL_SetRenderDrawColor(app.ren, 100, 100, 100, 255);
		SDL_Rect sol = { 0, 160, 320, 160 };
		SDL_RenderFillRect(app.ren, &sol);

		drawRay();

		//drawSprite();

		if (Level1[(int)player.y >> 6][(int)player.x >> 6] == -10) {
			player.x = 96; player.y = 96;
		}
		if (Level1[(int)player.y >> 6][(int)player.x >> 6] == -12) {
			player.x = 64*62; player.y = 64*1;
		}

		SDL_Rect tGun = { 90, 195, 160, 125 };
		
		if (!player.gun && frame == 0) {
			SDL_Rect gun = { 0, 65, 64, 64 };
			SDL_RenderCopy(app.ren, textureSprite.pistol, &gun, &tGun);
		}
		else {
			if (frame >= 0 && frame < 8) {
				SDL_Rect gun = { 65, 65, 64, 64 };
				SDL_RenderCopy(app.ren, textureSprite.pistol, &gun, &tGun);
			}
			else if (frame >= 8 && frame < 16) {
				SDL_Rect gun = { 130, 65, 64, 64 };
				SDL_RenderCopy(app.ren, textureSprite.pistol, &gun, &tGun);
			}
			else if (frame >= 16 && frame < 24) {
				SDL_Rect gun = { 195, 65, 64, 64 };
				SDL_RenderCopy(app.ren, textureSprite.pistol, &gun, &tGun);
			}
			else if (frame >= 24 && frame < 32) {
				SDL_Rect gun = { 260, 65, 64, 64 };
				SDL_RenderCopy(app.ren, textureSprite.pistol, &gun, &tGun);
			}
			frame++;
			if (frame == 32) {
				frame = 0;
			}
		}


		SDL_Rect screen = { 400, 320, 320, 300 };
		SDL_SetRenderDrawColor(app.ren, 0, 0, 0, 255);
		SDL_RenderFillRect(app.ren, &screen);



		if (!Mix_PlayingMusic()) {
			//Mix_PlayMusic(playlist[musicPos], 1);
			Mix_FadeInMusic(playlist[musicPos], 1, 300);
			Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
			//Mix_FadeOutMusic(100);
			musicPos++;
			musicPos %= 4;
		}

		SDL_RenderPresent(app.ren);

		SDL_Delay(16);

		while (SDL_PollEvent(&event)) {

			switch (event.type) {
			case SDL_QUIT:
				run = 0;
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_RIGHT) {
					player.right = 1;
				}
				if (event.key.keysym.sym == SDLK_LEFT) {
					player.left = 1;
				}
				if (event.key.keysym.sym == SDLK_UP) {
					player.up = 1;
				}
				if (event.key.keysym.sym == SDLK_DOWN) {
					player.down = 1;
				}
				if (event.key.keysym.sym == SDLK_EQUALS) {
					int volume = Mix_VolumeMusic(-1) + 2;
					Mix_VolumeMusic(volume);
				}
				if (event.key.keysym.sym == SDLK_RIGHTPAREN) {
					int volume = Mix_VolumeMusic(-1) - 2;
					Mix_VolumeMusic(volume);
				}
				if (event.key.keysym.sym == SDLK_u) {
					Mix_FadeInMusic(playlist[3], 1, 0);

				}
				if (event.key.keysym.sym == SDLK_RCTRL) {
					player.gun = 1;
				}
				break;
			case SDL_KEYUP:
				if (event.key.keysym.sym == SDLK_RIGHT) {
					player.right = 0;
				}
				if (event.key.keysym.sym == SDLK_LEFT) {
					player.left = 0;
				}
				if (event.key.keysym.sym == SDLK_UP) {
					player.up = 0;
				}
				if (event.key.keysym.sym == SDLK_DOWN) {
					player.down = 0;
				}
				if (event.key.keysym.sym == SDLK_RCTRL) {
					player.gun = 0;
				}
				if (event.key.keysym.sym == SDLK_p) {
					if (Mix_PausedMusic()) {
						Mix_ResumeMusic();
					}
					else {
						Mix_PauseMusic();
					}
				}
				break;
			}
		}
	}
	SDL_DestroyTexture(textureSprite.staHead);
	SDL_DestroyTexture(textureSprite.pistol);
	SDL_DestroyTexture(textureWall.blueWall);
	freeMusic();
	Mix_CloseAudio();
	Close();
	return 0;
}

