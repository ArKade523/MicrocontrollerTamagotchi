#ifndef button_interface 
#define button_interface

#include <stdint.h>

#define BUTTON_READ 2   // Defined for calling a read in the button read functions

bool debounce(uint32_t pin);

void rightButton_ISR();
void leftButton_ISR();
void centerButton_ISR();

bool leftButtonPushed(uint8_t functionBehavior = BUTTON_READ);
bool rightButtonPushed(uint8_t functionBehavior = BUTTON_READ);
bool centerButtonPushed(uint8_t functionBehavior = BUTTON_READ);

#endif