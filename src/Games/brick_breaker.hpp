#pragma once

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include "../globals.h"
#include "../utility/button_interface.hpp"
#include "../Tamagotchi/Tamagotchi.hpp"
#include "../Tamagotchi/bitmaps.hpp"
#include "../Tamagotchi/bitmaps_6x7.hpp"

class BrickBreaker {
    public:
        BrickBreaker(Adafruit_SH1106G& disp);
        int play();
    
    private:
        Adafruit_SH1106G& display;

        // Paddle properties
        const uint8_t paddleWidth, paddleHeight;
        const int paddleY;
        int paddleX;
        int lives;
        uint8_t bricks[6][3];
        int score;

        // Ball properties
        float ballX, ballY;
        float ballSpeedX, ballSpeedY;
        const int ballSize, constantBallSpeed;

        void handleDeath();
        void handleWin();
        void handlePaddleMovement();
        void updateBallPosition();
        void handleBallCollision();
        void drawGame();

};
