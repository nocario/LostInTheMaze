#include "StructApp.h"


//trash
void drawPlayer() {
	SDL_Rect pl = { player.x, player.y, 10, 10 };
	SDL_SetRenderDrawColor(app.ren, 255, 255, 0, 255);
	SDL_RenderFillRect(app.ren, &pl);
}
//trash
void drawDir() {
	SDL_SetRenderDrawColor(app.ren, 255, 255, 0, 255);
	SDL_RenderDrawLine(app.ren, player.x + 5, player.y + 5, player.dirX*(100) + player.x + 5, player.dirY*(100) + player.y + 5);
}
//trash
void drawGrid() {
	SDL_SetRenderDrawColor(app.ren, 255, 255, 255, 255);
	for (int i = 0; i < 7; i++) {
		SDL_RenderDrawLine(app.ren, i * 64, 0, i * 64, 384);
		SDL_RenderDrawLine(app.ren, 0, i * 64, 384, i * 64);
	}
}