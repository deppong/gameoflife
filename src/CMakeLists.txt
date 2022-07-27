cmake_minimum_required(VERSION 3.18)

project(gameoflife)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(gameoflife main.c)
if(MSVC)
    target_link_libraries(gameoflife ${SDL2_LIBRARIES})
    target_compile_options(gameoflife PRIVATE /W4)
else()
    target_link_libraries(gameoflife ${SDL2_LIBRARIES} -ldl -lm)
    target_compile_options(gameoflife PRIVATE -Wall -Wextra)
endif()