
#include "button.h" 

void ButtonInit()
{
  DIO_init(PORTF,0 ,IN , PUR);
}

int ButtonCheck()
{
  if(DIO_ReadPin(PORTF, 0)==0) {
      delayMs(100);
      if(DIO_ReadPin(PORTF, 0)==0){
        return 1;
      }
  }
  return 0;
}