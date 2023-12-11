#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include "../globals.h"
#include "../utility/button_interface.hpp"
#include "../Tamagotchi/Tamagotchi.hpp"
#include "../Tamagotchi/bitmaps.hpp"
#include "../Tamagotchi/bitmaps_6x7.hpp"
#include <cstdlib>

#include "sheep_jump.hpp"

#define XMIN 0
#define XMAX 128
#define YMIN 0
#define YMAX 64

#define SHEEP_WIDTH 27
#define SHEEP_HEIGHT 18

#define FENCE_Y 0
#define FENCE_HEIGHT 15

#define DIFFICULTY_INTERVAL 10


/*
NOTE: the x and y axis for this game are different from the display. (0,0) is at the bottom left hand corner
      with the x axis pointing right and the y axis pointing up.

      The sheep's position is mapped from its bottom left hand corner.
*/


/*
CONSTRUCTOR
*/
sheepJump::sheepJump(Adafruit_SH1106G& disp) : display(disp){}


inline bool buttonPressed(){
    return leftButtonPushed() || centerButtonPushed() || rightButtonPushed();
}


/*
Sheep position detection
*/

// Detects if the sheep sprite is past the left/right display borders
inline bool sheepJump::sheepOutXBounds(){
    if (x_position > XMAX || x_position+SHEEP_WIDTH < XMIN) return true;
    else return false;
}
// Detects if the sheep sprite is past the top/bottom display borders
inline bool sheepJump::sheepOutYBounds(){
    if (y_position+SHEEP_HEIGHT < YMIN || y_position > YMAX) return true;
    else return false;
}
// Detects if the sheep sprite is off the screen
bool sheepJump::sheepOutOfBounds(){
    if (sheepOutXBounds() || sheepOutYBounds()) return true;
    else return false;
}




typedef struct{
    int lowerBound, higherBound;
}range;

/*!
    @brief  Detects if the sheep sprite is within a given rectangular range
    @param  x   x coordinate of the bottom left corner of the rectangular region
    @param  y   y coordinate of the bottom left corner of the rectangular region
    @param  w   width of the rectangular region
    @param  h   height of the rectangular region
*/
bool sheepJump::sheepInRange(int x, int y, int w, int h){
    range smallerX, largerX, smallerY, largerY;

    if (SHEEP_WIDTH >= w){
        smallerX.lowerBound = x;
        smallerX.higherBound = x + w;

        largerX.lowerBound = x_position;
        largerX.higherBound = x_position + SHEEP_WIDTH;
    }
    else{
        smallerX.lowerBound = x_position;
        smallerX.higherBound = x_position + SHEEP_WIDTH;

        largerX.lowerBound = x;
        largerX.higherBound = x + w;
    }

    if (SHEEP_HEIGHT >= h){
        smallerY.lowerBound = x;
        smallerY.higherBound = x + h;

        largerY.lowerBound = y_position;
        largerY.higherBound = y_position + SHEEP_HEIGHT;
    }
    else{
        smallerY.lowerBound = y_position;
        smallerY.higherBound = y_position + SHEEP_HEIGHT;

        largerY.lowerBound = x;
        largerY.higherBound = x + h;
    }

    if (((smallerX.lowerBound >= largerX.lowerBound && smallerX.lowerBound <= largerX.higherBound) || 
         (smallerX.higherBound >= largerX.lowerBound && smallerX.higherBound <= largerX.higherBound)) &&
        ((smallerY.lowerBound >= largerY.lowerBound && smallerY.lowerBound <= largerY.higherBound) || 
         (smallerY.higherBound >= largerY.lowerBound && smallerY.higherBound <= largerY.higherBound)))
    {
        return true;
    }
    else{
        return false;
    }
}
// A specialized version of the sheepInRange function, specifically for the fence.
bool sheepJump::sheepInFence(){
    range sheep_x{.lowerBound = x_position, .higherBound = x_position+SHEEP_WIDTH},
          sheep_y{.lowerBound = y_position, .higherBound = y_position+SHEEP_HEIGHT},
          fence_x{.lowerBound = fence_x_position, .higherBound = fence_x_position+fence_width},
          fence_Y{.lowerBound = FENCE_Y, .higherBound = fence_x_position+FENCE_HEIGHT};

    if (((fence_x.lowerBound >= sheep_x.lowerBound && fence_x.lowerBound <= sheep_x.higherBound) ||
         (fence_x.higherBound >= sheep_x.lowerBound && fence_x.higherBound <= sheep_x.higherBound)) &&
        ((fence_Y.lowerBound >= sheep_y.lowerBound && fence_Y.lowerBound <= sheep_y.higherBound) ||
         (fence_Y.higherBound >= sheep_y.lowerBound && fence_Y.higherBound <= sheep_y.higherBound)))
    {
        return true;
    }
    else{
        return false;
    }
}


/*
Display Functions
*/
// Draws sheep at (x,y). Sheep position is from bottom left hand corner.
void sheepJump::drawSheep(int x, int y, int& frame){
    #define FRAMESWITCH 3

    frame++;
    if (frame/(FRAMESWITCH*2)) frame = 0;

    display.drawBitmap(x, 64-y-SHEEP_HEIGHT, sheep[ frame/FRAMESWITCH ], SHEEP_WIDTH, SHEEP_HEIGHT, SH110X_WHITE);
}

