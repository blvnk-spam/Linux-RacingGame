#include <stdbool.h>
#include "input.h"
#include "drawPixels.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"
#include "menu.h"
#include "mario.c"
#include "coin.c"
#include "spike.c"
#include "castle.c"
#include "loseScreen.c"
#include "winScreen.c"
#include <wiringPi.h>
//#include <wiringPi.h>

//#define TRUE 0 
//#define FALSE 1

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define CELL_WIDTH_HEIGHT 32 //will be 40 later
#define SCREEN_WIDTH_SPACES SCREEN_WIDTH / CELL_WIDTH_HEIGHT
#define SCREEN_HEIGHT_SPACES SCREEN_HEIGHT / CELL_WIDTH_HEIGHT

#define NUM_OF_ENEMIES 1 //should be same value as in game.h

#define PRESSED 0 
#define NOT_PRESSED 1

#define BUTTON_ISNT_BEING_HELD_DOWN 0 
#define BUTTON_IS_BEING_HELD_DOWN 1

#define START 3
#define JOYPAD_UP 4
#define JOYPAD_DOWN 5
#define JOYPAD_LEFT 6
#define JOYPAD_RIGHT 7

#define SECS_BETWEEN_EACH_MOVE 1

#define MARIO 0
#define GRASS 1        
#define SPIKE 2
#define COIN 3
#define CLOCK 4
#define HEART 5
#define WATER 6                                     
#define CASTLE 7   

#define DELAY_BUTTON_INPUT_MICROSECS 300000 //should be same val in menu.c, game.c

//#define MARIO_INFO enemies[0]

int map;
int gameRunning;
/*
void wait(int microsecs){
    delayMicroseconds(microsecs);
}
*/
//typedef struct EnemyInfo;
/*
struct EnemyInfo
{
	int xPos;
	int yPos;
	int xMovement;
	int yMovement;
};
*/

