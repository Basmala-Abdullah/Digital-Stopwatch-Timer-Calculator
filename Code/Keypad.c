#include "tm4c123gh6pm.h"
#include "DIO.h"
#include "Keypad.h"

void delayMs(int n){
  int i;
  for(; n>0 ; n--)
    for(i=0 ;i<3195 ; i++);
}

void Keypad_Init(){
  //Rows
  DIO_init(PORTE, 0, OUT, NEITHER);
  DIO_init(PORTE, 1, OUT, NEITHER);
  DIO_init(PORTE, 2, OUT, NEITHER);
  DIO_init(PORTE, 3, OUT, NEITHER);
  GPIO_PORTE_ODR_R = 0xf;
  
  //Columns
  DIO_init(PORTC, 4, IN, PUR);
  DIO_init(PORTC, 5, IN, PUR);
  DIO_init(PORTC, 6, IN, PUR);
  DIO_init(PORTC, 7, IN, PUR);
}

unsigned char Keypad_Read(){
  const unsigned char keymap[4][4] = {
    { '1', '2', '3', 'A'},
    { '4', '5', '6', 'B'},
    { '7', '8', '9', 'C'},
    { '*', '0', '#', 'D'}
  };
  int row, col;
  
  DIO_WritePort(PORTE, 0x0);
  if((DIO_ReadPort(PORTC) & 0xf0) == 0xf0)
    return 0;
  
  while(1){
    row = 0;
    DIO_WritePort(PORTE, 0x0e);
    delayMs(20);
    col = DIO_ReadPort(PORTC) & 0xf0;
    if(col != 0xf0)
      break;
    
    row = 1;
    DIO_WritePort(PORTE, 0x0d);
    delayMs(20);
    col = DIO_ReadPort(PORTC) & 0xf0;
    if(col != 0xf0)
      break;
    
    row = 2;
    DIO_WritePort(PORTE, 0x0b);
    delayMs(20);
    col = DIO_ReadPort(PORTC) & 0xf0;
    if(col != 0xf0)
      break;
    
    row = 3;
    DIO_WritePort(PORTE, 0x07);
    delayMs(20);
    col = DIO_ReadPort(PORTC) & 0xf0;
    if(col != 0xf0)
      break;
    
    return 0;
  }
  
  if(col == 0xe0)
    return keymap[row][0];
  if(col == 0xd0)
    return keymap[row][1];
  if(col == 0xb0)
    return keymap[row][2];
  if(col == 0x70)
    return keymap[row][3];
  return 0;
}