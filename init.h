
#ifndef INIT__H__DEFINED
#define INIT__H__DEFINED

#include <SDL.h>

#define MapWidth 64
#define MapHeight 64
#define MapBlock 64

#define PI 3.14
#define ScreenWidth 320
#define ScreenHeight 320

typedef struct {
	SDL_Texture* blueWall;
} TextureWall;

typedef struct {
	SDL_Texture* staHead;
	SDL_Texture* pistol;
} TextureSprite;

typedef struct {
	SDL_Window* win;
	SDL_Renderer* ren;
} App;

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
} Player;

typedef struct {
	double x;
	double y;
	int activated;
	int map[2];
} Sprite;


extern App app;
extern Player player;
extern TextureWall textureWall;
//extern const int distPlane = (ScreenWidth / 2) / 0.58;
//extern const float angleForEachRay = (60.0 / ScreenWidth) * 0.017;

#endif // !INIT__H__DEFINED
