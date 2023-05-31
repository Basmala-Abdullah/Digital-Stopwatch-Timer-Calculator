#include "Timer.h"
#include "DIO.h"

#define BuzzerPin     (7)
#define BuzzerPort    (PORTA)

void BuzzerOn(void);
void Buzzer_Init();
void BuzzerOff(void);
void delayMsBuzzer(int n);