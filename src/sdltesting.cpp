#include <string>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include "character.h"
#include "cSurface.h"
#include "cTexture.h"
#include "tmxparser/Tmx.h"
#include "levelMap.h"
//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 400;

//Starts up SDL and creates window
bool init();

//Frees media and shuts down SDL
void close();

SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
SDL_Renderer* renderer = NULL;

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Texture* gBackground = NULL;
character* bigfoot = NULL;

int main(int argv, char* args[]){

	levelMap* map = NULL;

	bool quit = false;

	double t = SDL_GetTicks();
	double dt = 0.0;

	SDL_Event e;

	//Start up SDL and create window
	if (!init()){
		printf("Failed to initialize!\n");
	}
	else{
		//Load level data
		map = new levelMap("textures/forest.tmx", renderer, gScreenSurface->format);
		//Load media
		bigfoot = new character(renderer, "textures/bigfootsprite2.png", gScreenSurface->format);
		gBackground = cTexture::loadTexture(renderer, "textures/forest.png", gScreenSurface->format);
	
		//Update the surface
		SDL_UpdateWindowSurface(gWindow);
	}

	printf("width: %d height: %d", map->level_width, map->level_height);

	while (!quit){
		while (SDL_PollEvent(&e) != 0){
			//User requests quit
			if(e.type == SDL_QUIT)
			{
				quit = true;
			}

			bigfoot->handleEvent(e);
		}

		dt = (SDL_GetTicks()-t)/1000.0;

		bigfoot->move(dt, map);

		camera.x = ( bigfoot->cPosX + bigfoot->currentframe->w / 2 ) - SCREEN_WIDTH / 2;
        camera.y = ( bigfoot->cPosY + bigfoot->currentframe->h / 2 ) - SCREEN_HEIGHT / 2;

        if( camera.x < 0 ){ 
        	camera.x = 0;
        }
        
        if( camera.y < 0 ){
            camera.y = 0;
        }
        
        if( camera.x > map->level_width - camera.w ){
            camera.x = map->level_width- camera.w;
        }
        
        if( camera.y > map->level_height - camera.h ){
            camera.y = map->level_height - camera.h;
        }

 		//printf("cam x: %d cam y: %d\n", camera.x, camera.y);

		t = SDL_GetTicks();

		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
		SDL_RenderClear(renderer);

		cTexture::renderTexture(gBackground, renderer, 0, 0);
		map->drawMapPortion(renderer, &camera);
		bigfoot->render(renderer, &camera);
		SDL_Rect characterFrame = {bigfoot->cPosX - camera.x, bigfoot->cPosY - camera.y, 50, 100};
		SDL_RenderDrawRect(renderer, &characterFrame);

		SDL_RenderPresent(renderer);
	}
	bigfoot->free();
	cTexture::free(gBackground);
	map->free();

	//Free resources and close SDL
	close();

	return 0;

}

bool init(){

	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}

	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}

		else
		{
			//Create vsynced renderer for window
			renderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (renderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}

			//Get window surface
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}

	return success;
}

void close(){

	//Deallocate surface
	SDL_FreeSurface(gScreenSurface);
	gScreenSurface = NULL;
	//Destroy window
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	renderer = NULL;

	//Quit SDL subsystems
	SDL_Quit();

}
