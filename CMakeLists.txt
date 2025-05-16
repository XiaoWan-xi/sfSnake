cmake_minimum_required(VERSION 3.16)
project(sfSnake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output directory for all build types
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# Download and build the latest SFML (3.x) with FetchContent
# first time build may take more time because of the fetch
# please ensure that your device can correctly connect to Github
include(FetchContent)
set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_DOC OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_AUDIO ON CACHE BOOL "" FORCE)
set(SFML_BUILD_GRAPHICS ON CACHE BOOL "" FORCE)
set(SFML_BUILD_WINDOW ON CACHE BOOL "" FORCE)
set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)
FetchContent_Declare(
    sfml
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG master
)
FetchContent_MakeAvailable(sfml)

add_executable(sfSnake
    main.cpp
    Fruit.cpp
    Game.cpp
    GameOverScreen.cpp
    GameScreen.cpp
    MenuScreen.cpp
    Screen.cpp
    Snake.cpp
    SnakeNode.cpp
)

target_link_libraries(sfSnake PRIVATE SFML::Graphics SFML::Window SFML::Audio SFML::System)

target_include_directories(sfSnake PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Copy SFML DLLs to output dir after build (Windows only)
if(WIN32)
    add_custom_command(TARGET sfSnake POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "$<TARGET_FILE_DIR:sfml-graphics>"
            "$<TARGET_FILE_DIR:sfSnake>"
    )
endif()

# Copy asset folders to output dir
add_custom_command(TARGET sfSnake POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/Fonts"
        "$<TARGET_FILE_DIR:sfSnake>/Fonts"
)
add_custom_command(TARGET sfSnake POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/Music"
        "$<TARGET_FILE_DIR:sfSnake>/Music"
)
add_custom_command(TARGET sfSnake POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/Sounds"
        "$<TARGET_FILE_DIR:sfSnake>/Sounds"
)
