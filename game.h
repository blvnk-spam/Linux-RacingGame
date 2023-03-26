#include <stdbool.h>

#ifndef GAME
#define GAME

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define CELL_WIDTH_HEIGHT 32 //will be 40 later
#define SCREEN_WIDTH_SPACES SCREEN_WIDTH / CELL_WIDTH_HEIGHT //=40
#define SCREEN_HEIGHT_SPACES SCREEN_HEIGHT / CELL_WIDTH_HEIGHT //=22

#define NUM_OF_ENEMIES 1 //should be same value as in game.c

/* DEFINITIONS */
//Other stuff most likely needed here, this is just super basic

struct EnemyInfo
{
	int xPos;
	int yPos;
	int xMovement;
	int yMovement;
};

struct GameState {
	int noObjectsGameMap[SCREEN_WIDTH_SPACES][SCREEN_HEIGHT_SPACES];
	int currGameMap[SCREEN_WIDTH_SPACES][SCREEN_HEIGHT_SPACES];
	int currGameMapNum;
	bool finishedGameMap;
	struct EnemyInfo marioInfo;
	struct EnemyInfo map1MarioInitInfo;
	struct EnemyInfo map2MarioInitInfo;
	int LEN_ENEMIES;
	struct EnemyInfo enemies[NUM_OF_ENEMIES];
	struct EnemyInfo map1EnemiesInitInfo[NUM_OF_ENEMIES];
	struct EnemyInfo map2EnemiesInitInfo[NUM_OF_ENEMIES];
	int score;
	int lives;
	int timeLeftInSecs;
	bool gameWon;
	bool gameLost;
	bool levelWon;
	
};

//struct EnemyInfo enemies[1];

int map;
int gameRunning;

void run_game(); 
void runMap(int mapNumber);

#endif
