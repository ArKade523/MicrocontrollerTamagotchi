#include "snake.hpp"

Snake::Snake(Adafruit_SH1106G& disp) : display(disp), snakeLength(4), isDead(false) {
    randomSeed(analogRead(0));
    foodX = random(0, SCREEN_WIDTH - 8);
    foodY = random(12, SCREEN_HEIGHT - 8);

    // initialize snake position
    int startX = SCREEN_WIDTH / 2;
    int startY = SCREEN_HEIGHT / 2;
    for (int i = 0; i < 2 * snakeLength; i++) {
        tail.push_back({startX - i, startY});
    }
}

void Snake::handleMovement() {
    if (leftButtonPushed()) {
        snakeDirection = static_cast<Direction>((snakeDirection + 1) % 4);
    }

    if (rightButtonPushed()) {
        snakeDirection = static_cast<Direction>((snakeDirection + 3) % 4);
    }

    // Insert new head segment depending on direction
    Position newHead;

    switch (snakeDirection) {
        case UP:
            newHead = {tail.front().x, tail.front().y - 1};
            tail.insert(tail.begin(), newHead);
            break;
        case LEFT:
            newHead = {tail.front().x - 1, tail.front().y};
            tail.insert(tail.begin(), newHead);
            break;
        case DOWN:
            newHead = {tail.front().x, tail.front().y + 1};
            tail.insert(tail.begin(), newHead);
            break;
        case RIGHT:
            newHead = {tail.front().x + 1, tail.front().y};
            tail.insert(tail.begin(), newHead);
            break;
    }

    // Remove the last segment of the tail
    tail.pop_back();
}

void Snake::handleDeath() {
    // Check if snake is out of bounds
    if (tail.front().x < 0 || tail.front().x > SCREEN_WIDTH || tail.front().y < 0 || tail.front().y > SCREEN_HEIGHT) {
        isDead = true;
    }

    // Check if snake has collided with itself
    for (uint i = 1; i < tail.size(); i++) {
        if (tail.front().x == tail[i].x && tail.front().y == tail[i].y) {
            isDead = true;
        }
    }
}

void Snake::handleEating() {
    if (tail.front().x >= foodX - 2 && tail.front().x <= foodX + 6 && tail.front().y >= foodY - 2 && tail.front().y <= foodY + 6) {
        grow();
        snakeLength++;
        foodX = random(0, SCREEN_WIDTH - 8);
        foodY = random(12, SCREEN_HEIGHT - 8);
    }
}

void Snake::grow() {
    // Duplicate the last segment of the tail twice so that it looks longer
    tail.push_back(tail.back());
    tail.push_back(tail.back());
}

void Snake::drawGame() {
    display.clearDisplay();

    // draw score
    display.setTextColor(SH110X_WHITE);
    display.setTextSize(1);
    display.setCursor(64 - 4.5 * 6, 0);
    display.print("Score: ");
    display.print(snakeLength - 4);

    // Draw food
    display.drawBitmap(foodX, foodY, hunger_bmp, 7, 6, SH110X_WHITE);

    // Draw head
    switch (snakeDirection) {
        case UP:
            display.drawBitmap(tail.front().x - 1, tail.front().y - 2, snake_head_vertical_up_bmp, 6, 7, SH110X_WHITE);
            break;
        case LEFT:
            display.drawBitmap(tail.front().x - 2, tail.front().y - 1, snake_head_horizontal_left_bmp, 7, 6, SH110X_WHITE);
            break;
        case DOWN:
            display.drawBitmap(tail.front().x - 1, tail.front().y, snake_head_vertical_down_bmp, 6, 7, SH110X_WHITE);
            break;
        case RIGHT:
            display.drawBitmap(tail.front().x, tail.front().y - 1, snake_head_horizontal_right_bmp, 7, 6, SH110X_WHITE);
            
            break;
    }

    // Draw snake body
    for (uint i = 1; i < tail.size() - 1; i++) {
        Position segment = tail[i];
        display.fillRect(segment.x, segment.y, 4, 4, SH110X_WHITE);
    }

    // Draw tail
    if (tail.back().x > tail[tail.size() - 2].x) {
        // LEFT
        display.fillTriangle(tail.back().x, tail.back().y, tail.back().x, tail.back().y + 3, tail.back().x + 6, tail.back().y + 2, SH110X_WHITE);
    } else if (tail.back().y > tail[tail.size() - 2].y) {
        // UP
        display.fillTriangle(tail.back().x, tail.back().y, tail.back().x + 3, tail.back().y, tail.back().x + 2, tail.back().y + 6, SH110X_WHITE);
    } else if (tail.back().x < tail[tail.size() - 2].x) {
        // RIGHT
        display.fillTriangle(tail.back().x, tail.back().y, tail.back().x, tail.back().y + 3, tail.back().x - 6, tail.back().y + 2, SH110X_WHITE);
    } else if (tail.back().y < tail[tail.size() - 2].y) {
        // DOWN
        display.fillTriangle(tail.back().x, tail.back().y, tail.back().x + 3, tail.back().y, tail.back().x + 2, tail.back().y - 6, SH110X_WHITE);
    }

    display.display();
}

int Snake::play() {
    while (!isDead) {
        handleMovement();
        handleDeath();
        handleEating();
        drawGame();
        delay(20);
    }

    display.clearDisplay();
    display.setTextColor(SH110X_WHITE);
    display.setTextSize(1);
    display.setCursor(64 - 4.5 * 6, 32 - 4);
    display.print("Score: ");
    display.print(snakeLength - 4);
    display.setCursor(64 - (2 + ((snakeLength - 4) / 2) / 10) * 6, 40);
    display.print("+");
    display.print((snakeLength - 4) / 2);
    display.drawBitmap(68, 40, hunger_bmp, 7, 6, SH110X_WHITE);
    display.display();
    delay(2000);

    return snakeLength;
}