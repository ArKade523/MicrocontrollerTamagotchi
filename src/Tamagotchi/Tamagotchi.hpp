#pragma once
#include <cstdint>

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
        PLAY,
        TRAIN,
        SLEEP,
        MENU,
        NUM_STATES
    };

    static const int WIDTH = 50;
    static const int HEIGHT = 50;

    Tamagotchi();
    void update();
    void feed();
    void play();
    void train();
    uint8_t* getBitmap();

    virtual void drawHome() = 0;
    virtual void drawMenu() = 0;
    virtual void feedGameUpdate() = 0;
    virtual void playGameUpdate() = 0;
    virtual void trainGameUpdate() = 0;

    State state;
    int hunger;
    int happiness;
    int training;
    int sleepiness;
    int age;
    GameState gameState;

private:
    uint8_t bitmap[WIDTH][HEIGHT] = {{1, 0, 1, 1},
                                     {0, 1, 0, 1},
                                     {1, 0, 1, 1},
                                     {0, 1, 0, 1}};
    uint8_t* bitmapPtr = &bitmap[0][0];
};
