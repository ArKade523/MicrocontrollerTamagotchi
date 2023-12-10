#ifndef M4_Utility 
#define M4_Utility

#include <stdint.h>

bool debounce(uint32_t pin);

void rightButton_ISR();
void leftButton_ISR();
void centerButton_ISR();

extern volatile bool leftButtonPushed;
extern volatile bool rightButtonPushed;
extern volatile bool centerButtonPushed;

#endif