#include "input.h"
#include "drawPixels.h"
#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include "menuBackground.c"
#include "quitButtonDeselected.c"
#include "quitButtonSelected.c"
#include "startButtonDeselected.c"
#include "startButtonSelected.c"
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include "framebuffer.h"
#include <wiringPi.h>

#define TRUE 0 
#define FALSE 1

/*
#define drawStartButton 0 
#define drawPauseButton 1
#define buttonSelected 0
#define buttonDeselected 1
*/

#define PRESSED 0 
#define NOT_PRESSED 1

#define BUTTON_ISNT_BEING_HELD_DOWN 0 
#define BUTTON_IS_BEING_HELD_DOWN 1

#define START_GAME 0
#define QUIT_GAME 1

#define START 3
#define A_BUTTON 8
#define JOYPAD_UP 4
#define JOYPAD_DOWN 5
#define JOYPAD_LEFT 6
#define JOYPAD_RIGHT 7

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define START_BUTTON_XPOS 400
#define START_BUTTON_YPOS 260

#define QUIT_BUTTON_XPOS 400
#define QUIT_BUTTON_YPOS 490

#define DELAY_BUTTON_INPUT_MICROSECS 300000 //should be same val in menu.c, game.c

///made scope of these greater so can be used by all subsequent functions
int isButtonHeldDown = BUTTON_ISNT_BEING_HELD_DOWN;
	
short int *menuButtonPtr= 0;
unsigned int menuButtonWidth = 0;
unsigned int menuButtonHeight = 0;
///

typedef struct {
	int button_selected;
} Menu;

	/* Definitions */
typedef struct {
	short int color;
	int x, y;
} Pixel;
	
struct fbs framebufferstruct;
//void drawPixel(Pixel *pixel);

int framebufferstructForMenuBackgroundCreated = 0;
void drawBackground(short int *backgroundPtr){
	
	if(framebufferstructForMenuBackgroundCreated == 0){
		framebufferstruct = initFbInfo();
		framebufferstructForMenuBackgroundCreated = 1;
	}
	
		
	//short int *menuBackgroundPtr=(short int *) menuBackground.pixel_data;
	
	/* initialize a pixel */
	Pixel *pixel;

	pixel = malloc(sizeof(Pixel));
	
	//int i=0;
	//unsigned int quarter,byte,word;
	
	//int previousCell; 
	for (int currPixelY = 0; currPixelY < SCREEN_HEIGHT; currPixelY++)
	{
		for (int currPixelX = 0; currPixelX < SCREEN_WIDTH; currPixelX++) 
		{	
			pixel->x = currPixelX;
			pixel->y = currPixelY;
			int pixelIdx = (currPixelY * SCREEN_WIDTH) + currPixelX;
			pixel->color = backgroundPtr[pixelIdx];
			
			drawPixel(pixel);
		}
	}

	/* free pixel's allocated memory */
	free(pixel); 
	pixel = NULL;
	//munmap(framebufferstruct.fptr, framebufferstruct.screenSize);
	return;
}

void drawImage(short int *backgroundPtr, int xOffset, int yOffset, int imageWidth, int imageHeight){
	
	if(framebufferstructForMenuBackgroundCreated == 0){
		framebufferstruct = initFbInfo();
		framebufferstructForMenuBackgroundCreated = 1;
	}
	
		
	//short int *menuBackgroundPtr=(short int *) menuBackground.pixel_data;
	
	/* initialize a pixel */
	Pixel *pixel;

	pixel = malloc(sizeof(Pixel));
	
	//int i=0;
	//unsigned int quarter,byte,word;
	
	//int previousCell; 
	for (int currPixelY = yOffset; currPixelY < yOffset + imageHeight; currPixelY++)
	{
		for (int currPixelX = xOffset; currPixelX < xOffset + imageWidth; currPixelX++) 
		{	
			pixel->x = currPixelX;
			pixel->y = currPixelY;
			int pixelIdx = (currPixelY * SCREEN_WIDTH) + currPixelX;
			pixel->color = backgroundPtr[pixelIdx];
			
			drawPixel(pixel);
		}
	}

	/* free pixel's allocated memory */
	free(pixel); 
	pixel = NULL;
	//munmap(framebufferstruct.fptr, framebufferstruct.screenSize);
	return;
}





//////////////START OF drawMenuButton////////////////






