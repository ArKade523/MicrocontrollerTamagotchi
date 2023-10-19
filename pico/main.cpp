#include "Tamagotchi.hpp"
#include <cstdint>
extern "C" {
#include "pico/stdlib.h"
}
#include "pico/Display.hpp"


int main() {
    stdio_init_all();
    Display display;
    Tamagotchi pet;

    const std::uint32_t FEED_BUTTON_PIN = 2;
    const std::uint32_t PLAY_BUTTON_PIN = 3;
    const std::uint32_t CLEAN_BUTTON_PIN = 4;

    // Initialize buttons
    gpio_init(FEED_BUTTON_PIN);
    gpio_set_dir(FEED_BUTTON_PIN, GPIO_IN);
    gpio_pull_up(FEED_BUTTON_PIN);

    gpio_init(PLAY_BUTTON_PIN);
    gpio_set_dir(PLAY_BUTTON_PIN, GPIO_IN);
    gpio_pull_up(PLAY_BUTTON_PIN);

    gpio_init(CLEAN_BUTTON_PIN);
    gpio_set_dir(CLEAN_BUTTON_PIN, GPIO_IN);
    gpio_pull_up(CLEAN_BUTTON_PIN);

    while (true) {
        pet.update();
        // Update display based on Tamagotchi state

        if (gpio_get(FEED_BUTTON_PIN)) {
            pet.feed();
        }
        if (gpio_get(PLAY_BUTTON_PIN)) {
            pet.play();
        }
        if (gpio_get(CLEAN_BUTTON_PIN)) {
            pet.clean();
        }

        display.drawBitmap(pet.getBitmap(), sizeof(uint8_t) * pet.WIDTH * pet.HEIGHT);

        sleep_ms(100);
    }
}
