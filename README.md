# John Conway's Game of Life
Game of Life written in C/SDL2

Controls:
|Key|Action|
|-|--|
Space|Pause
Escape | Close game
R | Reset board
Left Mouse | Draw
Right Mouse | Erase
Up arrow | Increase simulation speed
Down arrow | Decrease simulation speed



# Build Instructions
Start by making the folder build with the command `mkdir build`

For windows download and extract sdl2 for visual studio then copy the lib and include directories to this directory 

For Linux you must install `cmake` and `libsdl2-dev`

run the commands

```
cmake -B build -S src
```

On windows you must edit in `/build/CMakeCache.txt` the SDL2_DIR variable to the path of this folder.

afterwards run the following commands on either windows or linux:
```
cmake -B build -S src
cd build
cmake --build .
```

On windows, be sure the SDL2.dll is in the same directory as the executable before executing. This file can be found in the lib directory