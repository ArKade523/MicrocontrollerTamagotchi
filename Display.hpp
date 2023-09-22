extern "C" {
#include "hardware/i2c.h"
#include "hardware/gpio.h"
}

class Display {
public:
    Display() {
        i2c_init(i2c0, 400 * 1000);  // Initialize I2C at 400KHz
        gpio_set_function(0, GPIO_FUNC_I2C);
        gpio_set_function(1, GPIO_FUNC_I2C);
        gpio_pull_up(0);
        gpio_pull_up(1);
        // Initialization sequence for your display
        uint8_t init_seq[] = { /* ... */ };
        i2c_write_blocking(i2c0, 0x3C, init_seq, sizeof(init_seq), false);
    }

    void drawBitmap(uint8_t *bitmap, size_t size) {
        i2c_write_blocking(i2c0, 0x3C, bitmap, size, false);
    }
};
