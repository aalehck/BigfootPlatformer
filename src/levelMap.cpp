#include "levelMap.h"

levelMap::levelMap(std::string fileName, SDL_Renderer* renderer, const SDL_PixelFormat* fmt){
	map = new Tmx::Map();
	map->ParseFile(fileName);

	char* namething = "./textures/foresttile.png";

	printf("namething: %s", namething);

	levelTileSet = cTexture::loadTexture(renderer, namething, fmt);

	tileLayer = map->GetTileLayer(0);

	tileset = map->GetTileset(0);
	//comment

	tile_width = map->GetTileWidth();
	tile_height = map->GetTileHeight();
	level_width = map->GetWidth() * tile_width;
	level_height = map->GetHeight() * tile_height;
	tilesetColumns = (tileset->GetImage()->GetWidth()) / tile_width;
	tilesetRows = (tileset->GetImage()->GetHeight()) / tile_height;
}

collisionState levelMap::checkTileCollision(hitBox* characterFrame){

	collisionState collision = {{characterFrame->x, characterFrame->y}, COLLISION_NONE, COLLISION_NONE};


	//calculate range of tiles for character to check for collisions
	int heightDiv = ceil((float)(characterFrame->h) / (float)(tile_height));
	int hRemainder = characterFrame->h % tile_height;

	int widthDiv = ceil((float)(characterFrame->w) / (float)(tile_width));
 	int wRemainder = characterFrame->w % tile_width;

	int i = floor((float)(characterFrame->x) / (float)(tile_width));
	int j = floor((float)(characterFrame->y) / (float)(tile_height));

	//printf("%d %d %d %d\n", characterFrame->h,  heightDiv, characterFrame->w,  widthDiv);

	int yPix = j * 24;
	int xPix = i * 24;

	float xCollisionTime = 0.0f;
	float yCollisionTime = 0.0f;

	/*
	for(int y = j; y < j + heightDiv; ++y){

		if(tileLayer->GetTileTilesetIndex(i, y) != -1 && characterFrame->x < (xPix + tile_width) && characterFrame->vx < 0){
			collision.collisionX = COLLISION_LEFT;
			collision.adjustLocation.x = (i * tile_width) + tile_width;
			xCollisionTime = ((float)(characterFrame->x) - ((float)(i * tile_width) + (float)(tile_width))) / -(float)(characterFrame->vx);

			break;
		}
		else if(tileLayer->GetTileTilesetIndex(i + widthDiv, y) != -1 && (characterFrame->x + characterFrame->w) > xPix && characterFrame->vx > 0){
			collision.collisionX = COLLISION_RIGHT;
			collision.adjustLocation.x = (i * tile_width);
			xCollisionTime = ((float)(i * tile_width) - ((float)(characterFrame->x) + (float)(tile_width))) / (float)(characterFrame->vx);
			//i = collision.adjustLocation.x / tile_width;
			//xPix = collision.adjustLocation.x;

			break;
		}
	}
	
	for(int x = i; x < i + widthDiv; ++x){

		if(tileLayer->GetTileTilesetIndex(x, j) != -1 && characterFrame->y < yPix){
			collision.collisionY = COLLISION_TOP;
			collision.adjustLocation.y = (j * tile_height) + tile_height;
			yCollisionTime = ((float)(j * tile_width) - ((float)(characterFrame->y) + (float)(tile_height))) / (float)(characterFrame->vy);
			//j = j + tile_height;
			break;
		}
		else if(tileLayer->GetTileTilesetIndex(x, j + heightDiv) != -1  && (characterFrame->y + characterFrame->h) > yPix){
			collision.collisionY = COLLISION_BOTTOM;
			collision.adjustLocation.y = j * tile_height;
			yCollisionTime = ((float)(characterFrame->y) - ((float)(j * tile_width) + (float)(tile_height))) / -(float)(characterFrame->vy);

			break;
		}
	}
	*/

	
	for(int y = j; y < j + heightDiv; ++y){
		for(int x = i; x < i + widthDiv; ++x){
			if(tileLayer->GetTileTilesetIndex(x, y) != -1){
					yPix = y * tile_height;
					xPix = x * tile_width;
					printf("should collide\n");
					if(characterFrame->x < (xPix + tile_width) && characterFrame->vx < 0){
						printf("left\n");
						collision.collisionX = COLLISION_LEFT;
						collision.adjustLocation.x = xPix + tile_width;	
					}
					else if((characterFrame->x + characterFrame->w) > xPix  && characterFrame->vx < 0){
						printf("right\n");
						collision.collisionX = COLLISION_RIGHT;
						collision.adjustLocation.x = xPix - tile_width;
					}
						
					if(characterFrame->y < yPix){
						printf("top\n");
						collision.collisionY = COLLISION_TOP;
						collision.adjustLocation.y = yPix + tile_height;
					}
					else if((characterFrame->y + characterFrame->h) > yPix){
						printf("bottom\n");
						collision.collisionY = COLLISION_BOTTOM;
						collision.adjustLocation.y = yPix - tile_height;
					}
					/*
					int cCenterX = characterFrame->x + 12;
					int cCenterY = characterFrame->y + 12;
					
					int tCenterX = xPix + 12;
					int tCenterY = yPix + 12;

					int xd = abs((tCenterX * tCenterX) + (cCenterX * cCenterX));
					int yd = abs((tCenterY * tCenterY) + (cCenterY * cCenterY));

					if(xd < yd){
						if(cCenterX < tCenterX){
							//right side
							collision.collisionX = COLLISION_RIGHT;
							collision.adjustLocation.x = xPix;
						}
						else{
							//left side
							collision.collisionX = COLLISION_LEFT;
							collision.adjustLocation.x = xPix + tile_width;
						}
						return collision;
					}
					else if(yd < xd){
						if(cCenterY < tCenterY){
							//bottom side
							collision.collisionY = COLLISION_BOTTOM;
							collision.adjustLocation.y = yPix;
						}
						else{
							//top side
							collision.collisionY = COLLISION_TOP;
							collision.adjustLocation.y = yPix + tile_height;
						}
						return collision;
					}
					*/
			}
		}
	}
	

	if(characterFrame->isJumping){
		/*if(yCollisionTime > xCollisionTime){
			collision.adjustLocation.x = characterFrame->x;
			collision.collisionX = COLLISION_NONE;
		}
		else if(xCollisionTime > yCollisionTime){
			collision.adjustLocation.y = characterFrame->y;
			collision.collisionY = COLLISION_NONE;
			}*/
		if(characterFrame->vy > characterFrame->vx){
			collision.adjustLocation.x = characterFrame->x;
		}
		else {
			collision.adjustLocation.y = characterFrame->y;
		}
	}
	
	
	return collision;
}