// Draws fence at the prespecified coordinates
void sheepJump::drawFence(){
    // Fence is two 2 pixel wide rectangles connected by two lines

    // Fence posts
    display.fillRect(fence_x_position, (64-FENCE_Y-FENCE_HEIGHT), 2, FENCE_HEIGHT, SH110X_WHITE);
    display.fillRect(fence_x_position+fence_width-2, (64-FENCE_Y-FENCE_HEIGHT), 2, FENCE_HEIGHT, SH110X_WHITE);

    // Fence struts
    display.drawLine(fence_x_position, 64-(FENCE_Y+2), fence_x_position+fence_width, 64-(FENCE_HEIGHT-2), SH110X_WHITE);
    display.drawLine(fence_x_position, 64-(FENCE_HEIGHT-2), fence_x_position+fence_width, 64-(FENCE_Y+2), SH110X_WHITE);
    display.drawLine(fence_x_position, 64-(FENCE_HEIGHT-2), fence_x_position+fence_width, 64-(FENCE_HEIGHT-2), SH110X_WHITE);
}

// Draws the display header for the score and lives
void sheepJump::drawHeader(){
    display.fillRect(0,0,128,10,SH110X_BLACK);                  // Fill a bar of black on the top to keep header easily visible

    // draw lives
    for (int i = 0; i < lives; i++) {
        display.drawBitmap(2 + i * 8, 2, heart_bmp, 7, 6, SH110X_WHITE);
    }

    //Display score
    display.setTextSize(1);
    display.setCursor(128 - (7*6) - ((score/10)*6+6), 0);       // Set cursor to print score in the upper right hand corner. (Max 3 digits)
    display.println("Score: ");
    display.setCursor(128 - ((score/10)*6+6), 0);
    display.print(score);
}

// Draws the grass
void sheepJump::drawGrass(){
    display.drawLine(0, 63, 128, 63, SH110X_WHITE);
    for (int i = 0; i < NUM_GRASS_STRANDS; i++){
        display.drawPixel(grass_locations[i], 62, SH110X_WHITE);
    }
}
// Updates grass locations
void sheepJump::updateGrass(){
    for (int i = 0; i < NUM_GRASS_STRANDS; i++){
        grass_locations[i] = std::rand()%128;
    }
}


/*
Movement functions
*/

// Updates the position of the sheep
void sheepJump::updateMovement(){
    if (y_position > YMIN) y_velocity += y_acceleration;

    x_position += x_velocity;
    y_position += y_velocity;
    
    if (y_position < YMIN) y_position = YMIN;
}
// Resets movement to defaults
void sheepJump::resetMovement(){
    x_position = -SHEEP_WIDTH;                  // Starting Game values
    y_position = YMIN;
    x_velocity = 3;
    y_velocity = 0;
    y_acceleration = -1;

    fence_x_position = 70;
    fence_width = 10;
}
// Resets sheep position
void sheepJump::resetPosition(){
    x_position = -SHEEP_WIDTH;                  // Starting Game values
    y_position = YMIN;
}


/*
End of game screen
*/
void sheepJump::gameEnd(){
    display.clearDisplay();
    display.setTextColor(SH110X_WHITE);
    display.setTextSize(1);
    display.setCursor(64 - 4.5 * 6, 32 - 4);
    display.print("Score: ");
    display.print(score);
    display.setCursor(64 - 2 * 6, 40);
    display.print("+");
    display.print(score / DIFFICULTY_INTERVAL);
    display.drawBitmap(68, 40, sleeping_bmp, 7, 6, SH110X_WHITE);
    display.display();
    delay(3000);
}



/*
Game update function
*/

// Starts playing the Sheep Jump game, returns once the game is finished
int sheepJump::play(){
    resetMovement();
    int sheep_animation_frame = 0;

    while (1){                                  // loop until end of game (break statement)
        //Draw current state
        display.clearDisplay();
        drawSheep(x_position, y_position, sheep_animation_frame);
        drawFence();
        drawGrass();
        drawHeader();

        display.display();

        updateMovement();

        //Check new state
        if (sheepInFence()){
            lives--;
            if (lives == 0){
                gameEnd();
                break;                                          // If out of lives then exit game
            }
            resetPosition();
        }
        else{

            if (buttonPressed() && (y_position == YMIN)) y_velocity = 9;    // Jump if a button is pressed and on the ground

            
            if (sheepOutXBounds()){                                         // Score condition
                score++;
                x_position = -SHEEP_WIDTH;
                y_position = YMIN;

                updateGrass();

                // Difficulty management stuff
                int difficulty_level = score/DIFFICULTY_INTERVAL;
                
                if (score%DIFFICULTY_INTERVAL == 0 && difficulty_level <= 3){                                           // Increase difficulty
                    x_velocity++;
                    fence_width += 5*(difficulty_level);
                }
                if (score > DIFFICULTY_INTERVAL){                                                                       // Increase fence size in higher difficulty levels
                    fence_width += difficulty_level;
                }

                fence_x_position = (60 - 3*(difficulty_level%3)) + 
                                    std::rand()%((XMAX- 60 - 3*(difficulty_level)) - 10 - fence_width);                 // Set next fence position to be somewhere randomly between 50 and 10 before the end (increases with difficulty)
            }
        }
    }

    return score/DIFFICULTY_INTERVAL;
}