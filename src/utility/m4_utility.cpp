#include <Arduino.h>
#include <stdint.h>
#include "m4_utility.hpp"

bool debounce(uint32_t pin){
    bool state;
    state = digitalRead(pin);
    delay(30);
    if (state == digitalRead(pin) && state == LOW){
        return true;   
    }
    else{
        return false;
    }
}