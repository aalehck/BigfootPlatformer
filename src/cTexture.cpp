#include "cTexture.h"

void cTexture::renderTexture(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip){

	int h, w;
	SDL_QueryTexture(texture, NULL, NULL, &h, &w);

	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, h, w};

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, angle, center, flip);
}

SDL_Texture* cTexture::loadTexture(SDL_Renderer* ren, char* File, const SDL_PixelFormat* fmt){
	SDL_Texture* texture = NULL;

	SDL_Surface* surface = cSurface::cLoad(File, fmt);

	if (surface != NULL){

		texture = SDL_CreateTextureFromSurface(ren, surface);
		SDL_FreeSurface(surface);

		if (texture == NULL){
			printf("Texture load from surface died\n");
		}

	}
	
	return texture;
};

SDL_Texture* cTexture::loadTexture(SDL_Renderer* ren, char* File, const SDL_PixelFormat* fmt, int R, int B, int G, int A){
	SDL_Texture* texture = NULL;

	SDL_Surface* surface = cSurface::cLoad(File, fmt, R, B, G, A);

	if (surface != NULL){

		texture = SDL_CreateTextureFromSurface(ren, surface);
		SDL_FreeSurface(surface);

		if (texture == NULL){
			printf("Texture load from surface died");
		}

	}

	return texture;
};

void cTexture::free(SDL_Texture* texture){
	if (texture != NULL)
	{
		SDL_DestroyTexture(texture);
	}
}
