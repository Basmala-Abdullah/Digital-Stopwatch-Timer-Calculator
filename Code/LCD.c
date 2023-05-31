#include "LCD.h"
#include <stdio.h>



// Function to make an n-milliseconds delay
void del(int n){
  for(int i=0 ; i<n ; i++)
    for(int j=0 ; j<3195 ; j++);
}



// Function to send a command to the LCD
void LCD_sendCMD(unsigned char cmd){
  // Set Write Operation command
  DIO_WritePin(LCD_CONTROL_PORT, LCD_RW, 0);
  // Set Register Selection to Insruction code
  DIO_WritePin(LCD_CONTROL_PORT, LCD_RS, 0);
  
  // Send the first 4 bits of the command
  DIO_WritePin(LCD_DATA_PORT, LCD_D7, Get_Bit(cmd, 7));
  DIO_WritePin(LCD_DATA_PORT, LCD_D6, Get_Bit(cmd, 6));
  DIO_WritePin(LCD_DATA_PORT, LCD_D5, Get_Bit(cmd, 5));
  DIO_WritePin(LCD_DATA_PORT, LCD_D4, Get_Bit(cmd, 4));
  
  // Make a falling edge for the Enable pin
  DIO_WritePin(LCD_CONTROL_PORT, LCD_EN, 0);
  del(50);
  DIO_WritePin(LCD_CONTROL_PORT, LCD_EN, 1);
  
  // Send the second 4 bits of the command
  DIO_WritePin(LCD_DATA_PORT, LCD_D7, Get_Bit(cmd, 3));
  DIO_WritePin(LCD_DATA_PORT, LCD_D6, Get_Bit(cmd, 2));
  DIO_WritePin(LCD_DATA_PORT, LCD_D5, Get_Bit(cmd, 1));
  DIO_WritePin(LCD_DATA_PORT, LCD_D4, Get_Bit(cmd, 0));
  
  // Make a falling edge for the Enable pin
  DIO_WritePin(LCD_CONTROL_PORT, LCD_EN, 0);
  del(50);
  DIO_WritePin(LCD_CONTROL_PORT, LCD_EN, 1);
}



// Function to send data to the LCD
void LCD_sendData(unsigned char data){
  // Set Write Operation command
  DIO_WritePin(LCD_CONTROL_PORT, LCD_RW, 0);
  // Set Register Selection to Display Data
  DIO_WritePin(LCD_CONTROL_PORT, LCD_RS, 1);
  
  // Send the first 4 bits of the data
  DIO_WritePin(LCD_DATA_PORT, LCD_D7, Get_Bit(data, 7));
  DIO_WritePin(LCD_DATA_PORT, LCD_D6, Get_Bit(data, 6));
  DIO_WritePin(LCD_DATA_PORT, LCD_D5, Get_Bit(data, 5));
  DIO_WritePin(LCD_DATA_PORT, LCD_D4, Get_Bit(data, 4));
  
  // Make a falling edge for the Enable pin
  DIO_WritePin(LCD_CONTROL_PORT, LCD_EN, 0);
  del(25);
  DIO_WritePin(LCD_CONTROL_PORT, LCD_EN, 1);
  
  // Send the second 4 bits of the data
  DIO_WritePin(LCD_DATA_PORT, LCD_D7, Get_Bit(data, 3));
  DIO_WritePin(LCD_DATA_PORT, LCD_D6, Get_Bit(data, 2));
  DIO_WritePin(LCD_DATA_PORT, LCD_D5, Get_Bit(data, 1));
  DIO_WritePin(LCD_DATA_PORT, LCD_D4, Get_Bit(data, 0));
  
  // Make a falling edge for the Enable pin
  DIO_WritePin(LCD_CONTROL_PORT, LCD_EN, 0);
  del(25);
  DIO_WritePin(LCD_CONTROL_PORT, LCD_EN, 1);
}



// Function to clear the LCD display
void LCD_clearDisp(){
  LCD_sendCMD(0x01);
  del(2);
}



// Function to initialize the LCD
void LCD_init(){
  // Initialize the data port pins
  DIO_init(LCD_DATA_PORT, LCD_D4, OUT, NEITHER);
  DIO_init(LCD_DATA_PORT, LCD_D5, OUT, NEITHER);
  DIO_init(LCD_DATA_PORT, LCD_D6, OUT, NEITHER);
  DIO_init(LCD_DATA_PORT, LCD_D7, OUT, NEITHER);
  
  // Initialize the control port pins
  del(50);
  DIO_init(LCD_CONTROL_PORT, LCD_RS, OUT, NEITHER);
  DIO_init(LCD_CONTROL_PORT, LCD_RW, OUT, NEITHER);
  DIO_init(LCD_CONTROL_PORT, LCD_EN, OUT, NEITHER);
  
  // Set the enable to high
  DIO_WritePin(LCD_CONTROL_PORT, LCD_EN, 1);
   
  /* function set */
  // Set LCD to 4-bit mode, and 2-line display
  DIO_WritePin(LCD_CONTROL_PORT, LCD_RW, 0);
  DIO_WritePin(LCD_CONTROL_PORT, LCD_RS, 0);
  
  DIO_WritePin(LCD_DATA_PORT, LCD_D7, 0);
  DIO_WritePin(LCD_DATA_PORT, LCD_D6, 0);
  DIO_WritePin(LCD_DATA_PORT, LCD_D5, 1);
  DIO_WritePin(LCD_DATA_PORT, LCD_D4, 0);
  
  DIO_WritePin(LCD_CONTROL_PORT, LCD_EN, 0);
  del(50);
  DIO_WritePin(LCD_CONTROL_PORT, LCD_EN, 1);
  
  LCD_sendCMD(0x2c);
  del(1);
  
  /* display on/off */
  // Set the display, the cursor, and the blinking of the cursor to ON
  LCD_sendCMD(0x0f);
  del(1);
  
  /* clear display */
  LCD_clearDisp();
  
  /* entry mode set */
  // Set the Increment Mode to ON and set shift operation to OFF
  LCD_sendCMD(0x06);
  del(1);
}



// Function to display the integer part of a number on the LCD
void int2char(int number){
  char arr[20];
  sprintf(arr, "%d", number);
  unsigned char i = 0;
  while(arr[i] != '\0'){
    LCD_sendData(arr[i]);
//    printf("%c", arr[i]);
    i++;
  }
}



// Function to display the fraction part of a number on the LCD
void decimal2char(double number){
  char arr[3] = {0};
  for(int i=0 ; i<3 ; i++){
      number *= ((double)10);
      arr[i] = (char)((int)number+'0');
      number -= ((double)((int)number));
    }
  for(int i=0 ; i<3 ; i++){
    LCD_sendData(arr[i]);
    //printf("%c", arr[i]);
  }
}



// Function to display a double number on the LCD
void double2char(double number){
  int intNum = (int)number;
  double decNum = number - (double)intNum;
  int2char(intNum);
  LCD_sendData('.');
  //printf(".");
  decimal2char(decNum);
}



// Function to display time on the LCD
void timer2char(int min, int sec){
  if(min < 10)
    LCD_sendData('0');
  int2char(min);
  LCD_sendData(':');
  if(sec < 10)
    LCD_sendData('0');
  int2char(sec);
}



// Function to display the word "ERROR!!" on the LCD
void displayError(){
  LCD_clearDisp();
  LCD_sendData('E');
  LCD_sendData('R');
  LCD_sendData('R');
  LCD_sendData('O');
  LCD_sendData('R');
  LCD_sendData('!');
  LCD_sendData('!');
}





