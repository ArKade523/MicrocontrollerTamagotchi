#include <Arduino.h>
#include <stdint.h>
#include "m4_utility.hpp"

bool debounce(uint32_t pin){
    if (digitalRead(pin) == HIGH){
        return false;
    }
    
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