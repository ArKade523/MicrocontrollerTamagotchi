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

    // delay(250); // wait for the OLED to power up
    // display.begin(i2c_Address, true); // Address 0x3C default

    // display.display();

    // delay(100);

    // display.clearDisplay();   // clears the screen and buffer

    // display.setTextSize(1);   // text size 1 = 6x8, 2 = 12x16, 3 = 18x24, etc
    // display.setTextColor(SH110X_WHITE); // default color
    // display.println("Hello, elly!");    
    // display.display();
    
    while(1) {
        tamagotchi.trainGameUpdate();
        // if (digitalRead(LEFT_BUTTON) == LOW) {
        //     display.clearDisplay();
        //     display.setCursor(0, 0);
        //     display.println("Left button pressed");
        //     display.display();
        // } else if (digitalRead(CENTER_BUTTON) == LOW) {
        //     display.clearDisplay();
        //     display.setCursor(0, 0);
        //     display.println("Center button pressed");
        //     display.display();
        // } else if (digitalRead(RIGHT_BUTTON) == LOW) {
        //     display.clearDisplay();
        //     display.setCursor(0, 0);
        //     display.println("Right button pressed");
        //     display.display();
        // }
        // delay(100);
        // display.display();
    }

}

void loop() {

}