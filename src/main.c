/*
    John Conway's Game of Life 
    programmed in C/SDL2 by Isaiah Deppong

*/
#ifdef __unix__

    #include <SDL2/SDL.h>

#elif defined(_WIN32)

    #include <SDL.h>

#endif

#include <stdio.h>
#include <stdlib.h>

const int WIDTH  = 800;
const int HEIGHT = 800;
const int res    =  40;

int main(int argc, char**argv) {
    // Initialization -------------------- 
    int quit = 1;
    SDL_Init(SDL_INIT_VIDEO);

    srand(time(0));

    SDL_Window *window = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    const int num_cells = (WIDTH*HEIGHT)/res;
    const int cell_w = WIDTH/res;
    const int cell_h = HEIGHT/res;

    uint8_t *grid = malloc(sizeof(uint8_t) * num_cells);
    for (int i = 0; i < num_cells; i++) {
        grid[i] = rand() % 2;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    SDL_Event e;

    while(quit) {
        SDL_PollEvent(&e);

        switch (e.type) {
            case SDL_QUIT: quit=0; break;
        }

        // display each cell
        for (int i = 0; i < res; i++) {
            for (int j = 0; j < res; j++) {
                SDL_Rect rect = {
                    cell_w + i*cell_w, 
                    cell_h + j*cell_h, 
                    .w=cell_w, 
                    .h=cell_h
                };
                if (grid[i + j*WIDTH]) {
                    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
                } else {
                    SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255);
                }
                SDL_RenderFillRect(renderer, &rect);
            }
        }

        SDL_RenderPresent(renderer);
    }

    free(grid);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    return 0;
}
