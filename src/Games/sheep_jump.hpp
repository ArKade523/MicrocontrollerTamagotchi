#pragma once
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include "../globals.h"
#include "../utility/button_interface.hpp"
#include "../Tamagotchi/Tamagotchi.hpp"
#include "../Tamagotchi/bitmaps.hpp"
#include "../Tamagotchi/bitmaps_6x7.hpp"

class sheepJump{
    private:
        Adafruit_SH1106G& display;

        int lives = 3, score = 0;

        int x_position, y_position;
        int x_velocity, y_velocity;
        int y_acceleration;

        int fence_x_position;
        int fence_width;

        #define NUM_GRASS_STRANDS 15
        int grass_locations[NUM_GRASS_STRANDS];

        void updateMovement();
        void resetMovement();
        void resetPosition();

        void drawSheep(int x, int y, int& frame);
        void drawFence();
        void drawHeader();
        void drawGrass();
        void updateGrass();

        bool sheepOutOfBounds();
        inline bool sheepOutXBounds();
        inline bool sheepOutYBounds();
        bool sheepInRange(int x, int y, int w, int h);
        bool sheepInFence();

        void gameEnd();

    public:
        sheepJump(Adafruit_SH1106G& disp);

        int play();
};