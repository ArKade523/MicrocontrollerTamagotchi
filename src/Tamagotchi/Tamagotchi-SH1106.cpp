#include "Tamagotchi-SH1106.hpp"
#include "Tamagotchi.hpp"
#include "../globals.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

void Tamagotchi_SH1106::noGameUpdate() {

}

void Tamagotchi_SH1106::playGameUpdate() {

}

void Tamagotchi_SH1106::feedGameUpdate() {

}

void Tamagotchi_SH1106::trainGameUpdate() {
    // Paddle properties
    static const uint8_t paddleWidth = 5;
    static const uint8_t paddleHeight = 1;
    static const uint8_t paddleBitmap[5] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; // 5x1 bitmap
    static int paddleX = 60;
    static int paddleY = 50;

    // Ball properties
    static int ballX = 64, ballY = 32;
    static int ballSpeedX = 1, ballSpeedY = 1;
    static int ballSize = 2;

    // Handle paddle movement
    if (digitalRead(LEFT_BUTTON) == LOW) {
        paddleX -= 2;
    } else if (digitalRead(RIGHT_BUTTON) == LOW) {
        paddleX += 2;
    }

    // ball movement
    ballX += ballSpeedX;
    ballY += ballSpeedY;

    // Collision with walls
    if (ballX <= 0 || ballX >= display.width() - ballSize) ballSpeedX = -ballSpeedX;
    if (ballY <= 0) ballSpeedY = -ballSpeedY;

    // Collision with paddle
    if (ballY >= paddleY - ballSize && ballX >= paddleX && ballX <= paddleX + paddleWidth) {
        ballSpeedY = -ballSpeedY;
    }

    // Redraw
    display.clearDisplay();
    display.drawBitmap(paddleX, paddleY, paddleBitmap, paddleWidth, paddleHeight, SH110X_WHITE);
    display.fillCircle(ballX, ballY, ballSize, SH110X_WHITE);
    display.display();
    
    delay(10);
}