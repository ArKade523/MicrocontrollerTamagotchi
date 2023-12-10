#include "Tamagotchi-SH1106.hpp"
#include "Tamagotchi.hpp"
#include "../globals.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include "bitmaps_6x7.hpp"
#include "../utility/m4_utility.hpp"
#include "bitmaps.hpp"

Tamagotchi_SH1106::Tamagotchi_SH1106(void) : display(Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET)) {
    delay(250); // wait for the OLED to power up
    display.begin(i2c_Address, true); // Address 0x3C default
    display.clearDisplay();
}

void Tamagotchi_SH1106::drawHome() {
    display.clearDisplay();

    // Hunger stat
    display.drawBitmap(2, 2, hunger_bmp, 7, 6, SH110X_WHITE);
    display.drawLine(11, 3, 31, 3, SH110X_WHITE);
    display.drawLine(11, 6, 31, 6, SH110X_WHITE);
    display.drawRect(11, 4, hunger / 5, 2, SH110X_WHITE);

    // Happiness stat
    display.drawBitmap(34, 2, heart_bmp, 7, 6, SH110X_WHITE);
    display.drawLine(43, 3, 63, 3, SH110X_WHITE);
    display.drawLine(43, 6, 63, 6, SH110X_WHITE);
    display.drawRect(43, 4, happiness / 5, 2, SH110X_WHITE);

    // Training stat
    display.drawBitmap(66, 2, training_bmp, 7, 6, SH110X_WHITE);
    display.drawLine(75, 3, 95, 3, SH110X_WHITE);
    display.drawLine(75, 6, 95, 6, SH110X_WHITE);
    display.drawRect(75, 4, training / 5, 2, SH110X_WHITE);

    // Sleepiness stat
    display.drawBitmap(98, 2, sleeping_bmp, 7, 6, SH110X_WHITE);
    display.drawLine(107, 3, 127, 3, SH110X_WHITE);
    display.drawLine(107, 6, 127, 6, SH110X_WHITE);
    display.drawRect(107, 4, sleepiness / 5, 2, SH110X_WHITE);

    display.drawLine(0, 10, 128, 10, SH110X_WHITE);

    display.drawBitmap(64 - 20, 18, egg_uncracked_bmp, 40, 40, SH110X_WHITE);

    if (centerButtonPushed()) {
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

    static GameState selectedGame = HOME;

    delay(50);

    if (centerButtonPushed()) {
        gameState = selectedGame;
    }

    if (leftButtonPushed()) {
        selectedGame = static_cast<GameState>((static_cast<int>(selectedGame) - 1) % (static_cast<int>(GameState::NUM_STATES) - 1));
    } else if (rightButtonPushed()) {
        selectedGame = static_cast<GameState>((static_cast<int>(selectedGame) + 1) % (static_cast<int>(GameState::NUM_STATES) - 1));
    }

    switch(selectedGame) {
        case HOME:
            display.setTextSize(2);
            display.setCursor(64 - 2 * 12, 32 - 8);
            display.print("Home");
            break;
        case PLAY:
            display.setTextSize(2);
            display.setCursor(64 - 2 * 12, 32 - 8);
            display.print("Play");
            break;
        case TRAIN:
            display.setTextSize(2);
            display.setCursor(64 - 2.5 * 12, 32 - 8);
            display.print("Train");
            break;
        case FEED:
            display.setTextSize(2);
            display.setCursor(64 - 2 * 12, 32 - 8);
            display.print("Feed");
            break;

        default:
            display.setTextSize(2);
            display.setCursor(64 - 1 * 12, 32 - 8);
            display.print("??");
            break;
    }

    display.display();
}

void Tamagotchi_SH1106::playGameUpdate() {
    gameState = HOME;
}

void Tamagotchi_SH1106::feedGameUpdate() {
    gameState = HOME;
}

void Tamagotchi_SH1106::trainGameUpdate() {
    // Paddle properties
    static const uint8_t paddleWidth = 15;
    static const uint8_t paddleHeight = 2;
    static const int paddleY = 63;
    static int paddleX = 60;
    static int lives = 3;
    static uint8_t bricks[6][3] = {
        1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1
    };

    if (lives <= 0) {
        lives = 3;
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 3; j++) {
                bricks[i][j] = 1;
            }
        }
    }

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
    if (ballX <= ballSize || ballX >= display.width() - ballSize) ballSpeedX = -ballSpeedX;
    if (ballY <= ballSize) ballSpeedY = -ballSpeedY;

    // Collision with paddle
    if (ballY >= paddleY - ballSize && ballX >= paddleX && ballX <= paddleX + paddleWidth) {
        ballSpeedY = -ballSpeedY;
    }

    // Collision with bottom
    if (ballY >= display.height() - ballSize) {
        ballX = 64;
        ballY = 32;
        ballSpeedX = 1;
        ballSpeedY = 1;
        lives--;
    }

    // collision with bricks
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 3; j++) {
            // if the brick is active
            if (bricks[i][j] == 1) {
                // if the ball is within the bounds of the brick
                if (ballX >= 2 + i * 20 && ballX <= 2 + i * 20 + 16 && ballY >= 10 + j * 8 && ballY <= 10 + j * 8 + 6) {
                    // deactivate the brick
                    bricks[i][j] = 0;
                    // bounce the ball
                    ballSpeedY = -ballSpeedY;
                }
            }
        }
    }

    // Handle death
    if (lives <= 0) {
        gameState = HOME;
    }

    // Redraw
    display.clearDisplay();
    display.drawRect(paddleX, paddleY, paddleWidth, paddleHeight, SH110X_WHITE);
    display.fillCircle(ballX, ballY, ballSize, SH110X_WHITE);
    // draw lives
    for (int i = 0; i < lives; i++) {
        display.drawBitmap(2 + i * 8, 2, heart_bmp, 7, 6, SH110X_WHITE);
    }

    // draw bricks
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 3; j++) {
            if (bricks[i][j] == 1) {
                display.fillRect(2 + i * 20, 10 + j * 8, 16, 6, SH110X_WHITE);
            }
        }
    }
    display.display();
    
    delay(10);
}