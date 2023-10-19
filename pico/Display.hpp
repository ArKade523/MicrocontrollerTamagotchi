extern "C" {
#include "hardware/i2c.h"
#include "hardware/gpio.h"
}

#define SH1106_EXTERNALVCC 0x1 // Modify this to match your actual setup
#define SH1106_SETMULTIPLEX 0xA8
#define SH1106_OUTPUT_FOLLOWS_RAM 0xA4
#define SH1106_SETDISPLAYOFFSET 0xD3
#define SH1106_SETSTARTLINE 0x40
#define SH1106_CHARGEPUMP 0x8D
#define SH1106_MEMORYMODE 0x20
#define SH1106_SET_PAGE_ADDRESS 0x22  // This is an educated guess. Please check your documentation.
#define SH1106_COMSCANDEC 0xC8
#define SH1106_SETLOWCOLUMN 0x00      // Also a guess, confirm with your documentation
#define SH1106_SETHIGHCOLUMN 0x10     // Also a guess, confirm with your documentation
#define SH1106_SETCOMPINS 0xDA
#define SH1106_SETCONTRAST 0x81
#define SH1106_SET_SEGMENT_REMAP 0xA1
#define SH1106_SETPRECHARGE 0xD9
#define SH1106_SETVCOMDETECT 0xDB
#define SH1106_DISPLAYALLON_RESUME 0xA4
#define SH1106_NORMALDISPLAY 0xA6

class Display {
public:
    Display(uint8_t vccState = SH1106_EXTERNALVCC, uint8_t i2cAddress = 0x3C) {
        i2c_init(i2c0, 400 * 1000);  // Initialize I2C at 400KHz
        gpio_set_function(0, GPIO_FUNC_I2C);
        gpio_set_function(1, GPIO_FUNC_I2C);
        gpio_pull_up(0);
        gpio_pull_up(1);

        uint8_t vccstate = SH1106_EXTERNALVCC;

        // Power Up sequence:
        // 1. Power up VDD (assume already on)
        // 2. Send Display off command
        uint8_t off_command[] = {0x00, 0xAE}; // Have to start with 0x00 (control byte)
        i2c_write_blocking(i2c0, 0x3C, off_command, 1, false);
        // 3. Initialization
        uint8_t init_seq[] = {
            0x00, 0xF0,
            0x00, SH1106_SETMULTIPLEX, 0x00, 0x3F,
            0x00, SH1106_OUTPUT_FOLLOWS_RAM,
            0x00, SH1106_SETDISPLAYOFFSET, 0x00, 0x0,
            0x00, SH1106_SETSTARTLINE | 0x0,
            0x00, SH1106_CHARGEPUMP, 0x00, (vccstate == SH1106_EXTERNALVCC ? 0x10 : 0x14),
            0x00, SH1106_MEMORYMODE, 0x00, 0x0, // Assuming horizontal addressing
            0x00, SH1106_SET_PAGE_ADDRESS, // Assuming no arguments are needed
            0x00, SH1106_COMSCANDEC,
            0x00, SH1106_SETLOWCOLUMN,
            0x00, SH1106_SETHIGHCOLUMN,
            0x00, SH1106_SETCOMPINS, 0x00, 0x12,
            0x00, SH1106_SETCONTRAST, 0x00, (vccstate == SH1106_EXTERNALVCC ? 0x9F : 0xCF),
            0x00, SH1106_SET_SEGMENT_REMAP,
            0x00, SH1106_SETPRECHARGE, 0x00, (vccstate == SH1106_EXTERNALVCC ? 0x22 : 0xF1),
            0x00, SH1106_SETVCOMDETECT, 0x00, 0x20,
            0x00, SH1106_DISPLAYALLON_RESUME,
            0x00, SH1106_NORMALDISPLAY
        };
        i2c_write_blocking(i2c0, 0x3C, init_seq, sizeof(init_seq), false);
        // 4. Clear Screen

        // 5. Power up VCC/ VBAT
        // 6. Delay 100ms
        // (When VCC is stable)
        // 7. Send Display on command
        uint8_t on_command[] = {0x00, 0xAF};
        i2c_write_blocking(i2c0, 0x3C, on_command, 2, false);
        
    }

    void drawBitmap(uint8_t *bitmap, size_t size) {
        i2c_write_blocking(i2c0, 0x3C, bitmap, size, false);
    }

    private:
        uint8_t buffer[1024];
        uint8_t m_vccState;
        uint8_t m_i2cAddress;
};
