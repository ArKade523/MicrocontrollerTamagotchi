#include "Tamagotchi-SH1106.hpp"
#include "Tamagotchi.hpp"
#include "../globals.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include "bitmaps_6x7.hpp"
#include "../utility/button_interface.hpp"
#include "bitmaps.hpp"
#include <algorithm>

#include "../Games/sheep_jump.hpp"
#include "../Games/brick_breaker.hpp"
#include "../Games/snake.hpp"

Tamagotchi_SH1106::Tamagotchi_SH1106(void) : display(Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET)) {
    delay(250); // wait for the OLED to power up
    display.begin(i2c_Address, true); // Address 0x3C default
    display.clearDisplay();
}

void Tamagotchi_SH1106::drawHome() {
    display.clearDisplay();

    // Hunger stat
    display.drawBitmap(2, 2, hunger_bmp, 7, 6, SH110X_WHITE);
    display.drawLine(11, 3, 31, 3, SH110X_WHITE);
    display.drawLine(11, 6, 31, 6, SH110X_WHITE);
    if (hunger > 0) display.drawRect(11, 4, hunger / 5, 2, SH110X_WHITE);

    // Happiness stat
    display.drawBitmap(34, 2, heart_bmp, 7, 6, SH110X_WHITE);
    display.drawLine(43, 3, 63, 3, SH110X_WHITE);
    display.drawLine(43, 6, 63, 6, SH110X_WHITE);
    if (happiness > 0) display.drawRect(43, 4, happiness / 5, 2, SH110X_WHITE);

    // Training stat
    display.drawBitmap(66, 2, training_bmp, 7, 6, SH110X_WHITE);
    display.drawLine(75, 3, 95, 3, SH110X_WHITE);
    display.drawLine(75, 6, 95, 6, SH110X_WHITE);
    if (training > 0) display.drawRect(75, 4, (training*20)/training_needed.at(state), 2, SH110X_WHITE);      // Fill the training bar proportionally to how much training is done

    // Sleepiness stat
    display.drawBitmap(98, 2, sleeping_bmp, 7, 6, SH110X_WHITE);
    display.drawLine(107, 3, 127, 3, SH110X_WHITE);
    display.drawLine(107, 6, 127, 6, SH110X_WHITE);
    if (sleepiness > 0) display.drawRect(107, 4, sleepiness / 5, 2, SH110X_WHITE);

    // Stats bottom line
    display.drawLine(0, 10, 128, 10, SH110X_WHITE);

    // Draw tamagotchi
    display.drawBitmap(64 - 20, 18, state_bitmap.at(state), 40, 40, SH110X_WHITE);

    if (centerButtonPushed()) {
        gameState = MENU;
    }

    display.display();
}

void Tamagotchi_SH1106::drawMenu() {
    display.clearDisplay();
    display.setTextColor(SH110X_WHITE);
    display.setTextSize(1);
    display.setCursor(64 - 6.5 * 6, 0);
    display.print("Select a game");

    static GameState selectedGame = HOME;

    delay(50);

    if (centerButtonPushed()) {
        gameState = selectedGame;
    }

    if (leftButtonPushed()) {
        selectedGame = static_cast<GameState>((static_cast<int>(selectedGame) + 
            static_cast<int>(GameState::NUM_STATES) - 2) % (static_cast<int>(GameState::NUM_STATES) - 1));
    } else if (rightButtonPushed()) {
        selectedGame = static_cast<GameState>((static_cast<int>(selectedGame) + 1)
            % (static_cast<int>(GameState::NUM_STATES) - 1));
    }

    switch(selectedGame) {
        case HOME:
            display.setTextSize(2);
            display.setCursor(64 - 2 * 12, 32 - 8);
            display.print("Home");
            break;
        // case PLAY:
        //     display.setTextSize(2);
        //     display.setCursor(64 - 2 * 12, 32 - 8);
        //     display.print("Play");
        //     break;
        case TRAIN:
            display.setTextSize(2);
            display.setCursor(64 - 2.5 * 12, 32 - 8);
            display.print("Train");
            break;
        case FEED:
            display.setTextSize(2);
            display.setCursor(64 - 2 * 12, 32 - 8);
            display.print("Feed");
            break;
        case SLEEP:
            display.setTextSize(2);
            display.setCursor(64 - 2.5 * 12, 32 - 8);
            display.print("Sleep");
            break;
        default:
            display.setTextSize(2);
            display.setCursor(64 - 1 * 12, 32 - 8);
            display.print("??");
            break;
    }

    display.fillTriangle(2, 32, 7, 27, 7, 37, SH110X_WHITE);
    display.fillTriangle(126, 32, 121, 27, 121, 37, SH110X_WHITE);

    display.display();
}

void Tamagotchi_SH1106::playGameUpdate() {
    tire();
    happiness+=2;
    gameState = HOME;
}

void Tamagotchi_SH1106::feedGameUpdate() {
    Snake snakeGame {display};              // Initialize the game by providing the display information
    int score = snakeGame.play();           // Will return score once the game ends

    // Update hunger stat
    hunger += score / 2;
    // Increase sleepiness

    tire();
    gameState = HOME;
}

void Tamagotchi_SH1106::sleepGameUpdate() {
    sheepJump sheepGame {display};          // Initialize the game by providing the display information
    sleepiness += sheepGame.play();         // Will return increase in sleep score once the game ends

    gameState = HOME;
}

void Tamagotchi_SH1106::trainGameUpdate() {

    BrickBreaker brickGame {display};       // Initialize the game by providing the display information
    int score = brickGame.play();           // Will return score once the game ends

    // Update training stat
    if (score < 18) {
        training += score / 6;
    } else {
        training += 5;
    }

    tire();
    gameState = HOME;
}

void Tamagotchi_SH1106::die(){
    display.clearDisplay();

    display.setTextSize(1);
    display.setCursor(64 - (9/2)*6, 0);
    display.println("GAME OVER");

    display.drawLine(0, 10, 128, 10, SH110X_WHITE);

    // Draw dead tamagotchi
    display.drawBitmap(64 - 15, 18, dead_bmp, 40, 40, SH110X_WHITE);

    display.display();

    // Dead loop
    while(1);
}

void Tamagotchi_SH1106::rickRoll(){
    display.clearDisplay();
    display.drawBitmap(0,0,rick_astley_bmp, 114, 64, SH110X_WHITE);
    
    display.setTextSize(1);
    display.setCursor(5,5);
    display.println("Never");
    display.setCursor(5,5+8+5);
    display.println("gonna");
    display.setCursor(5,5+(8+5)*2);
    display.println("give");
    display.setCursor(5,5+(8+5)*3);
    display.println("you");
    display.setCursor(5,5+(8+5)*4);
    display.println("up");
    display.display();

    while(1);
}