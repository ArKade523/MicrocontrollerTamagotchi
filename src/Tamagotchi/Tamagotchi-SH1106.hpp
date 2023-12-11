#pragma once
#include <cstdint>

#include "Tamagotchi.hpp"
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include "../globals.h"

#include "../Games/sheep_jump.hpp"

class Tamagotchi_SH1106 : public Tamagotchi {

public:
    Tamagotchi_SH1106(void);
    uint8_t* getBitmap();

    void drawHome() override;
    void drawMenu() override;
    void feedGameUpdate() override;
    void playGameUpdate() override;
    void trainGameUpdate() override;
    void sleepGameUpdate() override;

    void die() override;

    void rickRoll();

private:
    Adafruit_SH1106G display;
};