int framebufferstructForMenuButtonCreated = 0;
void drawMenuButton(short int *menuButtonPixelDataPtr, unsigned int buttonWidth, unsigned int buttonHeight, int buttonXPos, int buttonYPos){
	
	if(framebufferstructForMenuButtonCreated == 0){
		framebufferstruct = initFbInfo();
		framebufferstructForMenuButtonCreated = 1;
	}
	
	/* initialize a pixel */
	Pixel *pixel;

	pixel = malloc(sizeof(Pixel));
	
	//int i=0;
	//unsigned int quarter,byte,word;
	
	//int previousCell; 
	for (int withinButtonCurrPixelY = 0; withinButtonCurrPixelY < buttonHeight; withinButtonCurrPixelY++)
	{
		for (int withinButtonCurrPixelX = 0; withinButtonCurrPixelX < buttonWidth; withinButtonCurrPixelX++) 
		{	
			pixel->x = buttonXPos + withinButtonCurrPixelX;
			pixel->y = buttonYPos + withinButtonCurrPixelY;
			int withinButtonPixelIdx = (withinButtonCurrPixelY * buttonWidth) + withinButtonCurrPixelX;
			pixel->color = menuButtonPixelDataPtr[withinButtonPixelIdx];
			
			drawPixel(pixel);
		}
	}

	/* free pixel's allocated memory */
	free(pixel); 
	pixel = NULL;
	//munmap(framebufferstruct.fptr, framebufferstruct.screenSize);
	return;
}


///Code to switch which button is being highlighted. 
void quitSelected(Menu* menu){
	menu -> button_selected = QUIT_GAME;
	isButtonHeldDown = BUTTON_IS_BEING_HELD_DOWN;
	
	short int *menuBackgroundPtr=(short int *) menuBackground.pixel_data;
	drawBackground(menuBackgroundPtr);
	menuButtonPtr=(short int *) startButtonDeselected.pixel_data;
	menuButtonWidth = startButtonDeselected.width;
	menuButtonHeight = startButtonDeselected.height;
	drawMenuButton(menuButtonPtr, menuButtonWidth, menuButtonHeight, START_BUTTON_XPOS, START_BUTTON_YPOS);
	menuButtonPtr=(short int *) quitButtonSelected.pixel_data;
	menuButtonWidth = quitButtonSelected.width;
	menuButtonHeight = quitButtonSelected.height;
	drawMenuButton(menuButtonPtr, menuButtonWidth, menuButtonHeight, QUIT_BUTTON_XPOS, QUIT_BUTTON_YPOS);
}
	
void startSelected(Menu* menu){
	menu -> button_selected = START_GAME;
	isButtonHeldDown = BUTTON_IS_BEING_HELD_DOWN; 
	short int *menuBackgroundPtr=(short int *) menuBackground.pixel_data;
	drawBackground(menuBackgroundPtr);
	menuButtonPtr=(short int *) startButtonSelected.pixel_data;
	menuButtonWidth = startButtonSelected.width;
	menuButtonHeight = startButtonSelected.height;
	drawMenuButton(menuButtonPtr, menuButtonWidth, menuButtonHeight, START_BUTTON_XPOS, START_BUTTON_YPOS);
	menuButtonPtr=(short int *) quitButtonDeselected.pixel_data;
	menuButtonWidth = quitButtonDeselected.width;
	menuButtonHeight = quitButtonDeselected.height;
	drawMenuButton(menuButtonPtr, menuButtonWidth, menuButtonHeight, QUIT_BUTTON_XPOS, QUIT_BUTTON_YPOS);
}
	



void run_menu(){
	Menu *menu;
	menu = malloc(sizeof(Menu));
	menu -> button_selected = QUIT_GAME;
	
	//printf("%d", test);
	int runningMenu = 1;
	int menuNeedsToBeShownInitially = 1;

	
	while(runningMenu){
		if(menuNeedsToBeShownInitially){
			if (menu -> button_selected == START_GAME) {
				quitSelected(menu);
				//printf("quit selected\n");
			} else {
				startSelected(menu);
			}
			menuNeedsToBeShownInitially = 0;
		}
		if (buttons_pressed_refined[JOYPAD_UP] == PRESSED && isButtonHeldDown == BUTTON_ISNT_BEING_HELD_DOWN) {
			if (menu -> button_selected == START_GAME) {
				quitSelected(menu);
				//printf("quit selected\n");
			} else {
				startSelected(menu);
			}
		} else if (buttons_pressed_refined[JOYPAD_DOWN] == PRESSED && isButtonHeldDown == BUTTON_ISNT_BEING_HELD_DOWN) {
            if (menu -> button_selected == START_GAME) {
				quitSelected(menu);
				//printf("quit selected\n");
			} else {
				startSelected(menu);
				//printf("start selected\n");
			}
		}
		if(buttons_pressed_refined[A_BUTTON] == PRESSED){
			if(menu -> button_selected == START_GAME){
				runningMenu = 0;
				//printf("game started\n");
				//free(menu);
                run_game();
                menuNeedsToBeShownInitially = 1;
                runningMenu = 1;
			//start game
			} else { //if button_selected == QUIT_GAME
				//printf("game quit\n");
				free(menu);
				system("clear");
				exit(0);
			}
		}
		
		if(buttons_pressed_refined[JOYPAD_UP] == NOT_PRESSED && buttons_pressed_refined[JOYPAD_DOWN] == NOT_PRESSED){
			isButtonHeldDown = BUTTON_ISNT_BEING_HELD_DOWN;
		}
	}
}

