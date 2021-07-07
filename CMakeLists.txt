cmake_minimum_required(VERSION 3.19)
project(pong C)

set(CMAKE_C_STANDARD 99)

set(SDL2_PATH "C:\\Program Files (x86)\\CodeBlocks\\SDL2-devel-2.0.12-mingw\\SDL2-2.0.12\\x86_64-w64-mingw32")
SET(SDL_SEARCH_PATH ${SDL2_PATH})
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

find_package(SDL2 REQUIRED)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
include_directories(${PROJECT_SOURCE_DIR}/include)          #Include project include directory(headers)
link_directories(${PROJECT_SOURCE_DIR}/lib -lmingw32 -lSDL2main -lSDL2)
add_executable(pong main.c src/main_game.c header/main_game.h src/nyanpasu_lib.c header/nyanpasu_lib.h header/struct.h src/gui.c header/gui.h src/gui_game.c header/gui_game.h src/control.c header/control.h)