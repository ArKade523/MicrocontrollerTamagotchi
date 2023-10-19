#include "RaylibDisplay.hpp"
#include <cstdint>
#include <iostream>
#include <unistd.h>

RaylibDisplay::RaylibDisplay() {
    InitWindow(gridSizeX * squareSize, gridSizeY * squareSize + buttonAreaHeight, "RaylibDisplay");
    SetTargetFPS(60);
}

void RaylibDisplay::Render(uint8_t *bitmap, uint64_t size) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    // Draw the bitmap
    for (int y = 0; y < gridSizeY; y++) {
        for (int x = 0; x < gridSizeX; x++) {
            unsigned long index = y * gridSizeX + x;
            // Check that the index is within the size bounds of the bitmap
            if (index < size) {
                Color color = bitmap[index] ? WHITE : BLACK;
                DrawRectangle(x * squareSize, y * squareSize, squareSize, squareSize, color);
            }
        }
    }
    DrawRectangle(feedButtonCoordinates[0], feedButtonCoordinates[1], buttonSize, buttonSize, RED);
    DrawRectangle(playButtonCoordinates[0], playButtonCoordinates[1], buttonSize, buttonSize, GREEN);
    DrawRectangle(cleanButtonCoordinates[0], cleanButtonCoordinates[1], buttonSize, buttonSize, BLUE);
    EndDrawing();
}

bool RaylibDisplay::buttonPressed(std::uint32_t pin) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        switch(pin) {
            case 2:
                // make sure that the button is pressed within the button area
                if (GetMouseX() > feedButtonCoordinates[0] && GetMouseX() < feedButtonCoordinates[0] + buttonSize &&
                    GetMouseY() > feedButtonCoordinates[1] && GetMouseY() < feedButtonCoordinates[1] + buttonSize) {
                    std::cout << "Feed button pressed" << std::endl;
                    return true;
                }
                return false;
            case 3:
                if (GetMouseX() > playButtonCoordinates[0] && GetMouseX() < playButtonCoordinates[0] + buttonSize &&
                    GetMouseY() > playButtonCoordinates[1] && GetMouseY() < playButtonCoordinates[1] + buttonSize) {
                    std::cout << "Play button pressed" << std::endl;
                    return true;
                }
                return false;
            case 4:
                if (GetMouseX() > cleanButtonCoordinates[0] && GetMouseX() < cleanButtonCoordinates[0] + buttonSize &&
                    GetMouseY() > cleanButtonCoordinates[1] && GetMouseY() < cleanButtonCoordinates[1] + buttonSize) {
                    std::cout << "Clean button pressed" << std::endl;
                    return true;
                }
                return false;
        }
    }
    return false;
}
