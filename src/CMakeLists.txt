cmake_minimum_required(VERSION 3.13)
project(gameoflife)

find_package(SDL2 REQUIRED)
include_directories(${SDL_INCLUDE_DIRS})


add_executable(gameoflife main.c)
target_link_libraries(gameoflife ${SDL2_LIBRARIES})

if(MSVC)
    target_compile_options(gameoflife PRIVATE /W4 /WX)
else()
    target_compile_options(gameoflife PRIVATE -Wall -Wextra)
endif()

