//Ben Foster 30094638 & Justin Yee 30113485

#include <unistd.h>
#include <stdio.h>
#include "initGPIO.h"
#include <wiringPi.h>
#include <pthread.h>

#include <stdlib.h>
#include <stdbool.h>            

//#define GPIO_BASE 0xFE200000
#define GPIO_SET_INPUT(gpio_base, pin) *(gpio_base+(((pin)/10))) &= ~(7<<(((pin)%10)*3))
#define GPIO_SET_OUTPUT(gpio_base, pin)  *(gpio_base+(((pin)/10))) |= (1<<(((pin)%10)*3))

#define CLO_REG 0x7E003004
unsigned *clo = (unsigned*)CLO_REG;

#define LAT 9 //Latch line has this pin #
#define DAT 10 //Data line has this pin #
#define CLK 11 //Clock has this pin #

#define READ 0
#define WRITE 1

#define GPSET0 7 //GPSET0 is 7 bytes after GPIO_BASE
#define GPCLR0 10 //GPCLR0 is 10 bytes after GPIO_BASE
#define GPLEV0 13 //GPLEV0 is 13 bytes after GPIO_BASE

#define NUM_OF_BUTTONS 12
#define NUM_OF_CLOCK_PULSES 16
#define START 3

#define CYCLES_BEFORE_BUTTON_CAN_BE_PRESSED_AGAIN 100 //because theres 204 micro seconds in a cycle (17 x 12microseconds, see diagram), and I want to have to wait around 5000 micro seconds so 5000/209 = 1020000

//struct input_state {
int buttons_pressed[NUM_OF_CLOCK_PULSES]; //each index stores either a 0 or a 1, 0 for if the button is pressed, 1 if it's not pressed 
int buttons_pressed_refined[NUM_OF_CLOCK_PULSES]; //each index stores either a 0 or a 1, 0 for if the button is pressed, 1 if it's not pressed. Refined so that button won,t oscilate between pressed and not pressed when holding down a button
int cycles_since_buttons_prev_pressed[NUM_OF_BUTTONS]; //So buttons that are held down don't get printed a million times
char button_names[NUM_OF_BUTTONS][14] = {"B", "Y", "Select", "Start", "Joy-pad UP", "Joy-pad DOWN", "Joy-pad LEFT", "Joy-pad RIGHT", "A", "X", "Left", "Right"}; //needs length of one more than how many characters a word looks like it has because every string needs of end of string character. Otherwise, it will print the next entry before reaching that entry's end of string character.
bool button_pressed_this_cycle = false; //So that if no button is pressed, you don't print the press_but_msg string
char press_but_msg[] = "Please press a button...\n";
extern int test = 7;

//} 
//struct input_state my_inputs;

/*
bool b_prev_pressed = false;
bool y_prev_pressed = false;
bool select_prev_pressed = false;
bool start_prev_pressed = false;
bool joy_up_prev_pressed = false;
bool joy_down_prev_pressed = false;
bool joy_left_prev_pressed = false;
bool joy_right_prev_pressed = false;
bool a_prev_pressed = false;
bool x_prev_pressed = false;
bool left_prev_pressed = false;
bool right_prev_pressed = false;
*/



void init_GPIO(unsigned int *gpio_ptr, int func_code, int line_num){
    //Initializing SNES lines
    if(func_code == READ){
        GPIO_SET_INPUT(gpio_ptr, line_num); //Clear GPIO pin to be 000 
    } else if(func_code == WRITE){
        GPIO_SET_INPUT(gpio_ptr, line_num); //Clear GPIO pin to be 000 
        GPIO_SET_OUTPUT(gpio_ptr, line_num); //Set GPIO pin to output (001)
    }
}

void initButtonsPrevPressed(){
    int i;
    for(i = 0; i < NUM_OF_BUTTONS; i++){
        cycles_since_buttons_prev_pressed[i] = CYCLES_BEFORE_BUTTON_CAN_BE_PRESSED_AGAIN;    //initialize all buttons time since they last been pressed to max to their max becuase they are ready to be pressed again
    }
}

void initButtonsPressed(){
    int i;
    for(i = 0; i < NUM_OF_CLOCK_PULSES; i++){
        buttons_pressed[i] = 1; //all buttons should be set to 1 (not pressed) otherwise it would be set to null which is what you don't want
 //#define CLO_REG 0x7E003004 r
                            
 
    }
}

