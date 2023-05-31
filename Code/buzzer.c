#include "buzzer.h"
#include "Timer.h"

void delayMsBuzzer(int n){
  int i;
  for(; n>0 ; n--)
    for(i=0 ; i<3195 ; i++);
}
//Function to initialize the buzzer
void Buzzer_Init(){
   DIO_init(BuzzerPort, BuzzerPin, 1, NEITHER);
}
//Function to turn on the buzzer
void BuzzerOn(void){
  
  DIO_WritePin(BuzzerPort, BuzzerPin, 1);
  //Start Timer
  delayMsBuzzer(2000);
  
}
//Function to turn off the buzzer
void BuzzerOff(void){
  DIO_WritePin(BuzzerPort, BuzzerPin, 0);
}