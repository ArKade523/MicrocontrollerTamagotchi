#include "../Tamagotchi.hpp"
#include <cstdint>
#include "RaylibDisplay.hpp"
#include <unistd.h>

int main() {
    RaylibDisplay display;
    Tamagotchi pet;

    const std::uint32_t FEED_BUTTON_PIN = 2;
    const std::uint32_t PLAY_BUTTON_PIN = 3;
    const std::uint32_t CLEAN_BUTTON_PIN = 4;

    while (true) {
        pet.update();
        // Update display based on Tamagotchi state

        if (display.buttonPressed(FEED_BUTTON_PIN)) {
            pet.feed();
        }
        if (display.buttonPressed(PLAY_BUTTON_PIN)) {
            pet.play();
        }
        if (display.buttonPressed(CLEAN_BUTTON_PIN)) {
            pet.clean();
        }

        display.Render(pet.getBitmap(), sizeof(uint8_t) * pet.WIDTH * pet.HEIGHT);

        usleep(100 * 1000);
    }
}
