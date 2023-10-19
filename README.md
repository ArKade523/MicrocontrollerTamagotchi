# Microcontroller Tamagotchi

This is a project to create a Tamagotchi-esque device using a microcontroller, three buttons, and a small 64x128 pixel display.

Component list:
- [Microcontroller](https://www.raspberrypi.com/documentation/microcontrollers/raspberry-pi-pico.html)
- Generic push-buttons
- [64x128px Display](https://www.amazon.com/dp/B0C3L7N917?ref=ppx_yo2ov_dt_b_product_details&th=1)
- Generic 1000mAh LiPo battery
- Generic TP4056 charging board

I am also using Raylib, a C++ graphics library, to test my Tamagotchi game code.

Installation instructions for Raylib can be found [here](https://www.raylib.com/#supported-platforms). Choose your development platform from the list.

Graphics are displayed from bitmaps, which I store as arrays of 64x128 `uint8_t` values. I've created some utilities to assist with converting `.bmp` files into arrays.

> [!NOTE]  
> Before running any of these tools, make sure that you recompile them for your system

```
# In the utils folder
g++ convertBMP.cpp -o convertBMP
g++ -std=c++17 convertBMPFolder.cpp -o convertBMPFolder 
```

To convert a single bitmap file, run this:
```bash
# In the root directory for this project
./utils/convertBMP <source.bmp file> <output file>
```

To convert an entire folder full of bitmap files, run this:
```bash
# In the root directory for this project
./utils/convertBMPFolder <folder path> <output file.hpp>
```

These will both output content for a `.hpp` file, so you should name it accordingly when running the commands.

This has all been built by Kade Angell, created for fun
