/**************************************************************/
/*                Includes                                   */
/**************************************************************/
#include "Keypad.h"
#include "stopWatch.h"
#include "Timer.h"
#include "DIO.h"
#include "button.h"
#include "Calculator.h"
#include "LCD.h"
#include "buzzer.h"

typedef enum{
  Calc_State,
  Timer_State,
  StopWatch_State
}States_t;

extern States_t ProgramState;
States_t ProgramState =Calc_State;

int main()
{
  
  /**Initialize Modules**/
  LCD_init();
  Keypad_Init();
  TimerInit();
  stopWatchInit();
  calculatorInit();
  Buzzer_Init();
  DIO_init(PORTF,0 ,IN , PUR);
  DIO_init(PORTF,4 ,IN , PUR);
  
  while(1){
    
   
    switch(ProgramState){
     
    case Calc_State:
      calculator();
       //Check if the switch is set, then switch to the next mode which is Timer state
      if(DIO_ReadPin(PORTF, 0)==0) {
      delayMs(70);
      if(DIO_ReadPin(PORTF, 0)==0){
        LCD_clearDisp();
        ProgramState= Timer_State;
      }
     }
      break;

    case Timer_State:
      Timer();
       ProgramState= Timer_State;
      //Check if the switch is set, then switch to the next mode which is Stopwatch state
      if(DIO_ReadPin(PORTF, 0)==0) {
      delayMs(70);
      if(DIO_ReadPin(PORTF, 0)==0){
        LCD_clearDisp();
        ProgramState= StopWatch_State;
      }
    }
    break;
      
     case StopWatch_State:
      stopWatch();
    //Check if the switch is set, then switch to the next mode which is Calculator state
      if(DIO_ReadPin(PORTF, 0)==0) {
        delayMs(70);
        if(DIO_ReadPin(PORTF, 0)==0)
        {
        ProgramState= Calc_State;
        LCD_clearDisp();
        }
    }  
     break;
  }
  }
  return 0;
}
