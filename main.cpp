#include "Tamagotchi.hpp"
#include <cstdint>
#include "Display.hpp"
extern "C" {
#include "pico/stdlib.h"
}

int main() {
    stdio_init_all();
    Display display;
    Tamagotchi pet;

    const std::uint32_t FEED_BUTTON_PIN = 2;
    const std::uint32_t PLAY_BUTTON_PIN = 3;
    const std::uint32_t CLEAN_BUTTON_PIN = 4;

    gpio_init(FEED_BUTTON_PIN);
    gpio_set_dir(FEED_BUTTON_PIN, GPIO_IN);
    gpio_pull_up(FEED_BUTTON_PIN);

    // Similarly initialize PLAY_BUTTON_PIN and CLEAN_BUTTON_PIN

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

        sleep_ms(100);
    }
}
