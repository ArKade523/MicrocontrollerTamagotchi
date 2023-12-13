#pragma once
#include <cstdint>
#include <map>
#include "bitmaps.hpp"

class Tamagotchi {
public:
    enum State {
        EGG,
        BABY,
        CHILD,
        TEEN,
        ADULT,
        SPECIAL,
        SENIOR,
        GHOST
    };

    enum GameState {
        HOME,
        FEED,
        TRAIN,
        SLEEP,
        MENU,
        NUM_STATES
    };


    // A map of the ammount of training needed to upgrade to next state
    const std::map<State, int> training_needed = {
        {EGG, 5},
        {BABY, 25},
        {CHILD, 50},
        {TEEN, 100},
        {ADULT, 1000}
    };

    const std::map<State, const uint8_t*> state_bitmap = {
        {EGG, egg_uncracked_bmp},
        {BABY, baby_bmp},
        {CHILD, child_bmp},
        {TEEN, teen_bmp},
        {ADULT, adult_bmp},
        {GHOST, dead_bmp}
    };

    static const int WIDTH = 40;
    static const int HEIGHT = 40;

    Tamagotchi();
    void update();
    void feed();
    void play();
    void train();
    void tire();
    virtual void die() = 0;

    virtual void drawHome() = 0;
    virtual void drawMenu() = 0;
    virtual void feedGameUpdate() = 0;
    virtual void playGameUpdate() = 0;
    virtual void trainGameUpdate() = 0;
    virtual void sleepGameUpdate() = 0;

    State state = EGG;
    int hunger;
    int happiness;
    int training;
    int sleepiness;
    // int age;
    GameState gameState;

};
