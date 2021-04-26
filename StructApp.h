#pragma once
#pragma once

#ifndef STRUCTAPP_H_INCLUDED
#define STRUCTAPP_H_INCLUDED

#include <SDL.h>
#include <SDL_mixer.h>


typedef struct {
	SDL_Window* win;
	SDL_Renderer* ren;
} APP;

typedef struct {
	float x;
	float y;
	float angle;
	float dirX;
	float dirY;
	int up;
	int down;
	int right;
	int left;
	int gun;
}PLAYER;

extern APP app;
extern PLAYER player;
extern Mix_Music *playlist[4];
APP app;
PLAYER player;



#endif // !STRUCTAPP_H_INCLUDED

