#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include "framebuffer.h"
#include "grass.c"
#include "spike.c"
#include "mario.c"
#include "coin.c"
#include "clock.c"
#include "heart.c"
#include "castle.c"
#include "menu.h"
#include "game.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define CELL_WIDTH_HEIGHT 32 //will be 40 later
#define SCREEN_WIDTH_SPACES SCREEN_WIDTH / CELL_WIDTH_HEIGHT
#define SCREEN_HEIGHT_SPACES SCREEN_HEIGHT / CELL_WIDTH_HEIGHT

#define MARIO 0
#define GRASS 1
#define SPIKE 2
#define COIN 3
#define CLOCK 4
#define HEART 5
#define WATER 6
#define CASTLE 7 

/* Definitions */
typedef struct {
	short int color;
	int x, y;
} Pixel;

typedef struct {
	int xPos;
	int yPos;
} Sprite;

Sprite sprite = {
.xPos = 0,
.yPos = 0
};



Sprite spikeSprite = {
.xPos = 4,
.yPos = 5
};


//sprite = malloc(sizeof(Sprite));


//extern int map1[40][22];
extern struct GameState myGameState;

void copyIntArrToOtherIntArr(int fromArr[][22], int toArr[][22], int cols, int rows){
	for(int currCol = 0; currCol < cols; currCol++){
		for(int currRow = 0; currRow < rows; currRow++){
			toArr[currCol][currRow] = fromArr[currCol][currRow];
		}
	}
}

struct fbs framebufferstruct;
void drawPixel(Pixel *pixel);
int boolean = 0;

//void drawBackground(int mapNum){
void drawCurrMap(){
	if(boolean == 0){
		framebufferstruct = initFbInfo();
		boolean = 1;
	}
/*	
	int currMap[40][22];
	
	switch(mapNum){
		case 1:
			copyIntArrToOtherIntArr(myGameState.initialGameMap, currMap, 40, 22);
			break;
		default:
			break;
	}
*/
	short int *grassPtr=(short int *) grass.pixel_data;
	short int *marioPtr=(short int *) mario.pixel_data;
	short int *spikePtr=(short int *) spike.pixel_data;
	short int *coinPtr=(short int *) coin.pixel_data;
	short int *clockPtr=(short int *) clock.pixel_data;
	short int *heartPtr=(short int *) heart.pixel_data;
	short int *castlePtr=(short int *) castle.pixel_data;
	
	/* initialize a pixel */
	Pixel *pixel;

	pixel = malloc(sizeof(Pixel));
	
	//int i=0;
	//unsigned int quarter,byte,word;
	
	//int previousCell; 
	for (int whichCellY = 0; whichCellY < SCREEN_HEIGHT_SPACES; whichCellY++)
	{
		for (int whichCellX = 0; whichCellX < SCREEN_WIDTH_SPACES; whichCellX++) 
		{	
			for (int withinCellY = 0; withinCellY < CELL_WIDTH_HEIGHT; withinCellY++)
			{
				for (int withinCellX = 0; withinCellX < CELL_WIDTH_HEIGHT; withinCellX++) 
				{	
					int withinCellPixelIdx = (withinCellY * CELL_WIDTH_HEIGHT) + withinCellX;
					pixel->x = (whichCellX * CELL_WIDTH_HEIGHT) + withinCellX;
					pixel->y = (whichCellY * CELL_WIDTH_HEIGHT) + withinCellY;

					if(myGameState.currGameMap[whichCellX][whichCellY] == MARIO){
						pixel->color = marioPtr[withinCellPixelIdx];
					} else if (myGameState.currGameMap[whichCellX][whichCellY] == GRASS){
						pixel->color = grassPtr[withinCellPixelIdx];
					} else if(myGameState.currGameMap[whichCellX][whichCellY] == SPIKE){
						pixel->color = spikePtr[withinCellPixelIdx];
					} else if(myGameState.currGameMap[whichCellX][whichCellY] == COIN){
						pixel->color = coinPtr[withinCellPixelIdx];
					}  else if(myGameState.currGameMap[whichCellX][whichCellY] == CLOCK){
						pixel->color = clockPtr[withinCellPixelIdx];
					}  else if(myGameState.currGameMap[whichCellX][whichCellY] == HEART){
						pixel->color = heartPtr[withinCellPixelIdx];
					}  else if(myGameState.currGameMap[whichCellX][whichCellY] == CASTLE){
						pixel->color = castlePtr[withinCellPixelIdx];
					} 
					
					drawPixel(pixel);
/*					
					if(whichCellY == (sprite.yPos) && whichCellX == (sprite.xPos) && map1[whichCellX + x_offset][whichCellY + y_offset] == SPIKE) {
						pixel->color = marioPtr[withinCellPixelIdx];
						
						
						sprite.xPos -= x_offset;
						sprite.yPos -= y_offset;
						
						
						//subtract a life
						
					} else if(whichCellY == (sprite.yPos + y_offset) && whichCellX == (sprite.xPos + x_offset) && map1[whichCellY][whichCellX] != SPIKE){
						pixel->color = marioPtr[withinCellPixelIdx];
					} 
*/
					
					//if(whichCellY == sprite.yPos && whichCellX == sprite.xPos)
					//{
					//	pixel->color = marioPtr[withinCellPixelIdx];
					
						//drawPixel(pixel);
					//} else if (whichCellY == spikeSprite.yPos && whichCellX == spikeSprite.xPos){
						

						//drawPixel(pixel);

					
					

					
					//if (whichCellX + sprite.xPos + x_offset >= 0) {
						
						
					//}
				}
			}
		}
	}
	//sprite.xPos += x_offset;
	//sprite.yPos += y_offset;

	/* free pixel's allocated memory */
	free(pixel); 
	pixel = NULL;
	//munmap(framebufferstruct.fptr, framebufferstruct.screenSize);
	return;
}

