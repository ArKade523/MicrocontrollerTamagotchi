#include <Arduino.h>
#include <stdint.h>
#include "globals.h"
#include "button_interface.hpp"

bool debounce(uint32_t pin){
    bool state;
    state = digitalRead(pin);
    delay(100);
    if (state == digitalRead(pin)){
        return true;   
    }
    else{
        return false;
    }
}

void rightButton_ISR(){
    if (debounce(RIGHT_BUTTON)) rightButtonPushed = true;
}

void leftButton_ISR(){
    if (debounce(LEFT_BUTTON)) leftButtonPushed = true;
}

void centerButton_ISR(){
    if (debounce(CENTER_BUTTON)) centerButtonPushed = true;
}