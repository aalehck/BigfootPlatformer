#ifndef _CHARACTER_
#define _CHARACTER_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include "cTexture.h"
#include "levelMap.h"

class character{
private:
	

	static const int DOT_VEL = 200;

public:

	double cPosX, cPosY;

	int cVelX, cVelY, gravity, speedCoefficient;
	
	int framecount, totalcount;

	bool isJumping, isFalling;

	SDL_Texture* texture = NULL;

	SDL_Rect spritesheet[4];
	
	SDL_Rect* currentframe = NULL;

	character(SDL_Renderer* renderer, char* File, const SDL_PixelFormat* fmt);

	void handleEvent(SDL_Event& e);

	void move(double dt, levelMap* map);

	void render(SDL_Renderer* renderer, SDL_Rect* camera);

	void free();

};
#endif