void drawTile(int tileX, int tileY){
	if(boolean == 0){
		framebufferstruct = initFbInfo();
		boolean = 1;
	}
	
	short int *grassPtr=(short int *) grass.pixel_data;
	//short int *marioPtr=(short int *) mario.pixel_data;
	short int *spikePtr=(short int *) spike.pixel_data;
	
	/* initialize a pixel */
	Pixel *pixel;

	pixel = malloc(sizeof(Pixel));
	
	//int previousCell; 
	for (int whichCellY = 0; whichCellY < SCREEN_HEIGHT_SPACES; whichCellY++)
	{
		for (int whichCellX = 0; whichCellX < SCREEN_WIDTH_SPACES; whichCellX++) 
		{	
			if((whichCellX != tileX || whichCellY != tileY)){
				//(whichCellX != enemy -> xPos || whichCellY != enemy -> yPos) && 
				continue;
			}
			for (int withinCellY = 0; withinCellY < CELL_WIDTH_HEIGHT; withinCellY++)
			{
				for (int withinCellX = 0; withinCellX < CELL_WIDTH_HEIGHT; withinCellX++) 
				{	
					int withinCellPixelIdx = (withinCellY * CELL_WIDTH_HEIGHT) + withinCellX;
					pixel->x = (whichCellX * CELL_WIDTH_HEIGHT) + withinCellX;
					pixel->y = (whichCellY * CELL_WIDTH_HEIGHT) + withinCellY;

					if (myGameState.currGameMap[whichCellX][whichCellY] == GRASS){
						pixel->color = grassPtr[withinCellPixelIdx];
					} else if(myGameState.currGameMap[whichCellX][whichCellY] == SPIKE){
						pixel->color = spikePtr[withinCellPixelIdx];
					}
					drawPixel(pixel);
				}
			}
		}
	}

	free(pixel); 
	pixel = NULL;
	//munmap(framebufferstruct.fptr, framebufferstruct.screenSize);
	return;
}


