#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include "Tamagotchi/Tamagotchi-SH1106.hpp"
#include "globals.h"


void setup() {
    Tamagotchi_SH1106 tamagotchi = Tamagotchi_SH1106();

    // set button modes
    pinMode(LEFT_BUTTON, INPUT_PULLUP);
    pinMode(CENTER_BUTTON, INPUT_PULLUP);
    pinMode(RIGHT_BUTTON, INPUT_PULLUP);

    while(1) {
        tamagotchi.update();

    }

}

void loop() {

}