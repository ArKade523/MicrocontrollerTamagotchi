#ifndef button_interface 
#define button_interface

#include <stdint.h>

bool debounce(uint32_t pin);

void rightButton_ISR();
void leftButton_ISR();
void centerButton_ISR();

extern volatile bool leftButtonPushed;
extern volatile bool rightButtonPushed;
extern volatile bool centerButtonPushed;

#endif