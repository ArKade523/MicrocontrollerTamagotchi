#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include "Tamagotchi/Tamagotchi-SH1106.hpp"
#include "utility/button_interface.hpp"
#include "globals.h"

void setup() {
    // Set buttons to not pushed initially
    leftButtonPushed(false);
    centerButtonPushed(false);
    rightButtonPushed(false);

    // set button modes
    pinMode(LEFT_BUTTON, INPUT_PULLUP);
    pinMode(CENTER_BUTTON, INPUT_PULLUP);
    pinMode(RIGHT_BUTTON, INPUT_PULLUP);

    // Create interrupts for buttons
    attachInterrupt(LEFT_BUTTON, leftButton_ISR, FALLING);
    attachInterrupt(RIGHT_BUTTON, rightButton_ISR, FALLING);
    attachInterrupt(CENTER_BUTTON, centerButton_ISR, FALLING);

    Tamagotchi_SH1106 tamagotchi = Tamagotchi_SH1106();
    
    while(1) {
        tamagotchi.update();
    }

}

void loop() {

}