void moveSpriteToCell(int x_offset, int y_offset, struct EnemyInfo *enemy, int spriteCode)
{
	if(myGameState.currGameMap[enemy -> xPos][enemy -> yPos] != spriteCode){
		return;
	}
	int newCellX = enemy -> xPos + x_offset;
	int newCellY = enemy -> yPos + y_offset;
	
	bool spikeMovesOntoMario = spriteCode == SPIKE && myGameState.currGameMap[newCellX][newCellY] == MARIO;
	bool marioMovesOntoSpike = spriteCode == MARIO && myGameState.currGameMap[newCellX][newCellY] == SPIKE;
	if(spikeMovesOntoMario || marioMovesOntoSpike){
		myGameState.lives = myGameState.lives - 1;
		//printf("lives: %d\n", myGameState.lives); // will get rid of later
		if(spikeMovesOntoMario){
			myGameState.currGameMap[newCellX-x_offset][newCellY-y_offset] = myGameState.noObjectsGameMap[newCellX-x_offset][newCellY-y_offset];
			return;
		}
	} 
	
	bool coinMovesOntoMario = spriteCode == COIN && myGameState.currGameMap[newCellX][newCellY] == MARIO;
	bool marioMovesOntoCoin = spriteCode == MARIO && myGameState.currGameMap[newCellX][newCellY] == COIN;
	if(coinMovesOntoMario || marioMovesOntoCoin){
		myGameState.score = myGameState.score + 1;
		//printf("coins: %d\n", myGameState.score); // will get rid of later
		if(coinMovesOntoMario){
			myGameState.currGameMap[newCellX-x_offset][newCellY-y_offset] = myGameState.noObjectsGameMap[newCellX-x_offset][newCellY-y_offset];
			return;
		}
	} 
	
	bool clockMovesOntoMario = spriteCode == CLOCK && myGameState.currGameMap[newCellX][newCellY] == MARIO;
	bool marioMovesOntoClock = spriteCode == MARIO && myGameState.currGameMap[newCellX][newCellY] == CLOCK;
	if(clockMovesOntoMario || marioMovesOntoClock){
		myGameState.timeLeftInSecs = myGameState.timeLeftInSecs + 10;
		//printf("time left: %d\n", myGameState.timeLeftInSecs); // will get rid of later
		if(clockMovesOntoMario){
			myGameState.currGameMap[newCellX-x_offset][newCellY-y_offset] = myGameState.noObjectsGameMap[newCellX-x_offset][newCellY-y_offset];
			return;
		}
	} 
	
	bool heartMovesOntoMario = spriteCode == HEART && myGameState.currGameMap[newCellX][newCellY] == MARIO;
	bool marioMovesOntoHeart = spriteCode == MARIO && myGameState.currGameMap[newCellX][newCellY] == HEART;
	if(heartMovesOntoMario || marioMovesOntoHeart){
		myGameState.lives = myGameState.lives + 1;
		//printf("lives: %d\n", myGameState.lives); // will get rid of later
		if(heartMovesOntoMario){
			myGameState.currGameMap[newCellX-x_offset][newCellY-y_offset] = myGameState.noObjectsGameMap[newCellX-x_offset][newCellY-y_offset];
			return;
		}
	} 
	
	bool castleMovesOntoMario = spriteCode == CASTLE && myGameState.currGameMap[newCellX][newCellY] == MARIO;
	bool marioMovesOntoCastle = spriteCode == MARIO && myGameState.currGameMap[newCellX][newCellY] == CASTLE;
	if(castleMovesOntoMario || marioMovesOntoCastle){
		myGameState.finishedGameMap = true;
		if(castleMovesOntoMario){
			myGameState.currGameMap[newCellX-x_offset][newCellY-y_offset] = myGameState.noObjectsGameMap[newCellX-x_offset][newCellY-y_offset];
			return;
		}
	} 
	
	bool newCellOutOfBoundsLeft = newCellX  < 0;
	bool newCellOutOfBoundsRight = newCellX  > SCREEN_WIDTH_SPACES - 1;
	bool newCellOutOfBoundsUp = newCellY  < 0;
	bool newCellOutOfBoundsDown = newCellY  > SCREEN_HEIGHT_SPACES - 1;
	
	if(myGameState.currGameMap[newCellX][newCellY] != WATER && !newCellOutOfBoundsLeft  && !newCellOutOfBoundsRight  && !newCellOutOfBoundsUp  && !newCellOutOfBoundsDown){
		//update currGameMap
		myGameState.currGameMap[newCellX][newCellY] = spriteCode;
		myGameState.currGameMap[newCellX-x_offset][newCellY-y_offset] = myGameState.noObjectsGameMap[newCellX-x_offset][newCellY-y_offset];
		enemy -> xPos += x_offset;
		enemy -> yPos += y_offset;
	}
}

int objectHasBeenDrawnYet = 0;

