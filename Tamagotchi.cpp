#include "Tamagotchi.hpp"
#include <cstdlib>
#include <cstdint>
#include <ctime>
#include <cstring>
#include "bitmaps.hpp"

Tamagotchi::Tamagotchi() : state(EGG), hunger(100), happiness(100), health(100) {
    // Initialization code
}

void Tamagotchi::update() {
    // Update the state, reduce hunger, happiness, etc.
    // Change states if conditions are met
    int random = rand() % 1000;
    if (random == 0) {
        hunger -= 1;

    } else if (random == 1){
        happiness -= 1;

    }

    if (happiness < 50) {
        // If the tamagotchi is sad, change the state of the bitmap to display a sad tamagotchi.
        // TODO: Create a sad tamagotchi animation loop
        std::memcpy(bitmap, food_bmp, sizeof(food_bmp));
    }
}

void Tamagotchi::feed() {
    std::memcpy(bitmap, food_bmp, sizeof(food_bmp));
    hunger += 10;
}

void Tamagotchi::play() {
    std::memcpy(bitmap, play_bmp, sizeof(play_bmp));
    happiness += 10;
}

void Tamagotchi::clean() {
    std::memcpy(bitmap, clean_bmp, sizeof(clean_bmp));
    // clean stuff, maybe improve health
    health += 10;
}

uint8_t* Tamagotchi::getBitmap() {
    // Return the bitmap
    return &bitmap[0][0];
}
