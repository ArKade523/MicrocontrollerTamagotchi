#include "brick_breaker.hpp"
#include <algorithm>

BrickBreaker::BrickBreaker(Adafruit_SH1106G& disp) : display(disp), 
    paddleWidth(20), paddleHeight(5), paddleY(63), paddleX(64), 
    lives(3), score(0), ballX(64), ballY(20), ballSpeedX(1), ballSpeedY(1), 
    ballSize(2), constantBallSpeed(2)
{
    // Initialize bricks
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 3; j++) {
            bricks[i][j] = 1;
        }
    }
}

void BrickBreaker::handlePaddleMovement() {
    if (digitalRead(LEFT_BUTTON) == LOW) {
        paddleX -= 4;
        if (paddleX < 0) paddleX = 0;
    } else if (digitalRead(RIGHT_BUTTON) == LOW) {
        paddleX += 4;
        if (paddleX > display.width() - paddleWidth) paddleX = display.width() - paddleWidth;
    }
}

void BrickBreaker::updateBallPosition() {
    ballX += ballSpeedX;
    ballY += ballSpeedY;
}

void BrickBreaker::handleBallCollision() {
    // Collision with walls
    if (ballX <= ballSize || ballX >= display.width() - ballSize) ballSpeedX = -ballSpeedX;
    if (ballY <= ballSize) ballSpeedY = -ballSpeedY;

    // Collision with paddle
    if (ballY >= paddleY - ballSize && ballX >= paddleX && ballX <= paddleX + paddleWidth) {
        // ball bounces away an angle depending on where it hits the paddle
        ballSpeedX = (ballX - (paddleX + paddleWidth / 2)) / 4;
        // Ensure ballSpeedX does not exceed the constantBallSpeed
        if (abs(ballSpeedX) > constantBallSpeed) {
            ballSpeedX = constantBallSpeed * (ballSpeedX > 0 ? 1 : -1);
        }

        // Calculate new ballSpeedY maintaining the same overall speed
        ballSpeedY = -sqrt(pow(constantBallSpeed, 2) - pow(ballSpeedX, 2));
    }

    // Collision with bottom
    if (ballY >= display.height() - ballSize) {
        ballX = 64;
        ballY = 32;
        ballSpeedX = 1;
        ballSpeedY = 1;
        lives--;
    }

    // Collision with bricks
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 3; j++) {
            // If the brick is active
            if (bricks[i][j] == 1) {
                // Coordinates of the brick's edges
                int brickLeft = 2 + i * 20;
                int brickRight = brickLeft + 16;
                int brickTop = 10 + j * 8;
                int brickBottom = brickTop + 6;

                // Check if the ball is colliding with the brick
                if (ballX + ballSize > brickLeft && ballX - ballSize < brickRight &&
                    ballY + ballSize > brickTop && ballY - ballSize < brickBottom) {
                    // Collision detected, deactivate the brick
                    bricks[i][j] = 0;
                    score++;

                    // Determine if the collision is more horizontal or vertical
                    int overlapLeft = ballX + ballSize - brickLeft;
                    int overlapRight = brickRight - (ballX - ballSize);
                    int overlapTop = ballY + ballSize - brickTop;
                    int overlapBottom = brickBottom - (ballY - ballSize);

                    // Find the minimum overlap
                    int minOverlap = std::min({overlapLeft, overlapRight, overlapTop, overlapBottom});

                    // Change ball direction based on the side of collision
                    if (minOverlap == overlapLeft || minOverlap == overlapRight) {
                        ballSpeedX = -ballSpeedX; // Horizontal collision
                    } else {
                        ballSpeedY = -ballSpeedY; // Vertical collision
                    }

                    // Only handle one brick collision per ball movement
                    break;
                }
            }
        }
    }
}

void BrickBreaker::handleDeath() {
    if (lives <= 0) {
        display.clearDisplay();
        display.setTextColor(SH110X_WHITE);
        display.setTextSize(1);
        display.setCursor(64 - 4.5 * 6, 32 - 4);
        display.print("Score: ");
        display.print(score);
        display.setCursor(64 - 2 * 6, 40);
        display.print("+");
        display.print(score / 6);
        display.drawBitmap(68, 40, training_bmp, 7, 6, SH110X_WHITE);
        display.display();
        delay(2000);
    }
}

void BrickBreaker::handleWin() {
    bool win = true;
    // Check if all bricks are deactivated
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 3; j++) {
            if (bricks[i][j] == 1) {
                win = false;
                break;
            }
        }
    }

    if (win) {
        display.clearDisplay();
        display.setTextColor(SH110X_WHITE);
        display.setTextSize(1);
        display.setCursor(64 - 4.5 * 6, 32 - 4);
        display.print("Score: ");
        display.print(score);
        display.setCursor(64 - 2 * 6, 40);
        display.print("+5");
        display.drawBitmap(68, 40, training_bmp, 7, 6, SH110X_WHITE);
        display.display();
        delay(2000);
    }
}

void BrickBreaker::drawGame() {
    display.clearDisplay();
    display.drawRect(paddleX, paddleY, paddleWidth, paddleHeight, SH110X_WHITE);
    display.fillCircle(static_cast<int>(ballX), static_cast<int>(ballY), ballSize, SH110X_WHITE);

    // draw lives
    for (int i = 0; i < lives; i++) {
        display.drawBitmap(2 + i * 8, 2, heart_bmp, 7, 6, SH110X_WHITE);
    }

    // draw score
    display.setCursor(128 - 2 * 6, 2);
    display.setTextSize(1);
    display.print(score);

    // draw bricks
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 3; j++) {
            if (bricks[i][j] == 1) {
                display.fillRect(2 + i * 20, 10 + j * 8, 16, 6, SH110X_WHITE);
            }
        }
    }
    display.display();
}

int BrickBreaker::play() {

    while (1) {
        handlePaddleMovement();
        updateBallPosition();
        handleBallCollision();
        handleDeath();
        handleWin();
        drawGame();

        // check if there are any bricks left
        bool bricksLeft = false;
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 3; j++) {
                if (bricks[i][j] == 1) {
                    bricksLeft = true;
                    break;
                }
            }
        }

        if (!bricksLeft) {
            return score;
        }

        if (lives <= 0) {
            return score;
        }

        delay(10);
    }
}