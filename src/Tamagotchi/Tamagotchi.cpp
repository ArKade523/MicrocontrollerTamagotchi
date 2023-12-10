#include "Tamagotchi.hpp"
#include <cstdlib>
#include <cstdint>
#include <ctime>
#include <cstring>
// #include "bitmaps.hpp"


Tamagotchi::Tamagotchi() : state(EGG), hunger(100), happiness(100), training(0), age(0), gameState(NORMAL) {
    // Display Initialization code


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
        // std::memcpy(bitmap, food_bmp, sizeof(food_bmp));
    }

    if (hunger < 50) {
        // If the tamagotchi is hungry, change the state of the bitmap to display a hungry tamagotchi.

    }

    { // Aging

        if (age >= 10 && state == BABY) {
            // If the tamagotchi is 10 and a baby, evolve the tamagotchi to the next state.
            state = CHILD;
        }

        if (age >= 20 && state == CHILD) {
            // If the tamagotchi is 20 and a child, evolve the tamagotchi to the next state.
            state = TEEN;
        }

        if (age >= 30 && state == TEEN) {
            // If the tamagotchi is 30 and a teen, evolve the tamagotchi to the next state.
            state = ADULT;
        }

        if (age >= 50 && state == ADULT) {
            // If the tamagotchi is 50 and an adult, evolve the tamagotchi to the next state.
            state = SPECIAL;
        }
        
        if (age >= 100 && state == SPECIAL) {
            // If the tamagotchi is 100 and a special, evolve the tamagotchi to the next state.
            state = SENIOR;
        }

    }

    if (training >= 100) {
        // If the tamagotchi is fully trained, evolve the tamagotchi to the next state instantly
        training = 0;
        state = static_cast<State>(static_cast<int>(state) + 1);
    }

    // State machine to determine whether a game is running
    switch (gameState) {
        case NORMAL:
            // If the game state is normal, do nothing
            drawHome();
            break;
        case MENU:
            // If the game state is menu, run the menu game update
            drawMenu();
            break;
        case FEED:
            // If the game state is feed, run the feed game update
            feedGameUpdate();
            break;
        case PLAY:
            // If the game state is play, run the play game update
            playGameUpdate();
            break;
        case TRAIN:
            // If the game state is train, run the train game update
            trainGameUpdate();
            break;

        default:
            // If gameState is invalid, set it to normal
            gameState = NORMAL;
            drawHome();
            break;
    }

}

void Tamagotchi::feed() {
    // std::memcpy(bitmap, food_bmp, sizeof(food_bmp));
    hunger += 10;
}

void Tamagotchi::play() {
    // std::memcpy(bitmap, play_bmp, sizeof(play_bmp));
    happiness += 10;
}

void Tamagotchi::train() {
    // std::memcpy(bitmap, train_bmp, sizeof(train_bmp));
    // train to 
    training += 10;
}

uint8_t* Tamagotchi::getBitmap() {
    // Return the bitmap
    return &bitmap[0][0];
}