void levelMap::drawMapPortion(SDL_Renderer* renderer, SDL_Rect* camera){

	int heightDiv = camera->h / tile_height;
	int hRemainder = camera->h % tile_height;

	if( hRemainder != 0)
		heightDiv = heightDiv + 3;

	int widthDiv = camera->w / tile_width;
 	int wRemainder = camera->w % tile_width;

 	if(wRemainder != 0)
 		widthDiv = widthDiv + 3;

	int i = camera->x / tile_width;

	if(i % tile_width != 0 && i != 0){
		--i;
	}

	int j = camera->y / tile_height;

	if(j % tile_width != 0 && j != 0){
		--j;
	}

 	for(int x = i; x < i + widthDiv; ++x){
 		for(int y = j; y < j + heightDiv; ++y){

 			int tileCheck = tileLayer->GetTileTilesetIndex(x, y);

 			if(tileCheck != -1){

 				int tileIndex = tileLayer->GetTileId(x, y);
 				int clipY = tileIndex / tilesetColumns;
 				int clipX = tileIndex - (clipY * tilesetColumns);

 				SDL_Rect clip = {clipX*tile_width, clipY*tile_height, tile_width, tile_height};

 				cTexture::renderTexture(levelTileSet, renderer, (x*24) - camera->x, (y*24) - camera->y, &clip);
 			}
 		}
 	}

}

void levelMap::free(){
	cTexture::free(levelTileSet);
}
