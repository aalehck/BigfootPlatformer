#include "character.h"

character::character(SDL_Renderer* renderer, char* File, const SDL_PixelFormat* fmt){
	//Loading the surface using helper class, complains if it fucks up
	if ((texture = cTexture::loadTexture(renderer, File, fmt, 0, 0, 0, 0)) == NULL){
		printf("Failed to load yeti!\n");
	}

	isJumping = false;

	speedCoefficient = DOT_VEL/6;

	gravity = speedCoefficient/30;

	framecount = 0;
	totalcount = 4;

	int h, w;

	SDL_QueryTexture(texture, NULL, NULL, &h, &w);

	printf("h: %d\nw: %d", h, w);

	//Initialize the offsets
	cPosX = 0;
	cPosY = 0;

	//Initialize the velocity
	cVelX = 0;
	cVelY = 0;

	spritesheet[0].x = 10;
	spritesheet[0].y = 0;
	spritesheet[0].h = 100;
	spritesheet[0].w = 80;

	spritesheet[1].x = 90;
	spritesheet[1].y = 0;
	spritesheet[1].h = 100;
	spritesheet[1].w = 80;

	spritesheet[2].x = 170;
	spritesheet[2].y = 0;
	spritesheet[2].h = 100;
	spritesheet[2].w = 80;

	spritesheet[3].x = 250;
	spritesheet[3].y = 0;
	spritesheet[3].h = 100;
	spritesheet[3].w = 80;


	currentframe = &spritesheet[0];
}

void character::handleEvent(SDL_Event& e){
	//If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: 
			if(isJumping == true){
				break;
			}

			else{
				cVelY = (speedCoefficient/2); 
				cVelY -= speedCoefficient; 
				isJumping= true; 
				break;
			}
		//case SDLK_DOWN: cVelY += DOT_VEL; break;
		case SDLK_LEFT: cVelX -= DOT_VEL; break;
		case SDLK_RIGHT: cVelX += DOT_VEL; break;
		}

		currentframe = &spritesheet[(framecount++/2)];

		if((framecount/2) >= totalcount){
			framecount = 0;
		}
	}
	//If a key was released
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		//case SDLK_UP: cVelY += DOT_VEL; break;
		//case SDLK_DOWN: cVelY -= DOT_VEL; break;
		case SDLK_LEFT: cVelX += DOT_VEL; break;
		case SDLK_RIGHT: cVelX -= DOT_VEL; break;
		}

		currentframe = &spritesheet[0];
	}
	else if (e.key.repeat != 0){
		currentframe = &spritesheet[(framecount++/2)];

		if((framecount/2) >= totalcount){
			framecount = 0;
		}
	}
}

void character::move(double dt, levelMap* map){
	
	//apply gravity to y velocity
	if(cPosY < map->level_height - 100){
		cVelY = cVelY + gravity;
	}
	//printf("x: %d y: %d\n",cPosX, cPosY);

	//Move the dot left or right
	cPosX += cVelX * dt;
	//Move the dot up or down
	cPosY += cVelY;

	int h = 100;
	int w = 70;

	hitBox characterFrame = { cPosX, cPosY, w, h, cVelX, cVelY, isJumping};

	collisionState collision = map->checkTileCollision(&characterFrame);
	
	if(collision.collisionX == COLLISION_RIGHT || collision.collisionX == COLLISION_LEFT){
		cPosX = collision.adjustLocation.x;
	}

	if(collision.collisionY == COLLISION_TOP || collision.collisionY == COLLISION_BOTTOM){
		isJumping = false;
		cVelY = 0;
		cPosY = collision.adjustLocation.y;
	}
	//If the dot went too far to the left or right
	if (cPosX < 0)
	{
		//Move back
		cPosX = 0;
	}

	if(cPosX   > map->level_width - 80)
	{
		cPosX = map->level_width - 80;
	}
}

void character::render(SDL_Renderer* renderer, SDL_Rect* camera){

	cTexture::renderTexture(texture, renderer, cPosX - camera->x, cPosY - camera->y, currentframe);

}

void character::free(){

	cTexture::free(texture);
	texture = NULL;

	cPosX = 0;
	cPosY = 0;

	cVelX = 0;
	cVelY = 0;
}
