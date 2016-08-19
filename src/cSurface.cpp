#include "cSurface.h"

cSurface::cSurface() {
}

SDL_Surface* cSurface::cLoad(char* File, const SDL_PixelFormat* fmt) {
	SDL_Surface* Surf_Temp = NULL;
	SDL_Surface* Surf_Return = NULL;

	if ((Surf_Temp = IMG_Load(File)) == NULL) {
		return NULL;
	}

	Surf_Return = SDL_ConvertSurface(Surf_Temp, fmt, NULL);
	SDL_FreeSurface(Surf_Temp);

	return Surf_Return;
}

SDL_Surface* cSurface::cLoad(char* File, const SDL_PixelFormat* fmt, int R, int B, int G, int A){
	SDL_Surface* Surf_Temp = NULL;
	SDL_Surface* Surf_Return = NULL;

	if ((Surf_Temp = IMG_Load(File)) == NULL) {
		return NULL;
	}

	Surf_Return = SDL_ConvertSurface(Surf_Temp, fmt, NULL);
	SDL_FreeSurface(Surf_Temp);

	Uint32 colorkey = SDL_MapRGBA(Surf_Return->format, R, B, G, A);
	SDL_SetColorKey(Surf_Return, SDL_TRUE, colorkey);


	return Surf_Return;
}

bool cSurface::cDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y) {
	if (Surf_Dest == NULL || Surf_Src == NULL) {
		return false;
	}

	SDL_Rect DestR;

	DestR.x = X;
	DestR.y = Y;

	SDL_BlitSurface(Surf_Src, NULL, Surf_Dest, &DestR);

	return true;
}

bool cSurface::cDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y, int X2, int Y2, int W, int H) {
	if (Surf_Dest == NULL || Surf_Src == NULL) {
		return false;
	}

	SDL_Rect DestR;

	DestR.x = X;
	DestR.y = Y;
	DestR.w = 640;
	DestR.h = 480;

	SDL_Rect SrcR;

	SrcR.x = X2;
	SrcR.y = Y2;
	SrcR.w = W;
	SrcR.h = H;

	SDL_BlitSurface(Surf_Src, &SrcR, Surf_Dest, &DestR);

	return true;
}

bool cSurface::checkCollision(SDL_Rect a, SDL_Rect b){
	//bottom of a and top of b
	if(a.y+a.h <= b.y){
		return false;
	}

	//top of a and bottom of b
	if(a.y >= b.y + b.h){
		return false;
	}

	//right of a and left of b
	if(a.x + a.w <= b.x){
		return false;
	}

	//left of a and right of b
	if(a.x >= b.x+b.h){
		return false;
	}

	return true;
}