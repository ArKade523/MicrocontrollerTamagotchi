#pragma once

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <vector>
#include "../globals.h"
#include "../utility/button_interface.hpp"
#include "../Tamagotchi/Tamagotchi.hpp"
#include "../Tamagotchi/bitmaps.hpp"
#include "../Tamagotchi/bitmaps_6x7.hpp"

class Snake {
    public:
        Snake(Adafruit_SH1106G& disp);
        int play();
    
    private:
        Adafruit_SH1106G& display;
        enum Direction {UP, LEFT, DOWN, RIGHT};
        struct Position {
            int x;
            int y;
        };

        int snakeLength;
        std::vector<Position> tail;
        Direction snakeDirection;
        int foodX, foodY;
        bool isDead;

        void handleDeath();
        void handleMovement();
        void handleEating();
        void drawGame();
        void grow();

};