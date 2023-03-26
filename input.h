#ifndef INPUT
#define INPUT

/* definitions */
int buttons_pressed[16];
int buttons_pressed_refined[16];
//int test;
//char button_names[12][14];


//struct

void initInput(unsigned int *gpio_ptr);

void init_GPIO(unsigned int *gpio_ptr, int func_code, int line_num);

void initButtonsPrevPressed(void);

void initButtonsPressed(void);

void Print_Message(char buttons_pressed[]);

void ifButtonsPressedPrint(void);

void wait(int microsecs);

void Write_Latch(unsigned int *gpio_ptr, int bit_to_write);

void Write_Clock(unsigned int *gpio_ptr, int bit_to_write);

void Write_Pin(unsigned int *gpio_ptr, int bit_to_write, int pin_num);

void Read_Data(unsigned int *gpio_ptr, int *read_dest);

void Read_SNES(unsigned int *gpio_ptr);

#endif
