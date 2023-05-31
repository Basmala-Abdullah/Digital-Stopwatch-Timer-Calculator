#include "Calculator.h"


/******************************************************************/
/*                  Global Variables                             */
/******************************************************************/
int calcSpace=0; //to indicate the last empty space in the stack
char Calcstack[12]; //global stack to store user input in order to be processed later
unsigned char Calc_key;
typedef enum{
  Calc_State,
  Timer_State,
  StopWatch_State
}States_t;

extern States_t ProgramState;
//Function to push the user input into the global stack
void Push(char key){
    
  if(key != 0){

    Calcstack[calcSpace]=key;
    calcSpace++;
  }
}


//Function to calulate the final answer from user input 
double Calc(){
  //initializing variables
  calcSpace--; //making calcSpace indicate the last non-empty place in stack
  int power =0;
  int par2=0;
  int par1=0;
  char op;
  //while input is within the range from 0 to 9, calculate second parameter
  while(Calcstack[calcSpace] >= '0'&& Calcstack[calcSpace] <= '9'){
   
    par2 += (Calcstack[calcSpace]  - '0')*pow(10,power);
    power++;
    calcSpace--;  //pop the stack
    
  }
  //saving the operator in a variable then pop the stack
  op=Calcstack[calcSpace];
  calcSpace--;
  power =0;
  //calculate first parameter 
  while(calcSpace>=0)
  {

   par1 += (Calcstack[calcSpace]  - '0')*pow(10,power);
   power++;
   calcSpace--;
   
  }
  //If operator is A then make addition
  if(op == 'A'){
  
    return par1+par2;
    
  }  
  else if(op == 'B')
    //If operator is B then make subtraction
    return par1-par2; 
  
  else if(op == 'C'){
    //If operator is C then make division
    if(par2 == 0)
      return 1e20; //handling diviosn by zero case, displays ERROR!!
    return ((double)par1/(double)par2); 
    }
  
  else if (op == '*') 
    //If operator is *then make multiplication
    return par1*par2;     
}

//Function to make initialization of calculator
void calculatorInit(){
  
  Keypad_Init();
  
}

void calculator(void)
{
    
    double result; //variable to store the final result
    //wait for user input
    do{
      Calc_key = Keypad_Read();
      delayMs(70);
    } while(Keypad_Read() != Calc_key);
    
    //while input is within the specified range value then push it into the stack and siplay it on LCD
    if((Calc_key>='0' && Calc_key<='9')||(Calc_key>='A' && Calc_key<='C')|| Calc_key=='*')
    {
      if(Calc_key>='0' && Calc_key<='9')
      {LCD_sendData(Calc_key);}
      else if(Calc_key =='A')
        LCD_sendData('+');
      else if(Calc_key =='B')
        LCD_sendData('-');
      else if(Calc_key =='C')
        LCD_sendData('/');
      else if(Calc_key =='*')
        LCD_sendData('*');
      
      Push(Calc_key);
      printf("\n");
    }
    else if(Calc_key == 'D')
    {
      //when input is D then start calculating the result
       LCD_sendData('=');
       result = Calc();
        
       if(result == 1e20)
         displayError();//Due to division by zero
       else{
         double2char(result); //Display result on LCD
       }
         calcSpace=0;

       }
   
      //Check if state of the 2nd button switch , if pressed then clear the display for another input data 
      else if(DIO_ReadPin(PORTF, 4)==0) {
      delayMs(70);
      if(DIO_ReadPin(PORTF, 4)==0){
          LCD_clearDisp();
        }
      }
}
