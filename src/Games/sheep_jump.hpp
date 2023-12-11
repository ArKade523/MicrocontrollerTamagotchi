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

        int x_position, y_position;
        int x_velocity, y_velocity;
        int y_acceleration;

        void updateMovement();

        void drawSheep(int x, int y);
        bool sheepOutOfBounds();
        inline bool sheepOutXBounds();
        inline bool sheepOutYBounds();

        void gameEnd();

    public:
        sheepJump(Adafruit_SH1106G& disp);

        void play();
};