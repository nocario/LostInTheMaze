#include "draw.h"


float Sbuffer[320];
const int distPlane = (ScreenWidth / 2) / 0.58;
const float angleForEachRay = (60.0 / ScreenWidth) * 0.017;

void drawRay() {
	float rayAngle = player.angle + (PI / 6);
	float interY, interX;
	float distX, distY;
	float Ya, Xa;
	int mapX, mapY;

	SDL_SetRenderDrawBlendMode(app.ren, SDL_BLENDMODE_BLEND);
	SDL_SetTextureBlendMode(textureWall.blueWall, SDL_BLENDMODE_BLEND);
	SDL_SetTextureBlendMode(textureWall.blueWall, SDL_BLENDMODE_BLEND);

	for (int i = 0; i < ScreenWidth; i++) {
		SDL_Rect sliceImage;
		distX = 1000;
		distY = 1000;
		int hitx = 0;
		int hity = 0;

		//check horizontal line


		int dof = 0;
		if (sin(rayAngle) > 0) {
			interY = ((((int)(player.y) >> 6) << 6) - 1);

			interX = player.x + (player.y - interY) / tan(rayAngle);
			Ya = -64;
			Xa = 64 / tan(rayAngle);
		}

		else if (sin(rayAngle) < 0) {
			interY = (((int)(player.y) >> 6) << 6) + 64;
			interX = player.x + ((player.y - interY) / tan(rayAngle));
			Ya = 64;
			Xa = (-64) / tan(rayAngle);
		}
		else {
			interX = player.x;
			interY = player.y;
			dof = 8;
		}
		while (dof < 10) {
			mapX = ((int)interX) >> 6;
			mapY = ((int)interY) >> 6;
			if (mapX >= 0 && mapX < MapWidth && mapY >= 0 && mapY < MapHeight && Level1[mapY][mapX] > 0) {
				//distY = abs((player.y - interY) / sin(rayAngle));

				distY = cos(rayAngle)*(interX - player.x) - sin(rayAngle)*(interY - player.y);
				dof = 10;
			}
			else {
				interX += Xa;
				interY += Ya;
				dof++;
			}
		}
		float oldInterX = interX;

		//check vertical line

		dof = 0;

		if (cos(rayAngle) > 0) {
			interX = (((int)(player.x) >> 6) << 6) + 64;
			interY = player.y + (player.x - interX)*tan(rayAngle);
			Xa = 64;
			Ya = (-64) * tan(rayAngle);
		}
		else if (cos(rayAngle) < 0) {
			interX = (((int)(player.x) >> 6) << 6) - 1;
			interY = player.y + (player.x - interX)*tan(rayAngle);
			Xa = -64;
			Ya = 64 * tan(rayAngle);
		}
		else {
			interX = player.x;
			interY = player.y;
			dof = 8;
		}
		while (dof < 10) {
			mapX = (int)(interX) >> 6;
			mapY = (int)(interY) >> 6;
			if (mapX >= 0 && mapX < MapWidth && mapY >= 0 && mapY < MapHeight && Level1[mapY][mapX] > 0) {

				//distX = abs((px - interX) / cos(rayAngle));
				distX = cos(rayAngle)*(interX - player.x) - sin(rayAngle)*(interY - player.y);

				dof = 10;
			}
			else {
				interX += Xa;
				interY += Ya;
				dof++;
			}
		}

		float fDist;
		if (distX < distY) {
			fDist = distX;
			sliceImage.x = (int)interY % 64;
			SDL_SetRenderDrawColor(app.ren, 10, 10, 10, 0);
		}
		else {
			fDist = distY;
			SDL_SetRenderDrawColor(app.ren, 10, 10, 10, 90);
			sliceImage.x = (int)oldInterX % 64;
		}

		sliceImage.w = 1;
		sliceImage.y = 0;
		sliceImage.h = 64;

		float fDistFish = fDist * cos(player.angle - rayAngle);
		int lineH = (64 * distPlane) / fDistFish;
		int lineO = (ScreenHeight / 2) - (lineH / 2);


		SDL_Rect wall = { i, lineO , 1, lineH };
		SDL_RenderCopy(app.ren, textureWall.blueWall, &sliceImage, &wall);

		SDL_RenderFillRect(app.ren, &wall);

		SDL_SetRenderDrawColor(app.ren, 255, 0, 0, 255);

		//SDL_RenderDrawLine(app.ren, px + 5, player.y + 5, cos(rayAngle) * distY + px + 5, -sin(rayAngle) * distY + player.y + 5);
		//SDL_RenderDrawLine(app.ren, px + 5, player.y + 5, cos(rayAngle) * distX + px + 5, -sin(rayAngle) * distX + player.y + 5);
		//SDL_SetRenderDrawColor(app.ren, 255, 0, 0, 255);
		//SDL_RenderDrawLine(app.ren, px, player.y, cos(rayAngle) * fDist + px, -sin(rayAngle) * fDist + player.y);

		rayAngle -= angleForEachRay;

		Sbuffer[i] = fDistFish;
	}
}

/*
void drawSprite() {

	float SpriteDist[1];
	int lineH = 64;
	int lineO = 0;
	float size;

	for (int i = 0; i < 1; i++) {
		SpriteDist[i] = sqrt((-player.x + spriteList[i].x)*(-player.x + spriteList[i].x) + (-player.y + spriteList[i].y)*(-player.y + spriteList[i].y));
	}

	float xPos;
	int yPos;
	for (int i = 0; i < 1; i++) {
		double spriteX = spriteList[i].x - player.x;
		double spriteY = spriteList[i].y - player.y;

		float ang = player.angle * 180 / PI;

		float a = atan2f(spriteY, spriteX) - atan2f(player.dirY, player.dirX);
		float b = a * 180 / PI;

		if (a < 0) a += 2 * PI;
		if (a > 0) a -= 2 * PI;

		while (b < 0) b += 360;
		while (b >= 360) b -= 360;

		size = 277 * (320 / 64) / (cos(a) * SpriteDist[0]);
		float x = tan(a) * 277;
		xPos = 160 + x + size / 2;

		yPos = (ScreenHeight + size * 5) / 2;
		if (yPos < 0) yPos = 0;

		//printf(" x %f", 160 + x + size/2);


		//printf("a %f", size);


		lineH = 64 * distPlane / SpriteDist[i];
		lineO = ((ScreenHeight) / 2) - (lineH / 2);
		float trsize = size * 5;
		for (int j = 0; j < 64; j++) {
			//printf("%f     ", Sbuffer[j]);
			//printf("sprite %f ", SpriteDist[j]);
			int cPos = xPos;
			if (cPos > 320) cPos = 320;
			if (cPos < 0) cPos = 0;
			if (SpriteDist[i] < 500 && Sbuffer[cPos + j] > SpriteDist[i] && (j + (int)xPos) > 0) {
				SDL_Rect obj = { j, 0, 1, 64 };
				SDL_Rect wall = { j + (int)xPos, yPos, 1, trsize };
				SDL_RenderCopy(app.ren, textureSprite.staHead, &obj, &wall);
				if (player.gun && !spriteList[i].activated) {
					spriteList[i].activated++;
					printf("aie");
					Level1[spriteList[i].map[1]][spriteList[i].map[0]] = 0;
				}
				//SDL_RenderFillRect(app.ren, &wall);
			}
		}

	}
}
*/