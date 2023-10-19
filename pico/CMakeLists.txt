# Include the Pico SDK
include(pico_sdk_import.cmake)

# Add all your files here
add_executable(${PROJECT_NAME}
    main.cpp
    Tamagotchi.cpp
    Display.hpp  # Header-only files can be included here as well to show up in IDEs
)

# Initialize the Pico SDK
pico_sdk_init()

# Enable stdio over USB and disable stdio over UART
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)

# Generate additional output formats (.hex, .uf2, etc.)
pico_add_extra_outputs(${PROJECT_NAME})

# Link the required libraries
target_link_libraries(${PROJECT_NAME} pico_stdlib hardware_i2c)