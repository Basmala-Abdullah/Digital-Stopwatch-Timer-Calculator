#include "stopWatch.h"

int key;
extern int stopmin;
int stopmin=-1; //initial state of minutes
extern int stopsec; 
int stopsec=-1; //initial state of seconds


typedef enum{
  Calc_State,
  Timer_State,
  StopWatch_State
}States_t;
extern States_t ProgramState; 


//ISR of the systick timer
void SysTick_Handler(){
  
  WTIMER0_IMR_R  = 0x00;//Disaple timer interrupts
  WTIMER0_CTL_R = 0x00;//Disaple the timer
  
  
  
  if (stopsec<59){
  
  stopsec++;
  LCD_clearDisp();
  timer2char(stopmin,stopsec);
  
  }
  
  else if (stopsec == 59)
  {
  stopmin++;
  stopsec= 0;
  LCD_clearDisp();
  timer2char(stopmin,stopsec);
  }
  NVIC_ST_RELOAD_R = 15999999; //initialize the reload register
}


//Function to initialize the systick timer and __asm("CPSIE  I");
void initStopWatch(){
  
  NVIC_ST_CTRL_R = 0x06;
  __asm("CPSIE    I");

}

//Function to call timer initialization
void stopWatchInit(){
  initStopWatch();
}


void stopWatch(void)
{
  NVIC_ST_CTRL_R |= (1<<1); //Enable systick timer interrupts
  NVIC_ST_CTRL_R |= (1<<0); //Enable systick timer
  do
  {
  if (stopmin==-1 && stopsec==-1)
   {
     //if stopmin and stopsec are -1 then initialize them to zero and display 00:00 on the LCD to start the stopwatch
      stopmin = 0;
       stopsec = 0;
      LCD_clearDisp();
      timer2char(0,0);
   }
    //Wait for the key pad input from the user
    do{
      key = Keypad_Read();
      delayMs(150);
    } while(Keypad_Read() != key);
    
    if(key>='A' &&key<='C')
      printf("\n%c",key);
  
    //if key is A then start the stopwatch
    if(key == 'A'){
      NVIC_ST_RELOAD_R = 15999999; //inialize the reload register
      NVIC_ST_CTRL_R |= 0x03; //Enable systick timer and systick timer interrupts
 
    }
    else if(key == 'B'){
      //if key is B then pause the stopwatch
      NVIC_ST_CTRL_R &= ~(1<<0); //Disaple the systick timer
      LCD_clearDisp(); 
      timer2char(stopmin,stopsec); //Display the last updated value of seconds and minutes
    }
    else if (key == 'C'){
      //if key is C then reset the stopwatch and display 00:00 on the LCD
      LCD_clearDisp();
      timer2char(0,0);
      //initialize stopmin and stopsec to -1 in order to start from the initial state
      stopsec=-1;
      stopmin=-1;
    }
  } while(DIO_ReadPin(PORTF, 0)!=0); //do this process while button switch is not pressed, otherwise switch the mode to calculator state
  
  delayMs(100);
  if (DIO_ReadPin(PORTF, 0)==0)
  {
    LCD_clearDisp();
    NVIC_ST_CTRL_R &= ~(1<<1); //Disable systick timer interrupts
    NVIC_ST_CTRL_R &= ~(1<<0); //Disbale systick timer 
    ProgramState= Calc_State; //Set state to calculator
 
  }
    
  
}

