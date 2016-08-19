#ifndef _CTEXTURE_
#define _CTEXTURE_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include "cSurface.h"

class cTexture{
private:

public:
	cTexture();

	static void free(SDL_Texture* texture);

	static SDL_Texture* loadTexture(SDL_Renderer* ren, char* File, const SDL_PixelFormat* fmt);

	static SDL_Texture* loadTexture(SDL_Renderer* ren, char* File, const SDL_PixelFormat* fmt, int R, int B, int G, int A);

	static void renderTexture(SDL_Texture* tex, SDL_Renderer* ren, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
};
#endif
