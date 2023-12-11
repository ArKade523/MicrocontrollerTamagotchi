#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include "../globals.h"
#include "../utility/button_interface.hpp"
#include "../Tamagotchi/Tamagotchi.hpp"
#include "../Tamagotchi/bitmaps.hpp"
#include "../Tamagotchi/bitmaps_6x7.hpp"

#include "sheep_jump.hpp"

#define XMIN 0
#define XMAX 128
#define YMIN 0
#define YMAX 64

#define SHEEP_WIDTH 35
#define SHEEP_HEIGHT 25

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


// Draws sheep at (x,y). Sheep position is from bottom left hand corner.
void sheepJump::drawSheep(int x, int y){
    display.drawRect( x, (64-y-SHEEP_HEIGHT), SHEEP_WIDTH, SHEEP_HEIGHT, SH110X_WHITE);
}

//Updates the position of the sheep
void sheepJump::updateMovement(){
    if (y_position > YMIN) y_velocity += y_acceleration;

    x_position += x_velocity;
    y_position += y_velocity;
    
    if (y_position < YMIN) y_position = YMIN;
}


/*
Game update function
*/
void sheepJump::play(){
    x_position = -SHEEP_WIDTH;                  // Starting Game values
    y_position = YMIN;
    x_velocity = 1;
    y_velocity = 0;
    y_acceleration = -3;

    while (1){                                  // loop until end of game (break statement)
        display.clearDisplay();
        drawSheep(x_position, y_position);

        display.setTextSize(1);
        display.setCursor(0,0);
        display.println(x_position);
        display.setCursor(0,10);
        display.println(y_position);

        display.display();

        updateMovement();
        if (buttonPressed() && (y_position == YMIN)) y_velocity = 20;
        if (sheepOutXBounds()) x_position = -SHEEP_WIDTH;
    }
}