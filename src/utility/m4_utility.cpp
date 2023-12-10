#include <Arduino.h>
#include <stdint.h>
#include "globals.h"
#include "m4_utility.hpp"

bool debounce(uint32_t pin){
    bool state;
    state = digitalRead(pin);
    delay(30);
    if (state == digitalRead(pin)){
        return true;   
    }
    else{
        return false;
    }
}

bool leftButtonPushed(){
    if (digitalRead(LEFT_BUTTON) == LOW){
        return debounce(LEFT_BUTTON);
    }
}

bool rightButtonPushed(){
    if (digitalRead(RIGHT_BUTTON) == LOW){
        return debounce(RIGHT_BUTTON);
    }
}


bool centerButtonPushed(){
    if (digitalRead(CENTER_BUTTON) == LOW){
        return debounce(CENTER_BUTTON);
    }
}