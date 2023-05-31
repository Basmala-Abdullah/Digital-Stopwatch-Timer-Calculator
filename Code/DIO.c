#include "DIO.h"
#include "bitwise_operation.h"

void DIO_init(int port, int pin, int dir, int pur){
  Set_Bit(SYSCTL_RCGCGPIO_R, port);
  while(Get_Bit(SYSCTL_PRGPIO_R, port) == 0){};
  
  switch(port){
    case PORTA:
      GPIO_PORTA_LOCK_R = 0x4c4f434b;
      Set_Bit(GPIO_PORTA_CR_R, pin);
      if(dir){
        Set_Bit(GPIO_PORTA_DIR_R, pin);
      }
      else {
        Clear_Bit(GPIO_PORTA_DIR_R, pin);
        if(pur == PUR){
          Set_Bit(GPIO_PORTA_PUR_R, pin);
        }
        else if(pur == PDR){
          Set_Bit(GPIO_PORTA_PDR_R, pin);
        }
      }
      Set_Bit(GPIO_PORTA_DEN_R, pin);
      break;
      
    case PORTB:
      GPIO_PORTB_LOCK_R = 0x4c4f434b;
      Set_Bit(GPIO_PORTB_CR_R, pin);
      if(dir){
        Set_Bit(GPIO_PORTB_DIR_R, pin);
      }
      else {
        Clear_Bit(GPIO_PORTB_DIR_R, pin);
        if(pur == PUR){
          Set_Bit(GPIO_PORTB_PUR_R, pin);
        }
        else if(pur == PDR){
          Set_Bit(GPIO_PORTB_PDR_R, pin);
        }
      }
      Set_Bit(GPIO_PORTB_DEN_R, pin);
      break;
      
    case PORTC:
      GPIO_PORTC_LOCK_R = 0x4c4f434b;
      Set_Bit(GPIO_PORTC_CR_R, pin);
      if(dir){
        Set_Bit(GPIO_PORTC_DIR_R, pin);
      }
      else {
        Clear_Bit(GPIO_PORTC_DIR_R, pin);
        if(pur == PUR){
          Set_Bit(GPIO_PORTC_PUR_R, pin);
        }
        else if(pur == PDR){
          Set_Bit(GPIO_PORTC_PDR_R, pin);
        }
      }
      Set_Bit(GPIO_PORTC_DEN_R, pin);
      break;
      
    case PORTD:
      GPIO_PORTD_LOCK_R = 0x4c4f434b;
      Set_Bit(GPIO_PORTD_CR_R, pin);
      if(dir){
        Set_Bit(GPIO_PORTD_DIR_R, pin);
      }
      else {
        Clear_Bit(GPIO_PORTD_DIR_R, pin);
        if(pur == PUR){
          Set_Bit(GPIO_PORTD_PUR_R, pin);
        }
        else if(pur == PDR){
          Set_Bit(GPIO_PORTD_PDR_R, pin);
        }
      }
      Set_Bit(GPIO_PORTD_DEN_R, pin);
      break;
      
    case PORTE:
      GPIO_PORTE_LOCK_R = 0x4c4f434b;
      Set_Bit(GPIO_PORTE_CR_R, pin);
      if(dir){
        Set_Bit(GPIO_PORTE_DIR_R, pin);
      }
      else {
        Clear_Bit(GPIO_PORTE_DIR_R, pin);
        if(pur == PUR){
          Set_Bit(GPIO_PORTE_PUR_R, pin);
        }
        else if(pur == PDR){
          Set_Bit(GPIO_PORTE_PDR_R, pin);
        }
      }
      Set_Bit(GPIO_PORTE_DEN_R, pin);
      break;
      
    case PORTF:
      GPIO_PORTF_LOCK_R = 0x4c4f434b;
      Set_Bit(GPIO_PORTF_CR_R, pin);
      if(dir){
        Set_Bit(GPIO_PORTF_DIR_R, pin);
      }
      else {
        Clear_Bit(GPIO_PORTF_DIR_R, pin);
        if(pur == PUR){
          Set_Bit(GPIO_PORTF_PUR_R, pin);
        }
        else if(pur == PDR){
          Set_Bit(GPIO_PORTF_PDR_R, pin);
        }
      }
      Set_Bit(GPIO_PORTF_DEN_R, pin);
      break;
      
     default:
       break;
  }
}

void DIO_WritePin(int port, int pin, int value){
  switch(port){
    case PORTA:
      if(value){
        Set_Bit(GPIO_PORTA_DATA_R, pin);
      }
      else{
        Clear_Bit(GPIO_PORTA_DATA_R, pin);
      }
      break;
      
    case PORTB:
      if(value){
        Set_Bit(GPIO_PORTB_DATA_R, pin);
      }
      else{
        Clear_Bit(GPIO_PORTB_DATA_R, pin);
      }
      break;
      
    case PORTC:
      if(value){
        Set_Bit(GPIO_PORTC_DATA_R, pin);
      }
      else{
        Clear_Bit(GPIO_PORTC_DATA_R, pin);
      }
      break;
      
    case PORTD:
      if(value){
        Set_Bit(GPIO_PORTD_DATA_R, pin);
      }
      else{
        Clear_Bit(GPIO_PORTD_DATA_R, pin);
      }
      break;
      
    case PORTE:
      if(value){
        Set_Bit(GPIO_PORTE_DATA_R, pin);
      }
      else{
        Clear_Bit(GPIO_PORTE_DATA_R, pin);
      }
      break;
      
    case PORTF:
      if(value){
        Set_Bit(GPIO_PORTF_DATA_R, pin);
      }
      else{
        Clear_Bit(GPIO_PORTF_DATA_R, pin);
      }
      break;
     
    default:
      break;
  }
}

void DIO_WritePort(int port, int value){
  switch(port){
    case PORTA:
      GPIO_PORTA_DATA_R = value;
      
    case PORTB:
      GPIO_PORTB_DATA_R = value;
      break;
      
    case PORTC:
      GPIO_PORTC_DATA_R = value;
      break;
      
    case PORTD:
      GPIO_PORTD_DATA_R = value;
      break;
      
    case PORTE:
      GPIO_PORTE_DATA_R = value;
      break;
      
    case PORTF:
      GPIO_PORTF_DATA_R = value;
      break;
     
    default:
      break;
  }
}

int DIO_ReadPin(int port, int pin){
  switch(port){
    case PORTA:
      return Get_Bit(GPIO_PORTA_DATA_R, pin);
      
    case PORTB:
      return Get_Bit(GPIO_PORTB_DATA_R, pin);
      break;
      
    case PORTC:
      return Get_Bit(GPIO_PORTC_DATA_R, pin);
      break;
      
    case PORTD:
      return Get_Bit(GPIO_PORTD_DATA_R, pin);
      break;
      
    case PORTE:
      return Get_Bit(GPIO_PORTE_DATA_R, pin);
      break;
      
    case PORTF:
      return Get_Bit(GPIO_PORTF_DATA_R, pin);
      break;
     
    default:
      break;
  }
  return -1;
}

int DIO_ReadPort(int port){
  switch(port){
    case PORTA:
      return GPIO_PORTA_DATA_R;
      
    case PORTB:
      return GPIO_PORTB_DATA_R;
      break;
      
    case PORTC:
      return GPIO_PORTC_DATA_R;
      break;
      
    case PORTD:
      return GPIO_PORTD_DATA_R;
      break;
      
    case PORTE:
      return GPIO_PORTE_DATA_R;
      break;
      
    case PORTF:
      return GPIO_PORTF_DATA_R;
      break;
     
    default:
      break;
  }
  return -1;
}