int map1WithObjects[40][22] = {{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
	{1,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
	{1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1}, 
	{1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,4,1,1,1,1,1,1,1,3,1,1,1,1,1,5,1,7}};
	
int map1WithoutObjects[40][22] = {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7}};
	
int map2WithObjects[40][22] = {{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
	{1,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
	{1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1}, 
	{1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,4,1,1,1,1,1,1,1,3,1,1,1,1,1,5,1,7}};
	
int map2WithoutObjects[40][22] = {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7}};


void copyIntArr22RowsToOtherIntArr(int fromArr[][22], int toArr[][22], int cols, int rows){
	for(int currCol = 0; currCol < cols; currCol++){
		for(int currRow = 0; currRow < rows; currRow++){
			toArr[currCol][currRow] = fromArr[currCol][currRow];
		}
	}
}

struct GameState myGameState;

struct EnemyInfo enemies[1];
struct EnemyInfo marioInfo;

typedef struct {
	int xPos;
	int yPos;
} MapsMarioInitInfo;

MapsMarioInitInfo map1MarioInitInfo = {
.xPos = 0,
.yPos = 0
};

MapsMarioInitInfo map2MarioInitInfo = {
.xPos = 0,
.yPos = 0
};

struct EnemyInfo map1EnemiesInitInfo[NUM_OF_ENEMIES];
struct EnemyInfo map2EnemiesInitInfo[NUM_OF_ENEMIES];

void initMarioInfo(struct GameState *gameStateToInit){
	gameStateToInit -> map1MarioInitInfo.xPos = 0;
	gameStateToInit -> map1MarioInitInfo.yPos = 0;
	
	gameStateToInit -> map2MarioInitInfo.xPos = 0;
	gameStateToInit -> map2MarioInitInfo.yPos = 0;
	
	gameStateToInit -> marioInfo.xPos = gameStateToInit -> map1MarioInitInfo.xPos;
	gameStateToInit -> marioInfo.yPos = gameStateToInit -> map1MarioInitInfo.yPos;
}


void initEnemyInfo(struct GameState *gameStateToInit){
	//marioInfo.xPos = 0; mario is his own struct now
	//marioInfo.yPos = 0;
	//marioInfo.xMovement = 0; //mario uses custom movement so these shouldn't be needed
	//marioInfo.yMovement = 0;
	gameStateToInit -> map1EnemiesInitInfo[0].xPos = 1;
	gameStateToInit -> map1EnemiesInitInfo[0].yPos = 1;
	gameStateToInit -> map1EnemiesInitInfo[0].xMovement = 0;
	gameStateToInit -> map1EnemiesInitInfo[0].yMovement = 1;
	
	gameStateToInit -> map2EnemiesInitInfo[0].xPos = 1;
	gameStateToInit -> map2EnemiesInitInfo[0].yPos = 1;
	gameStateToInit -> map2EnemiesInitInfo[0].xMovement = 0;
	gameStateToInit -> map2EnemiesInitInfo[0].yMovement = 1;
	
	
	gameStateToInit -> enemies[0].xPos = gameStateToInit -> map1EnemiesInitInfo[0].xPos;
	gameStateToInit -> enemies[0].yPos = gameStateToInit -> map1EnemiesInitInfo[0].yPos;
	gameStateToInit -> enemies[0].xMovement = gameStateToInit -> map1EnemiesInitInfo[0].xMovement;
	gameStateToInit -> enemies[0].yMovement = gameStateToInit -> map1EnemiesInitInfo[0].yMovement;
}


void initGameStateStruct(struct GameState *gameStateToInit){
	copyIntArr22RowsToOtherIntArr(map1WithoutObjects, gameStateToInit -> noObjectsGameMap, 40, 22); 
	copyIntArr22RowsToOtherIntArr(map1WithObjects, gameStateToInit -> currGameMap, 40, 22); 
	initMarioInfo(gameStateToInit);
	initEnemyInfo(gameStateToInit);
	gameStateToInit -> LEN_ENEMIES = NUM_OF_ENEMIES;
	gameStateToInit -> currGameMapNum = 1;
	gameStateToInit -> finishedGameMap = false;
	gameStateToInit -> score = 0;
	gameStateToInit -> lives = 3;
	gameStateToInit -> timeLeftInSecs = 60;
	gameStateToInit -> gameWon = false;
	gameStateToInit -> gameLost = false;
	gameStateToInit -> levelWon = false;
}


void ifEnemyReachesEndOfScreenSwitchDirection(struct EnemyInfo *currEnemy){
	int currEnemyNewCellX = currEnemy -> xPos + currEnemy -> xMovement;
	int currEnemyNewCellY = currEnemy -> yPos + currEnemy -> yMovement;
	if(currEnemyNewCellX < 0 || currEnemyNewCellX > SCREEN_WIDTH_SPACES - 1){
		currEnemy -> xMovement *= -1;
	}
	if(currEnemyNewCellY < 0 || currEnemyNewCellY > SCREEN_HEIGHT_SPACES - 1){
		currEnemy -> yMovement *= -1;
	}
}

void changeMapUpdateInfo (int newMapNum) {
	myGameState.currGameMapNum = newMapNum;
	switch (newMapNum) {
		case 1: 
			changeMapUpdateMapInfo(map1WithoutObjects, map1WithObjects);
			changeMapUpdateMarioInfo(myGameState.map1MarioInitInfo);
			changeMapUpdateEnemyInfo(myGameState.map1EnemiesInitInfo);
			break;
		case 2: 
			changeMapUpdateMapInfo(map2WithoutObjects, map2WithObjects);
			changeMapUpdateMarioInfo(myGameState.map2MarioInitInfo);
			changeMapUpdateEnemyInfo(myGameState.map2EnemiesInitInfo);
			break;
	}
	myGameState.finishedGameMap = false;
}

void changeMapUpdateMapInfo (int mapWithoutObjects[][SCREEN_HEIGHT_SPACES], int mapWithObjects[][SCREEN_HEIGHT_SPACES]) {
	struct GameState *myGameStatePtr = &myGameState;
	copyIntArr22RowsToOtherIntArr(mapWithoutObjects, myGameStatePtr -> noObjectsGameMap, SCREEN_WIDTH_SPACES, SCREEN_HEIGHT_SPACES); 
	copyIntArr22RowsToOtherIntArr(mapWithObjects, myGameStatePtr -> currGameMap, SCREEN_WIDTH_SPACES, SCREEN_HEIGHT_SPACES); 
}

void changeMapUpdateMarioInfo (struct EnemyInfo newMapMarioInitInfo) {
	myGameState.marioInfo.xPos = newMapMarioInitInfo.xPos;
	myGameState.marioInfo.yPos = newMapMarioInitInfo.yPos;
}

void changeMapUpdateEnemyInfo (struct EnemyInfo newMapEnemiesInitInfo) {
	for(int i = 0; i < myGameState.LEN_ENEMIES; i++){
		myGameState.enemies[i].xPos = newMapEnemiesInitInfo.xPos;
		myGameState.enemies[i].yPos = newMapEnemiesInitInfo.yPos;
		myGameState.enemies[i].xMovement = newMapEnemiesInitInfo.xMovement;
		myGameState.enemies[i].yMovement = newMapEnemiesInitInfo.yMovement;
	}
}

void runGameDrawScreen(){
	initGameStateStruct(&myGameState);
	//initMarioInfo();
	//initEnemyInfo();
	int isStartButtonHeldDown = BUTTON_ISNT_BEING_HELD_DOWN;
	int startPressed = 0;
	clock_t clockMarkWhenGameStarted = clock();
	int isLeftButtonHeldDown = BUTTON_ISNT_BEING_HELD_DOWN;
	int isRightButtonHeldDown = BUTTON_ISNT_BEING_HELD_DOWN;
	int isUpButtonHeldDown = BUTTON_ISNT_BEING_HELD_DOWN;
	int isDownButtonHeldDown = BUTTON_ISNT_BEING_HELD_DOWN;
	float floatSecsSinceGameStarted = 0;
	int intSecsSinceGameStarted = 0;
	float clockMarkNow = clock();
	int prevSecsSinceGameStarted = 0;
	//short int *spritePtr;
	drawCurrMap();
	while(!startPressed){ 
		if(buttons_pressed_refined[START] == PRESSED && isStartButtonHeldDown == BUTTON_ISNT_BEING_HELD_DOWN){
			startPressed = 1;
		}
		if(!buttons_pressed_refined[START]){
			isStartButtonHeldDown = BUTTON_ISNT_BEING_HELD_DOWN;
		}			
	}
	delayMicroseconds(DELAY_BUTTON_INPUT_MICROSECS);// so that when you press start to start game, that input doesn't bleed over into the game, which would open up the menu
	//moveAndDrawEnemy(0, 0, &marioInfo, spritePtr);
	while(myGameState.lives > 0 && myGameState.timeLeftInSecs > 0 && myGameState.levelWon == 0 && gameRunning){
		clockMarkNow = clock() - clockMarkWhenGameStarted;
		floatSecsSinceGameStarted = (float) clockMarkNow / CLOCKS_PER_SEC;
		intSecsSinceGameStarted = (int) floatSecsSinceGameStarted;
		//float secsSinceGameStartedAtInterval = secsSinceGameStarted % 2
		if(myGameState.finishedGameMap){
			changeMapUpdateInfo(myGameState.currGameMapNum + 1);
		}
		if(prevSecsSinceGameStarted != intSecsSinceGameStarted && intSecsSinceGameStarted % SECS_BETWEEN_EACH_MOVE == 0){
			prevSecsSinceGameStarted = intSecsSinceGameStarted;
			ifEnemyReachesEndOfScreenSwitchDirection(&myGameState.enemies[0]);
			moveSpriteToCell(myGameState.enemies[0].xMovement, myGameState.enemies[0].yMovement, &myGameState.enemies[0], COIN);
			drawCurrMap();
			//spritePtr =(short int *) coin.pixel_data;
			//drawTile(myGameState.enemies[0].xPos, myGameState.enemies[0].yPos);
			//moveAndDrawEnemy(myGameState.enemies[0].xMovement, myGameState.enemies[0].yMovement, &myGameState.enemies[0], spritePtr);
			//printf("%d\n", intSecsSinceGameStarted);
		}
		
		if (buttons_pressed_refined[JOYPAD_UP] == PRESSED && isUpButtonHeldDown == BUTTON_ISNT_BEING_HELD_DOWN) {
			isUpButtonHeldDown = BUTTON_IS_BEING_HELD_DOWN;
			moveSpriteToCell(0, -1, &myGameState.marioInfo, MARIO);
			drawCurrMap();
			//spritePtr =(short int *) mario.pixel_data;
			//drawTile(myGameState.marioInfo.xPos, myGameState.marioInfo.yPos);
			//moveAndDrawEnemy(0, -1, &myGameState.marioInfo, spritePtr);
			//printf("UP\n");
			//drawPixelsLoop(0, -1);
		} else if (buttons_pressed_refined[JOYPAD_DOWN] == PRESSED && isDownButtonHeldDown == BUTTON_ISNT_BEING_HELD_DOWN) {
			isDownButtonHeldDown = BUTTON_IS_BEING_HELD_DOWN;
			moveSpriteToCell(0, 1, &myGameState.marioInfo, MARIO);
			drawCurrMap();
			//spritePtr =(short int *) mario.pixel_data;
			//drawTile(myGameState.marioInfo.xPos, myGameState.marioInfo.yPos);
			//moveAndDrawEnemy(0, 1, &myGameState.marioInfo, spritePtr);
			//printf("DOWN\n");
			//drawPixelsLoop(0, 1);
		} else if (buttons_pressed_refined[JOYPAD_LEFT] == PRESSED && isLeftButtonHeldDown == BUTTON_ISNT_BEING_HELD_DOWN) {
			isLeftButtonHeldDown = BUTTON_IS_BEING_HELD_DOWN;
			moveSpriteToCell(-1, 0, &myGameState.marioInfo, MARIO);
			drawCurrMap();
			//spritePtr =(short int *) mario.pixel_data;
			//drawTile(myGameState.marioInfo.xPos, myGameState.marioInfo.yPos);
			//moveAndDrawEnemy(-1, 0, &myGameState.marioInfo, spritePtr);
			//printf("LEFT\n");
			//drawPixelsLoop(-1, 0);
		} else if (buttons_pressed_refined[JOYPAD_RIGHT] == PRESSED && isRightButtonHeldDown == BUTTON_ISNT_BEING_HELD_DOWN) {
			isRightButtonHeldDown = BUTTON_IS_BEING_HELD_DOWN;
			moveSpriteToCell(1, 0, &myGameState.marioInfo, MARIO);
			drawCurrMap();
			//spritePtr =(short int *) mario.pixel_data;
			//drawTile(myGameState.marioInfo.xPos, myGameState.marioInfo.yPos);
			//moveAndDrawEnemy(1, 0, &myGameState.marioInfo, spritePtr);
			//printf("RIGHT\n");
			//drawPixelsLoop(1, 0);
		}else if(buttons_pressed_refined[START] == PRESSED && isStartButtonHeldDown == BUTTON_ISNT_BEING_HELD_DOWN){
			run_pause_menu();
			drawCurrMap();
			delayMicroseconds(DELAY_BUTTON_INPUT_MICROSECS);
		}	
		
		if(buttons_pressed_refined[START] == NOT_PRESSED){
			isStartButtonHeldDown = BUTTON_ISNT_BEING_HELD_DOWN;
		}
		if(buttons_pressed_refined[JOYPAD_UP] == NOT_PRESSED){
			isUpButtonHeldDown = BUTTON_ISNT_BEING_HELD_DOWN;
		}
		if(buttons_pressed_refined[JOYPAD_DOWN] == NOT_PRESSED){
			isDownButtonHeldDown = BUTTON_ISNT_BEING_HELD_DOWN;
		}
		if(buttons_pressed_refined[JOYPAD_LEFT] == NOT_PRESSED){
			isLeftButtonHeldDown = BUTTON_ISNT_BEING_HELD_DOWN;
		}
		if(buttons_pressed_refined[JOYPAD_RIGHT] == NOT_PRESSED){
			isRightButtonHeldDown = BUTTON_ISNT_BEING_HELD_DOWN;
		}
	}
	if(myGameState.lives == 0 || myGameState.timeLeftInSecs <= 0){
		myGameState.gameLost = true;
		gameRunning = 0;
	}//else{
		//map += 1;
	//}		
}

void runMap(int mapNumber){
    if(mapNumber == 1){
		runGameDrawScreen();
        //take input and print to frameBuffer from these??
    }else if (mapNumber == 2){
        //take input and print to frameBuffer from these??
    }else if(mapNumber == 3){
        //take input and print to frameBuffer from these??
    }else if(mapNumber == 4){
        //take input and print to frameBuffer from these??
    }
 }
 
 void run_game(){
    gameRunning = 1;
    map = 1;
    //game logic would go here.
    //some sort of variable to toggle what map displays.
    //some sort of variable to say declare game end
    
    while(gameRunning){
        if(map == 1){
            runMap(1);
        }else if(map == 2){
            runMap(2);
        }else if(map == 3){
            runMap(3);
        }else if(map ==4){
            runMap(4);
        }
    }
    
    //actually put code here to distinguish if player has won or lost
    if(myGameState.gameLost == true){
		short int *loseScreenPtr=(short int *) loseScreen.pixel_data;
		drawBackground(loseScreenPtr);
		//printf("You lost!\n"); //replace with print of losing screen.
		delayMicroseconds(DELAY_BUTTON_INPUT_MICROSECS);
		while(1){
			for(int i = 0; i < 12; i++){
				if (buttons_pressed_refined[i] == PRESSED) {
					goto onceInputReadAfterLoss;
				}
			}
		}
		onceInputReadAfterLoss: ;
		delayMicroseconds(DELAY_BUTTON_INPUT_MICROSECS);
		//exit(0);
	}else if(myGameState.gameWon == true){
		short int *winScreenPtr=(short int *) winScreen.pixel_data;
		drawBackground(winScreenPtr);
		//printf("You won!\n"); //replace with print of winning screen. 
		delayMicroseconds(DELAY_BUTTON_INPUT_MICROSECS);
		while(1){
			for(int i = 0; i < 12; i++){
				if (buttons_pressed_refined[i] == PRESSED) {
					goto onceInputReadAfterWin;
				}
			}
		}
		onceInputReadAfterWin: ;
		delayMicroseconds(DELAY_BUTTON_INPUT_MICROSECS);
		//exit(0);
    }
    
}
