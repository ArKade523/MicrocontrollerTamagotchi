#pragma once
#include "raylib.h"
#include <cstdint>

class RaylibDisplay {
private:
    static const uint32_t gridSizeX = 128;
    static const uint32_t gridSizeY = 64;
    static const uint32_t squareSize = 5;  // Assuming each square is 5x5 pixels
    static const uint32_t buttonSize = 40; // Assuming each button is 10x10 pixels
    static const uint32_t buttonAreaHeight = 80;
    static constexpr uint32_t feedButtonCoordinates[2] = {gridSizeX * squareSize / 4, gridSizeY * squareSize + buttonAreaHeight / 2 - buttonSize / 2};
    static constexpr uint32_t playButtonCoordinates[2] = {gridSizeX * squareSize / 2, gridSizeY * squareSize + buttonAreaHeight / 2 - buttonSize / 2};
    static constexpr uint32_t cleanButtonCoordinates[2] = {gridSizeX * 3 * squareSize / 4, gridSizeY * squareSize + buttonAreaHeight / 2 - buttonSize / 2};

public:

    // Constructor
    RaylibDisplay();

    // Render a bitmap onto the Raylib window
    void Render(uint8_t *bitmap, uint64_t size);

    // Check if a button is pressed
    static bool buttonPressed(std::uint32_t pin);
};
