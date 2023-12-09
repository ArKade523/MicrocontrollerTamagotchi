#ifndef GLOBALS_H
#define GLOBALS_H

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define RIGHT_BUTTON 10
#define LEFT_BUTTON 11
#define CENTER_BUTTON 12

/* Uncomment the initialize the I2C address , uncomment only one, If you get a totally blank screen try the other */
#define i2c_Address 0x3c //initialize with the I2C addr 0x3C Typically eBay OLED's
//#define i2c_Address 0x3d //initialize with the I2C addr 0x3D Typically Adafruit OLED's

#define OLED_RESET -1   //   QT-PY / XIAO

#endif // GLOBALS_H