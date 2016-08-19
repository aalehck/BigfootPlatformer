#ifndef _LEVELMAP_
#define _LEVELMAP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include "tmxparser/Tmx.h"
#include "main_typedef.h"
#include "cTexture.h"

class levelMap{
	private:
		
		Tmx::Map* map;
		const Tmx::TileLayer* tileLayer;
		const Tmx::Tileset* tileset;
		SDL_Texture* levelTileSet;
		int tilesetColumns;
		int tilesetRows;

	public:

		int level_width;
		int level_height;
		int tile_width;
		int tile_height;

		levelMap(std::string fileName, SDL_Renderer* renderer, const SDL_PixelFormat* fmt);

		collisionState checkTileCollision(hitBox* characterFrame);

		void drawMapPortion(SDL_Renderer* renderer, SDL_Rect* camera);

		void free();
};
#endif
