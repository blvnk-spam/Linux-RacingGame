//Just got the grass tile to move from cell to cell only in left to right, menu buttons can be selected but havent been drawn out yet

#include "initGPIO.h"
#include "input.h"
#include <stdio.h>
#include "menu.h"


int main()
{
	// get gpio pointer
    unsigned int *gpioPtr = getGPIOPtr();  
	//init_GPIO(gpioPtr, WRITE, 17);
    //Write_Pin(gpioPtr, 1, 17);
    //wait(30000000);
	//printf("pointer address: %p\n", gpioPtr);
    //printf("Created by: Justin Yee and Ben Foster\n");
    //printf("\n");
    initInput(gpioPtr);
    //printf("%c", button_names[0][0]);
    //init_my_menu_struct();
    run_menu();
    while(1);
    
    

    return 0;
}
