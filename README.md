# John Conway's Game of Life
Game of Life written in C/SDL2


## build
For windows, copy the lib and include directories to this directory 
<br>

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
./Debug/gameoflife
```