void pauseQuitSelected(Menu* menu){
	menu -> button_selected = QUIT_GAME;
	isButtonHeldDown = BUTTON_IS_BEING_HELD_DOWN;
	
	short int *menuBackgroundPtr=(short int *) menuBackground.pixel_data;
	drawBackground(menuBackgroundPtr);
	menuButtonPtr=(short int *) startButtonDeselected.pixel_data;
	menuButtonWidth = startButtonDeselected.width;
	menuButtonHeight = startButtonDeselected.height;
	drawMenuButton(menuButtonPtr, menuButtonWidth, menuButtonHeight, START_BUTTON_XPOS, START_BUTTON_YPOS);
	menuButtonPtr=(short int *) quitButtonSelected.pixel_data;
	menuButtonWidth = quitButtonSelected.width;
	menuButtonHeight = quitButtonSelected.height;
	drawMenuButton(menuButtonPtr, menuButtonWidth, menuButtonHeight, QUIT_BUTTON_XPOS, QUIT_BUTTON_YPOS);
}
	
void pauseStartSelected(Menu* menu){
	menu -> button_selected = START_GAME;
	isButtonHeldDown = BUTTON_IS_BEING_HELD_DOWN; 
	short int *menuBackgroundPtr=(short int *) menuBackground.pixel_data;
	drawBackground(menuBackgroundPtr);
	menuButtonPtr=(short int *) startButtonSelected.pixel_data;
	menuButtonWidth = startButtonSelected.width;
	menuButtonHeight = startButtonSelected.height;
	drawMenuButton(menuButtonPtr, menuButtonWidth, menuButtonHeight, START_BUTTON_XPOS, START_BUTTON_YPOS);
	menuButtonPtr=(short int *) quitButtonDeselected.pixel_data;
	menuButtonWidth = quitButtonDeselected.width;
	menuButtonHeight = quitButtonDeselected.height;
	drawMenuButton(menuButtonPtr, menuButtonWidth, menuButtonHeight, QUIT_BUTTON_XPOS, QUIT_BUTTON_YPOS);
}
	
void run_pause_menu(){
	Menu *menu;
	menu = malloc(sizeof(Menu));
	menu -> button_selected = QUIT_GAME;
	
	//printf("%d", test);
	int runningMenu = 1;
	int menuNeedsToBeShownInitially = 1;

	
	while(runningMenu){
		if(menuNeedsToBeShownInitially){
			if (menu -> button_selected == START_GAME) {
				pauseQuitSelected(menu);
				//printf("quit selected\n");
			} else {
				pauseStartSelected(menu);
			}
			menuNeedsToBeShownInitially = 0;
			delayMicroseconds(DELAY_BUTTON_INPUT_MICROSECS);
		}
		if (buttons_pressed_refined[JOYPAD_UP] == PRESSED && isButtonHeldDown == BUTTON_ISNT_BEING_HELD_DOWN) {
			if (menu -> button_selected == START_GAME) {
				pauseQuitSelected(menu);
				//printf("quit selected\n");
			} else {
				pauseStartSelected(menu);
			}
		} else if (buttons_pressed_refined[JOYPAD_DOWN] == PRESSED && isButtonHeldDown == BUTTON_ISNT_BEING_HELD_DOWN) {
            if (menu -> button_selected == START_GAME) {
				pauseQuitSelected(menu);
				//printf("quit selected\n");
			} else {
				pauseStartSelected(menu);
				//printf("start selected\n");
			}
		}
		if(buttons_pressed_refined[START] == PRESSED){
			runningMenu = 0;
		}
		if(buttons_pressed_refined[A_BUTTON] == PRESSED){
			if(menu -> button_selected == START_GAME){
				runningMenu = 0;
				//printf("game started\n");
				//free(menu);
                //gameRunning = 0;
                delayMicroseconds(DELAY_BUTTON_INPUT_MICROSECS);
                run_game();
                //menuNeedsToBeShownInitially = 1;
                //runningMenu = 1;
			//start game
			} else { //if button_selected == QUIT_GAME
				//printf("game quit\n");
				free(menu);
				system("clear");
				exit(0);
			}
		}
		
		if(buttons_pressed_refined[JOYPAD_UP] == NOT_PRESSED && buttons_pressed_refined[JOYPAD_DOWN] == NOT_PRESSED){
			isButtonHeldDown = BUTTON_ISNT_BEING_HELD_DOWN;
		}
	}
}



