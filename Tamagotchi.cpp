#include "Tamagotchi.hpp"
#include <cstdlib>
#include <ctime>

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
}

void Tamagotchi::feed() {
    hunger += 10;
}

void Tamagotchi::play() {
    happiness += 10;
}

void Tamagotchi::clean() {
    // clean stuff, maybe improve health
}
