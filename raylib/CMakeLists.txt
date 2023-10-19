# Find Raylib
find_package(raylib REQUIRED)

# Add source files
add_executable(${PROJECT_NAME} 
    main.cpp
    ../Tamagotchi.cpp
    RaylibDisplay.cpp)

# Link with the Raylib library
target_link_libraries(${PROJECT_NAME} ${raylib_LIBRARIES})
target_include_directories(${PROJECT_NAME} PRIVATE ${raylib_INCLUDE_DIRS})