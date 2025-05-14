cmake_minimum_required(VERSION 3.10)
project(sfSnake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#if you have no SFML on your device please change the ON into OFF
option(USE_SYSTEM_SFML "Use system installed SFML instead of downloading it" ON)

# Set SFML_DIR to your local SFML installation path if you have SFML on you device
set(SFML_DIR "D:/Develop/SFML-3.0.0/lib/cmake/SFML")

if(USE_SYSTEM_SFML)
    find_package(SFML 3 COMPONENTS Graphics Window System Audio REQUIRED)
    set(SFML_LIBS SFML::Graphics SFML::Window SFML::System SFML::Audio)
else()
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
        GIT_TAG 3.0.0
    )
    FetchContent_MakeAvailable(sfml)
    set(SFML_LIBS SFML::Graphics SFML::Window SFML::System SFML::Audio)
endif()

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

target_link_libraries(sfSnake PRIVATE ${SFML_LIBS})

# Copy DLLs to output directory on Windows
if(WIN32)
    if(${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.21.0")
        add_custom_command(TARGET sfSnake POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_RUNTIME_DLLS:sfSnake>
            $<TARGET_FILE_DIR:sfSnake>
            COMMAND_EXPAND_LISTS
        )
    else()
        # Fallback for older CMake: copy all DLLs from SFML bin directory
        if(USE_SYSTEM_SFML)
            get_target_property(SFML_GRAPHICS_LOCATION SFML::Graphics IMPORTED_LOCATION_RELEASE)
            if(SFML_GRAPHICS_LOCATION)
                get_filename_component(SFML_BIN_DIR "${SFML_GRAPHICS_LOCATION}" DIRECTORY)
                file(GLOB SFML_DLLS "${SFML_BIN_DIR}/*.dll")
                foreach(DLL_FILE ${SFML_DLLS})
                    add_custom_command(TARGET sfSnake POST_BUILD
                        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                        "${DLL_FILE}"
                        $<TARGET_FILE_DIR:sfSnake>
                    )
                endforeach()
            endif()
        else()
            add_custom_command(TARGET sfSnake POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_directory
                "${CMAKE_BINARY_DIR}/_deps/sfml-build/bin/"
                $<TARGET_FILE_DIR:sfSnake>
            )
        endif()
    endif()
endif()

# Set include directories
target_include_directories(sfSnake PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Copy assets to build directory
add_custom_command(TARGET sfSnake POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/Fonts
    ${CMAKE_CURRENT_BINARY_DIR}/Fonts
)

add_custom_command(TARGET sfSnake POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/Sounds
    ${CMAKE_CURRENT_BINARY_DIR}/Sounds
)

add_custom_command(TARGET sfSnake POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/Music
    ${CMAKE_CURRENT_BINARY_DIR}/Music
)

# Set output directories
set_target_properties(sfSnake PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Make sure DLLs are copied to the executable directory on Windows
if(WIN32)
    # This approach ensures all DLLs (including debug versions) are copied
    add_custom_command(TARGET sfSnake POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:SFML::Graphics>
            $<TARGET_FILE:SFML::Window>
            $<TARGET_FILE:SFML::Audio>
            $<TARGET_FILE:SFML::System>
            $<TARGET_FILE_DIR:sfSnake>
    )
    
    # Copy any additional DLLs SFML might need
    if(EXISTS "${SFML_BINARY_DIR}/bin/openal32.dll")
        add_custom_command(TARGET sfSnake POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${SFML_BINARY_DIR}/bin/openal32.dll"
                $<TARGET_FILE_DIR:sfSnake>
        )
    endif()
endif()

# Install rules (optional)
install(TARGETS sfSnake
    RUNTIME DESTINATION bin
)

# Enable compiler warnings
if(MSVC)
    target_compile_options(sfSnake PRIVATE /W4)
else()
    target_compile_options(sfSnake PRIVATE -Wall -Wextra)
endif()

# Output some configuration info
message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
message(STATUS "CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}")