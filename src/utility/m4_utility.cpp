#include <Arduino.h>
#include <stdint.h>
#include "globals.h"
#include "m4_utility.hpp"

bool debounce(uint32_t pin){
    bool state;
    state = digitalRead(pin);
    delay(50);
    if (state == digitalRead(pin)){
        return true;   
    }
    else{
        return false;
    }
}

bool leftButtonPushed(){
    if (digitalRead(LEFT_BUTTON) == LOW){
        if (debounce(LEFT_BUTTON)){
            return true;
        }
    }
    return false;
}

bool rightButtonPushed(){
    if (digitalRead(RIGHT_BUTTON) == LOW){
        if (debounce(RIGHT_BUTTON)){
            return true;
        }
    }
    return false;
}

bool centerButtonPushed(){
    if (digitalRead(CENTER_BUTTON) == LOW){
        if (debounce(CENTER_BUTTON)){
            return true;
        }
    }
    return false;
}