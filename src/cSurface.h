#ifndef _CSURFACE_
#define _CSURFACE_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class cSurface {
	private:
		cSurface();

	public:
		static SDL_Surface* cLoad(char* File, const SDL_PixelFormat* fmt);

		static SDL_Surface* cLoad(char* File, const SDL_PixelFormat* fmt, int R, int G, int B, int A);

		static bool cDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y);

		static bool cDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y, int X2, int Y2, int W, int H);

		static bool checkCollision(SDL_Rect a, SDL_Rect b);
};
#endif
