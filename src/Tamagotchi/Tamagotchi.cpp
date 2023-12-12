#include "Tamagotchi.hpp"
#include <cstdlib>
#include <cstdint>
#include <ctime>
#include <cstring>
// #include "bitmaps.hpp"


Tamagotchi::Tamagotchi() : state(EGG), hunger(100), happiness(100), training(0), sleepiness(100), gameState(HOME) {
    // Display Initialization code


}

void Tamagotchi::update() {
    // Update the state, reduce hunger, happiness, etc.
    // Change states if conditions are met
    int random = rand() % 1000;

    if (random == 0) {
        hunger -= 1;

    } 
    
    int low_stats = (100 - sleepiness) + (100 - hunger);
    if (random >= 1 && random <= low_stats){
        happiness -= 1;
    }

    /*
    Maybe these will be implemented at some point
    */

    // if (happiness < 50) {
    //     // If the tamagotchi is sad, change the state of the bitmap to display a sad tamagotchi.
    //     // TODO: Create a sad tamagotchi animation loop
    //     // std::memcpy(bitmap, food_bmp, sizeof(food_bmp));
    // }

    // if (hunger < 50) {
    //     // If the tamagotchi is hungry, change the state of the bitmap to display a hungry tamagotchi.

    // }

    // { // Aging

    //     if (age >= 10 && state == BABY) {
    //         // If the tamagotchi is 10 and a baby, evolve the tamagotchi to the next state.
    //         state = CHILD;
    //     }

    //     if (age >= 20 && state == CHILD) {
    //         // If the tamagotchi is 20 and a child, evolve the tamagotchi to the next state.
    //         state = TEEN;
    //     }

    //     if (age >= 30 && state == TEEN) {
    //         // If the tamagotchi is 30 and a teen, evolve the tamagotchi to the next state.
    //         state = ADULT;
    //     }

    //     if (age >= 50 && state == ADULT) {
    //         // If the tamagotchi is 50 and an adult, evolve the tamagotchi to the next state.
    //         state = SPECIAL;
    //     }
        
    //     if (age >= 100 && state == SPECIAL) {
    //         // If the tamagotchi is 100 and a special, evolve the tamagotchi to the next state.
    //         state = SENIOR;
    //     }

    // }

    // If the tamagotchi is fully trained, evolve the tamagotchi to the next state instantly
    if (training >= training_needed.at(state)) {
        training -= training_needed.at(state);     //Overflow training to next state

        if (state != ADULT) state = static_cast<State>(static_cast<int>(state) + 1);
    }

    // If tamagotchi happiness drops to zero then the tamagotchi dies (TODO: probably should change this stat to something other than happiness)
    if (happiness <= 0){
        die();
    }

    // State machine to determine whether a game is running
    switch (gameState) {
        case HOME:
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
        // case PLAY:
        //     // If the game state is play, run the play game update
        //     playGameUpdate();
        //     break;
        case TRAIN:
            // If the game state is train, run the train game update
            trainGameUpdate();
            break;
        case SLEEP:
            sleepGameUpdate();
            break;

        default:
            // If gameState is invalid, set it to normal
            gameState = HOME;
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

// Increase how tired the tamagotchi is by 10
void Tamagotchi::tire() {       
    sleepiness -= 10;
}

void Tamagotchi::die(){
    // Death behavior
}