void Print_Message(char button_pressed[]){
    printf("You have pressed %s \n", button_pressed); 
    printf("\n");
}

void ifButtonsPressedPrint(){
    int button_num_idx;
    for(button_num_idx = 0; button_num_idx < NUM_OF_BUTTONS; button_num_idx++){ //check if each button needs printing, print which button pressed if so
        if(buttons_pressed[button_num_idx] == 0 && (cycles_since_buttons_prev_pressed[button_num_idx] >= CYCLES_BEFORE_BUTTON_CAN_BE_PRESSED_AGAIN)){  //if button is held down, shouldn't be printed more than once. 
            Print_Message(button_names[button_num_idx]);
            button_pressed_this_cycle = true; //flag to know whether the prompt to enter a button should be printed again
            cycles_since_buttons_prev_pressed[button_num_idx] = 0; //any button that is held should not be printed twice in a row so this flag is here for that
        } else if (buttons_pressed[button_num_idx] == 1){ //if button is let go however, should be able to press button again and get another print statement
            if(cycles_since_buttons_prev_pressed[button_num_idx] < CYCLES_BEFORE_BUTTON_CAN_BE_PRESSED_AGAIN){
                cycles_since_buttons_prev_pressed[button_num_idx]++;
            }
        } else { //if button is pressed but hasn't been long enough since the last press
            cycles_since_buttons_prev_pressed[button_num_idx] = 0;
        }
        //printf("%d", buttons_pressed[button_num_idx]);
    }
    
    if(button_pressed_this_cycle){  //for printing prompt to enter a button
       printf("%s", press_but_msg);
       printf("\n");
    }
    button_pressed_this_cycle = false; //Reset button_pressed_this_cycle 

}

void setButtonInButtonsPressedRefined(){
    int button_num_idx;
    for(button_num_idx = 0; button_num_idx < NUM_OF_BUTTONS; button_num_idx++){ //check if each button needs printing, print which button pressed if so
        if(buttons_pressed[button_num_idx] == 0 && (cycles_since_buttons_prev_pressed[button_num_idx] >= CYCLES_BEFORE_BUTTON_CAN_BE_PRESSED_AGAIN)){  //if button is held down, shouldn't be printed more than once. 
            //Print_Message(button_names[button_num_idx]);
            //button_pressed_this_cycle = true; //flag to know whether the prompt to enter a button should be printed again
            cycles_since_buttons_prev_pressed[button_num_idx] = 0; //any button that is held should not be printed twice in a row so this flag is here for that
            buttons_pressed_refined[button_num_idx] = 0;
        } else if (buttons_pressed[button_num_idx] == 1){ //if button is let go however, should be able to press button again and get another print statement
            if(cycles_since_buttons_prev_pressed[button_num_idx] < CYCLES_BEFORE_BUTTON_CAN_BE_PRESSED_AGAIN){
                cycles_since_buttons_prev_pressed[button_num_idx]++;
            } else { // if button has been let go for long enough, set button to show its not pressed
                buttons_pressed_refined[button_num_idx] = 1;
            }
        } else { //if button is pressed but hasn't been long enough since the last press
            cycles_since_buttons_prev_pressed[button_num_idx] = 0;
        }
        //printf("%d", buttons_pressed[button_num_idx]);
    }
    
    //button_pressed_this_cycle = false; //Reset button_pressed_this_cycle 

}

void wait(int microsecs){
    delayMicroseconds(microsecs);
    //unsigned c = *clo + microsecs;
    //while (c > *clo);
}

void Write_Latch(unsigned int *gpio_ptr, int bit_to_write){
    switch(bit_to_write){
        case(0):
            gpio_ptr[GPCLR0] = 1 << LAT; //sets GPCLR register so that latch pin is set to 1, because we want to clear bit stored in latch pin
            break;
        case(1):
            gpio_ptr[GPSET0] = 1 << LAT; //sets GPSET register so that latch pin is set to 1, because we want to set bit stored in latch pin
            break;
    }
}


void Write_Clock(unsigned int *gpio_ptr, int bit_to_write){
    switch(bit_to_write){
        case(0):
            gpio_ptr[GPCLR0] = 1 << CLK; //sets GPCLR register so that clock pin is set to 1, because we want to clear bit stored in clock pin
            break;
        case(1):
            gpio_ptr[GPSET0] = 1 << CLK; //sets GPSET register so that clock pin is set to 1, because we want to set bit stored in clock pin
            break;
    }
}