//typedef struct EnemyInfo;
void moveAndDrawEnemy(int x_offset, int y_offset, struct EnemyInfo *enemy, short int *spritePtr)
{
	if(objectHasBeenDrawnYet == 0){
		framebufferstruct = initFbInfo();
		objectHasBeenDrawnYet = 1;
	}

	/* initialize a pixel */
	Pixel *pixel;

	pixel = malloc(sizeof(Pixel));
	
	for (int whichCellY = 0; whichCellY < SCREEN_HEIGHT_SPACES; whichCellY++)
	{
		for (int whichCellX = 0; whichCellX < SCREEN_WIDTH_SPACES; whichCellX++) 
		{	
			if((whichCellX != (enemy -> xPos + x_offset) || whichCellY != (enemy -> yPos + y_offset))){
				//(whichCellX != enemy -> xPos || whichCellY != enemy -> yPos) && 
				continue;
			}
			for (int withinCellY = 0; withinCellY < CELL_WIDTH_HEIGHT; withinCellY++)
			{
				for (int withinCellX = 0; withinCellX < CELL_WIDTH_HEIGHT; withinCellX++) 
				{	
					int withinCellPixelIdx = (withinCellY * CELL_WIDTH_HEIGHT) + withinCellX;
					pixel->x = (whichCellX * CELL_WIDTH_HEIGHT) + withinCellX;
					pixel->y = (whichCellY * CELL_WIDTH_HEIGHT) + withinCellY;
	
					//pixel->color = spritePtr[withinCellPixelIdx]; //used if you dont care about moving object colliding with other object, and gets drawn on top
					//drawPixel(pixel);
					
					if(whichCellY == (enemy -> yPos) && whichCellX == (enemy -> xPos) && myGameState.currGameMap[whichCellX + x_offset][whichCellY + y_offset] == SPIKE) {
						pixel->color = spritePtr[withinCellPixelIdx];
						
						enemy -> xPos -= x_offset;
						enemy -> yPos -= y_offset;
						drawPixel(pixel);
						
						//subtract a life
						
					} else if(whichCellY == (enemy -> yPos + y_offset) && whichCellX == (enemy -> xPos + x_offset) && myGameState.currGameMap[whichCellY][whichCellX] != SPIKE){
						pixel->color = spritePtr[withinCellPixelIdx];
						drawPixel(pixel);
					}
					

					
				}
			}
		}
	}
	enemy -> xPos += x_offset;
	enemy -> yPos += y_offset;

	/* free pixel's allocated memory */
	free(pixel); 
	pixel = NULL;
	//munmap(framebufferstruct.fptr, framebufferstruct.screenSize);
	return;
}

int marioHasBeenDrawnYet = 0;
void moveAndDrawMario(int x_offset, int y_offset, struct EnemyInfo *enemy, short int *spritePtr)
{
	if(marioHasBeenDrawnYet == 0){
		framebufferstruct = initFbInfo();
		marioHasBeenDrawnYet = 1;
	}
		
	
	
	 // initialize a pixel
	Pixel *pixel;

	pixel = malloc(sizeof(Pixel));
	
	for (int whichCellY = 0; whichCellY < SCREEN_HEIGHT_SPACES; whichCellY++)
	{
		for (int whichCellX = 0; whichCellX < SCREEN_WIDTH_SPACES; whichCellX++) 
		{	
			if((whichCellX != (enemy -> xPos + x_offset) || whichCellY != (enemy -> yPos + y_offset))){
				//(whichCellX != enemy -> xPos || whichCellY != enemy -> yPos) && 
				continue;
			}
			for (int withinCellY = 0; withinCellY < CELL_WIDTH_HEIGHT; withinCellY++)
			{
				for (int withinCellX = 0; withinCellX < CELL_WIDTH_HEIGHT; withinCellX++) 
				{	
					int withinCellPixelIdx = (withinCellY * CELL_WIDTH_HEIGHT) + withinCellX;
					pixel->x = (whichCellX * CELL_WIDTH_HEIGHT) + withinCellX;
					pixel->y = (whichCellY * CELL_WIDTH_HEIGHT) + withinCellY;
	
					//pixel->color = spritePtr[withinCellPixelIdx]; //used if you dont care about moving object colliding with other object, and gets drawn on top
					//drawPixel(pixel);
					
					if(whichCellY == (enemy -> yPos) && whichCellX == (enemy -> xPos) && myGameState.currGameMap[whichCellX + x_offset][whichCellY + y_offset] == SPIKE) {
						pixel->color = spritePtr[withinCellPixelIdx];
						
						enemy -> xPos -= x_offset;
						enemy -> yPos -= y_offset;
						drawPixel(pixel);
						
						//subtract a life
						
					} else if(whichCellY == (enemy -> yPos + y_offset) && whichCellX == (enemy -> xPos + x_offset) && myGameState.currGameMap[whichCellY][whichCellX] != SPIKE){
						pixel->color = spritePtr[withinCellPixelIdx];
						drawPixel(pixel);
					}
					

					
				}
			}
		}
	}
	enemy -> xPos += x_offset;
	enemy -> yPos += y_offset;

	// free pixel's allocated memory 
	free(pixel); 
	pixel = NULL;
	//munmap(framebufferstruct.fptr, framebufferstruct.screenSize);
	return;
}


/* Draw a pixel */
void drawPixel(Pixel *pixel){
	long int location =(pixel->x +framebufferstruct.xOff) * (framebufferstruct.bits/8) +
                       (pixel->y+framebufferstruct.yOff) * framebufferstruct.lineLength;
	*((unsigned short int*)(framebufferstruct.fptr + location)) = pixel->color;
}
