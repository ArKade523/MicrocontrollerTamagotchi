#pragma once

#include <cstdint>
#include <binary.h>

static const uint8_t heart_bmp[] = {
    B01101100, 
    B10111110,
    B10111110,
    B01011100,
    B00111000,
    B00010000
};

static const uint8_t hunger_bmp[] = {
    B00111000,
    B01111100,
    B00000000,
    B11111110,
    B00000000,
    B01111100
};

static const uint8_t training_bmp[] = {
    B01000100,
    B11000110,
    B11111110,
    B11111110,
    B11000110,
    B01000100
};

static const uint8_t sleeping_bmp[] = {
    B00001110,
    B11100010,
    B00100100,
    B01001000,
    B10001110,
    B11100000
};

static const uint8_t snake_head_vertical_up_bmp[] = {
    B00110000,
    B01111000,
    B10110100,
    B11111100,
    B11111100,
    B01111000,
    B01111000,
};

static const uint8_t snake_head_vertical_down_bmp[] = {
    B01111000,
    B01111000,
    B11111100,
    B11111100,
    B10110100,
    B01111000,
    B00110000,
};

static const uint8_t snake_head_horizontal_right_bmp[] = {
    B00111000,
    B11110100,
    B11111110,
    B11111110,
    B11110100,
    B00111000
};

static const uint8_t snake_head_horizontal_left_bmp[] = {
    B00111000,
    B01011110,
    B11111110,
    B11111110,
    B01011110,
    B00111000
};