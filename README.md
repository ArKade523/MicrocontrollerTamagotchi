# Microcontroller Tamagotchi

This is a project to create a Tamagotchi-esque device using a microcontroller, three buttons, and a small 64x128 pixel display.

Component list:
- We used the [Adafruit Feather M4 Express](https://www.adafruit.com/product/3857), but any microcontroller small enough would work
- Generic push-buttons (We used [these](https://www.adafruit.com/product/3101) from Adafruit, since they feel nicer to use for long periods of time)
- [64x128px Display](https://www.amazon.com/dp/B0C3L7N917?ref=ppx_yo2ov_dt_b_product_details&th=1)
- Generic 1000mAh LiPo battery
- Generic TP4056 charging board

Graphics are handled via the [Adafruit_SH110X](https://github.com/adafruit/Adafruit_SH110x) library.

We are using [PlatformIO](https://platformio.org) for our build system. The repository contains a platformio.ini file that contains a reference to our microcontroller. If you choose to use a different one, make sure to update your PlatformIO project settings.

This is a joint project by Kade Angell and Hunter Nelson