void Write_Pin(unsigned int *gpio_ptr, int bit_to_write, int pin_num){
    switch(bit_to_write){
        case(0):
            gpio_ptr[GPCLR0] = 1 << pin_num;
            break;
        case(1):
            gpio_ptr[GPSET0] = 1 << pin_num;
            break;
    }
} 

void Read_Data(unsigned int *gpio_ptr, int *read_dest){
    int num_read = (gpio_ptr[GPLEV0] >> DAT) & 1;
    //printf("before: %d", *read_dest);
    *read_dest = num_read; //change value of read destination to whatever is read
    //printf("after: %d", *read_dest);
    //*read_dest = (gpio_ptr[GPLEV0] >> DAT) & 1;
    //printf("%d\n", *read_dest);
    //printf("%d\n", num_read);
}

void *Read_SNES(void *arg){
    unsigned int *gpio_ptr = arg;
//For loop cycle where clock osscilates up and down and inputs are read from data line, at the very end of for loop, will make a function call to ifButtonsPressedPrint
//MOV buttons, #0 // register sampling buttons //defined this array globally and it's called buttons_pressed 
    //printf("%s", press_but_msg);
    //printf("\n");
    int i;
    while(true){
//2. writeGPIO(CLOCK,#1)       
        Write_Clock(gpio_ptr, 1);
//3. writeGPIO(LATCH,#1)         
        Write_Latch(gpio_ptr, 1);
//4. wait(12s)  // signal to SNES to sample buttons        
        wait(12);
// 5. writeGPIO(LATCH,#0)
        Write_Latch(gpio_ptr, 0);
// 6. pulseLoop:  // start pulsing to read from SNES
        i = 0; 
        while(i < NUM_OF_CLOCK_PULSES){
// 1. i = 1
// 2. wait(6s)
            wait(6);
// 3. writeGPIO(CLOCK,#0) // falling edge
            Write_Clock(gpio_ptr, 0);
// 4. wait(6s)
            wait(6); //cuz updated psuedo code on d2l SNESS slides, this one is commented
// 5. readGPIO(DATA, b) // read bit i
// 6. buttons[i] = b
            Read_Data(gpio_ptr, &buttons_pressed[i]);
            //wait(6); //cuz updated psuedo code on d2l SNESS slides, this one is uncommented
// 7. writeGPIO(CLOCK,#1) // rising edge; new cycle
            Write_Clock(gpio_ptr, 1);
// 8. i++  // next button
            i++;
// 9. if (i <= 16) branch to pulseLoop 
        }
        //ifButtonsPressedPrint();
        setButtonInButtonsPressedRefined();
        /*
        int j;
        for(j = 0; j < NUM_OF_CLOCK_PULSES; j++){
            printf("%d: %d\n", j, buttons_pressed[j]);
        }
        */
        /*
        if(buttons_pressed[START] == 0){
            exit(0);
        }
        */
    }
}

/*
int main()
{
	// get gpio pointer
    unsigned int *gpioPtr = getGPIOPtr();  
	//init_GPIO(gpioPtr, WRITE, 17);
    //Write_Pin(gpioPtr, 1, 17);
    //wait(30000000);
	//printf("pointer address: %p\n", gpioPtr);
    printf("Created by: Justin Yee and Ben Foster\n");
    printf("\n");
    init_GPIO(gpioPtr, WRITE, CLK); //gets segfault if you don't run it with pi connected I think
    init_GPIO(gpioPtr, WRITE, LAT);
    init_GPIO(gpioPtr, READ, DAT);
    initButtonsPressed();
    initButtonsPrevPressed();
    Read_SNES(gpioPtr);
    

    return 0;
}
*/

void initInput(unsigned int *gpioPtr){
    init_GPIO(gpioPtr, WRITE, CLK); //gets segfault if you don't run it with pi connected I think
    init_GPIO(gpioPtr, WRITE, LAT);
    init_GPIO(gpioPtr, READ, DAT);
    initButtonsPressed();
    initButtonsPrevPressed();
    pthread_t input_thread_id;
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_create(&input_thread_id, &attr, Read_SNES, gpioPtr);
    //Read_SNES(gpioPtr);
}
