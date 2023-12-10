#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include "Tamagotchi/Tamagotchi-SH1106.hpp"
#include "utility/m4_utility.hpp"
#include "globals.h"

// Set global interrupt variables to default state
volatile bool leftButtonPushed = false;
volatile bool centerButtonPushed = false;
volatile bool rightButtonPushed = false;

void setup() {

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