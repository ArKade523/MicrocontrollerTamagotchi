#include "Tamagotchi-SH1106.hpp"
#include "Tamagotchi.hpp"
#include "../globals.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include "bitmaps_6x7.hpp"
#include "bitmaps.hpp"

Tamagotchi_SH1106::Tamagotchi_SH1106(void) : display(Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET)) {
    delay(250); // wait for the OLED to power up
    display.begin(i2c_Address, true); // Address 0x3C default

    display.display();

    delay(100);

    display.clearDisplay();   // clears the screen and buffer

    display.setTextSize(1);   // text size 1 = 6x8, 2 = 12x16, 3 = 18x24, etc
    display.setTextColor(SH110X_WHITE); // default color
    display.println("Hello, elly!");
    display.display();
}

void Tamagotchi_SH1106::drawHome() {
    display.clearDisplay();
    display.drawBitmap(2, 2, hunger_bmp, 7, 6, SH110X_WHITE);
    display.drawLine(11, 3, 31, 3, SH110X_WHITE);
    display.drawLine(11, 6, 31, 6, SH110X_WHITE);
    display.drawBitmap(34, 2, heart_bmp, 7, 6, SH110X_WHITE);
    display.drawLine(43, 3, 63, 3, SH110X_WHITE);
    display.drawLine(43, 6, 63, 6, SH110X_WHITE);
    display.drawBitmap(66, 2, training_bmp, 7, 6, SH110X_WHITE);
    display.drawLine(75, 3, 95, 3, SH110X_WHITE);
    display.drawLine(75, 6, 95, 6, SH110X_WHITE);
    display.drawBitmap(98, 2, sleeping_bmp, 7, 6, SH110X_WHITE);
    display.drawLine(107, 3, 127, 3, SH110X_WHITE);
    display.drawLine(107, 6, 127, 6, SH110X_WHITE);

    display.drawLine(0, 10, 128, 10, SH110X_WHITE);

    display.drawBitmap(50, 15, egg_uncracked_bmp, 40, 40, SH110X_WHITE);

    if (digitalRead(CENTER_BUTTON) == LOW) {
        gameState = MENU;
    }

    display.display();

}

void Tamagotchi_SH1106::drawMenu() {
    display.clearDisplay();
    display.setTextColor(SH110X_WHITE);
    display.setTextSize(1);
    display.setCursor(64 - 6.5 * 6, 0);
    display.print("Select a game");

    // Enum for different games
    enum Game {
        FEED_GAME,
        RETURN,
        PLAY_GAME,
        TRAIN_GAME,
    };

    Game selectedGame = RETURN;

    if (digitalRead(CENTER_BUTTON) == LOW) {
        switch(selectedGame) {
            case FEED_GAME:
                gameState = FEED;
                break;
            case RETURN:
                gameState = NORMAL;
                break;
            case PLAY_GAME:
                gameState = PLAY;
                break;
            case TRAIN_GAME:
                gameState = TRAIN;
                break;
        }
    }

    display.display();
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