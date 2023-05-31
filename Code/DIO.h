#include "bitwise_operation.h"

#define PORTA 0
#define PORTB 1
#define PORTC 2
#define PORTD 3
#define PORTE 4
#define PORTF 5

#define IN 0
#define OUT 1

#define PUR 1
#define PDR 0
#define NEITHER -1

/*
typedef enum{
  State0_White,
  State1_Red,
  State2_Green,
  State3_Blue,  
}States_t;*/

void DIO_init(int port, int pin, int dir, int pur);
void DIO_WritePin(int port, int pin, int value);
void DIO_WritePort(int port, int value);

int DIO_ReadPin(int port, int pin);
int DIO_ReadPort(int port);