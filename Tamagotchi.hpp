#pragma once
#include <cstdint>

class Tamagotchi {
public:
    enum State {
        EGG,
        CHILD,
        ADULT,
        // ...
    };

    static const int WIDTH = 64;
    static const int HEIGHT = 128;

    Tamagotchi();
    void update();
    void feed();
    void play();
    void clean();
    uint8_t* getBitmap();

private:
    State state;
    int hunger;
    int happiness;
    int health;
    uint8_t bitmap[WIDTH][HEIGHT] = {{1, 0, 1, 1},
                                     {0, 1, 0, 1},
                                     {1, 0, 1, 1},
                                     {0, 1, 0, 1}};
    uint8_t* bitmapPtr = &bitmap[0][0];
};
