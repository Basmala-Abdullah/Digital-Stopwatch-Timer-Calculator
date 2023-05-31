#include "tm4c123gh6pm.h"
#include "DIO.h"

#define LCD_CONTROL_PORT        PORTA
#define LCD_DATA_PORT           PORTB

#define LCD_RS          2
#define LCD_RW          3
#define LCD_EN          4
 
#define LCD_D0          0
#define LCD_D1          1
#define LCD_D2          2
#define LCD_D3          3
#define LCD_D4          0
#define LCD_D5          1
#define LCD_D6          2
#define LCD_D7          3

void del(int n);

void LCD_init();

void LCD_sendCMD(unsigned char cmd);

void LCD_sendData(unsigned char data);

void LCD_clearDisp();

void int2char(int number);

void decimal2char(double number);

void double2char(double number);

void timer2char(int min, int sec);

void displayError();