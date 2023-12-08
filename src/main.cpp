#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include "Tamagotchi/Tamagotchi-SH1106.hpp"
#include "globals.h"

/* Uncomment the initialize the I2C address , uncomment only one, If you get a totally blank screen try the other */
#define i2c_Address 0x3c //initialize with the I2C addr 0x3C Typically eBay OLED's
//#define i2c_Address 0x3d //initialize with the I2C addr 0x3D Typically Adafruit OLED's

#define OLED_RESET -1   //   QT-PY / XIAO
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Tamagotchi_SH1106 tamagotchi = Tamagotchi_SH1106(display);

void setup() {
    // set button modes
    pinMode(LEFT_BUTTON, INPUT_PULLUP);
    pinMode(CENTER_BUTTON, INPUT_PULLUP);
    pinMode(RIGHT_BUTTON, INPUT_PULLUP);

    digitalRead(LEFT_BUTTON);

    delay(250); // wait for the OLED to power up
    display.begin(i2c_Address, true); // Address 0x3C default

    display.display();

    delay(100);

    display.clearDisplay();   // clears the screen and buffer

}

void bouncingBall() {
    uint32_t ballX = 10, ballY = 10;
    int32_t ballXSpeed = 1, ballYSpeed = 1;
    uint32_t ballSize = 8;

    while(1) {
        display.clearDisplay();
        display.fillCircle(ballX, ballY, ballSize, SH110X_WHITE);
        display.display();

        ballX += ballXSpeed;
        ballY += ballYSpeed;

        if (ballX >= SCREEN_WIDTH - ballSize) {
            ballXSpeed = -1;
        }
        if (ballX <= ballSize) {
            ballXSpeed = 1;
        }
        if (ballY >= SCREEN_HEIGHT - ballSize) {
            ballYSpeed = -1;
        }
        if (ballY <= ballSize) {
            ballYSpeed = 1;
        }
        
        delay(10);
    }

}

void loop() {
    
}