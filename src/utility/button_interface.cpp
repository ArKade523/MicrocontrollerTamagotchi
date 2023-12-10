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

/*
Functions to call when checking if a button push occured
*/
// Check if left button pushed (default)
// Set button pushed to true (argument = true)
// Set button pushed to false (argument = false)
bool leftButtonPushed(uint8_t functionBehavior){
    volatile static bool LBP;

    if (functionBehavior == BUTTON_READ){
        if (LBP){   //Check if button was pushed, if so, clear the push and return true, otherwise return false
            LBP = false;
            return true;
        }
        else{
            return false;
        }   
    }
    else {
        LBP = functionBehavior;     // If argument is true, LBP = true, if false, LBP = false
        return LBP; 
    }
}
// Check if right button pushed (default)
// Set button pushed to true (argument = true)
// Set button pushed to false (argument = false)
bool rightButtonPushed(uint8_t functionBehavior){
    volatile static bool RBP;

    if (functionBehavior == BUTTON_READ){
        if (RBP){   //Check if button was pushed, if so, clear the push and return true, otherwise return false
            RBP = false;
            return true;
        }
        else{
            return false;
        }    
    }
    else {
        RBP = functionBehavior;     // If argument is true, RBP = true, if false, RBP = false
        return RBP; 
    }
}
// Check if center button pushed (default)
// Set button pushed to true (argument = true)
// Set button pushed to false (argument = false)
bool centerButtonPushed(uint8_t functionBehavior){
    volatile static bool CBP;

    if (functionBehavior == BUTTON_READ){
        if (CBP){   //Check if button was pushed, if so, clear the push and return true, otherwise return false
            CBP = false;
            return true;
        }
        else{
            return false;
        }
    }
    else {
        CBP = functionBehavior;     // If argument is true, CBP = true, if false, CBP = false
        return CBP; 
    }
}



void rightButton_ISR(){
    if (debounce(RIGHT_BUTTON)) rightButtonPushed(true);
}

void leftButton_ISR(){
    if (debounce(LEFT_BUTTON)) leftButtonPushed(true);
}

void centerButton_ISR(){
    if (debounce(CENTER_BUTTON)) centerButtonPushed(true);
}