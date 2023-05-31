#include "Timer.h"
#include "DIO.h"
#include "buzzer.h"
/******************************************************************/
/*                  Global Variables                             */
/******************************************************************/
int emptySpace=0; //indicates the index of last empty space in the global stack
int min=-1; 
int sec=-1;  
int ticks=0; //ticks are the total number of ISR entries
char stack[6];
extern int stopsec;
extern int stopmin;
int flag=0;


typedef enum{
  Calc_State,
  Timer_State,
  StopWatch_State
}States_t;
extern States_t ProgramState;




//Function to set the reload value of the timer
void ReloadValue(){
  WTIMER0_CTL_R = 0x00;
  WTIMER0_TAILR_R = 16000000;
  WTIMER0_IMR_R  = 0x01;           
  WTIMER0_CTL_R |= 0x03;
}


/******************************************************************/
/*                  Interrupt Handlers                            */
/******************************************************************/
//ISR of timer interrupt
void TimerHandler(){
  if( ProgramState != StopWatch_State)
  {

    
  if((min ==0)&&(sec==0)){
 //If minutes and seconds are equal to zero then buzzer is turned on for 3 sec then turned off
 //CTL register and Interrupt register is disabled, min adn sec are initialized with -1 for next user input
  BuzzerOn();
  BuzzerOff();
  WTIMER0_CTL_R = 0x00;
  WTIMER0_IMR_R  = 0x00;  
   min=-1;
   sec=-1;
  }
  //if sec>0, sec is decremented and displayed on LCD
  if (sec>0){
  ReloadValue();
  sec--;

  LCD_clearDisp();
  timer2char(min,sec);
  }
  else if (sec ==0 && min>0)
  {
    //if sec =0 then min is decremented, sec is set to 59 and then displayed on LCD
  ReloadValue();
  min--;
  sec= 59;

  LCD_clearDisp();
  timer2char(min,sec);
  
  }
  
  ticks--;
  WTIMER0_ICR_R=0x01; //To clear the interrupt flag of the timer
  }
  else 
  {
  //If state is stopWatch then dispale the CTL and IMR register of the timer
  WTIMER0_IMR_R  = 0x00;
  WTIMER0_CTL_R = 0x00;
  }                       
  
}

void Timer1Handler(){
  WTIMER1_ICR_R=0x01;
  WTIMER1_CTL_R = 0x00;
  DIO_WritePin(BuzzerPort, BuzzerPin, 0);
}

/******************************************************************/
/*                  Initialization                                */
/******************************************************************/
//Function to initialize the timer
void initTimer(){
  SYSCTL_RCGCWTIMER_R |= 0x01;
  WTIMER0_CTL_R = 0x00;
  WTIMER0_CFG_R= 0x00;
  WTIMER0_TAMR_R = 0x02;
  WTIMER0_TAPR_R = 0x00;
  WTIMER0_ICR_R=0x01;
  WTIMER0_IMR_R  = 0x01;
  NVIC_EN2_R = 1<<30;
     
}


//Function to push input from user into the global stack to be processed later
void PushTime(char key){
  
  if(key != 0){
    stack[emptySpace]=key;
    emptySpace++;
  }
}

//Function to calculate the value of seconds and minutes entered by the user 
//converts the character seconds and minutes entered by the user to integer seconds and minutes
void CalcSec(){
  emptySpace--;
  int power =0;
  
  while(stack[emptySpace] >= '0'&& stack[emptySpace] <= '9'){
    sec += ((stack[emptySpace]  - '0')*pow(10,power));
    power++;
    emptySpace--;  
    
  }
  printf("\n%d",sec);
  
  emptySpace--;
  power =0;
  
  while(emptySpace>=0 ){
   min += (stack[emptySpace]  - '0')*pow(10,power);
   power++;
   emptySpace--;
   
  }
  printf("\n%d",min);   
     
}

//Function to call timer initialization and __asm("CPSIE  I");
void TimerInit(){
  
  initTimer();
  __asm("CPSIE  I");
}


void Timer(void)
{
      unsigned char key; 
      //if min=-1 and sec=-1 this indicates the initial state so 00:00 is dispaled on LCD
      if (min==-1 && sec==-1)
      {  
        min=-2;
        sec=-2;
        emptySpace=0; //empty the stack to get ready for the user input
      WTIMER0_IMR_R  = 0x00; //disaple interrupts
      WTIMER0_CTL_R = 0x00; //disaple timer CTL register
      LCD_clearDisp(); //clear previous displayed value
      timer2char(0,0); //Display 00:00 on LCD
      }
      else if((min>=0 || sec>0))
      {
      WTIMER0_IMR_R  = 0x01; //Enable the interrupts to ISR to be called
      WTIMER0_CTL_R = 0x01; //Enable the timer
      
      }
      //Wait for the key pad input from the user
      do{
      key = Keypad_Read();
      delayMs(70);
    } while(Keypad_Read() != key);
    
    //If key is within range 0 to 9 or A where A indicates the input ':'
    if((key>='0' && key<='9')||(key=='A'))
    {
      
      if (emptySpace==0 )
        LCD_clearDisp(); //clear the LCD because it is the first user input
      if(key>='0' && key<='9')
        LCD_sendData(key); //Display the input keys
      else if( key == 'A')
        LCD_sendData(':'); //Display ':' when input is A
      PushTime(key); //Push the key value into the global stack
       printf("\n");
    }
    else if(key == 'D')
    {
      //when input is D start decrementing the timer
      //initialize min and sec to zero and calculate thier value 
        min=0;
        sec=0;
       CalcSec(); //calculating sec and min
       ticks = sec + min*60; 

       ReloadValue(); //Initialize the reload register
       while(ticks>0){
         //Check if the switch is set, then switch to the next mode
          if(DIO_ReadPin(PORTF, 0)==0) {
            delayMs(100);
           if(DIO_ReadPin(PORTF, 0)==0)
          {
            //Getting ready to switch for the next mode, which is stopwatch mode
            LCD_clearDisp();
            WTIMER0_IMR_R  = 0x00; 
            WTIMER0_CTL_R = 0x00;
           ProgramState= StopWatch_State;
           if(stopsec == 0 && stopmin == 0)
           {
             //if stopsec and stopmin = 0 then initialize them to -1 to start from the initial state
             stopsec=-1;
             stopmin=-1;
           }
           break;
          }
       }
       
    }

}


}