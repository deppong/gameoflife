/*
    John Conway's Game of Life 
    programmed in C/SDL2 by Isaiah Deppong

*/
#include "SDL.h"
#include <stdio.h>
#include <stdlib.h>

const int WIDTH  = 800;
const int HEIGHT = 800;
const int res    =  10;

int main(int argc, char**argv) {
    // Initialization -------------------- 
    int quit = 1;
    int pause = 1;
    int drawing = 0;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Event e;

    srand(time(0));

    SDL_Window *window = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    const int cols = WIDTH/res;
    const int rows = HEIGHT/res;

    uint8_t *grid = malloc(sizeof(uint8_t) * cols*rows);
    uint8_t *next_grid = malloc(sizeof(uint8_t) * cols*rows);
    for (int i = 0; i < cols*rows; i++) {
        grid[i] = 0;
        next_grid[i] = 0;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);


    while(quit) {
        SDL_PollEvent(&e);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        switch (e.type) {
            case SDL_QUIT: quit=0; break;
            case SDL_MOUSEBUTTONDOWN: drawing = 1; break;
            case SDL_MOUSEBUTTONUP:   drawing = 0; break;
            case SDL_MOUSEMOTION:
                if (drawing) {
                    int x = e.button.x;
                    int y = e.button.y;
                    int cell_x = (x-res+1)/res+1;
                    int cell_y = (y-res+1)/res+1;
                    grid[cell_x + cell_y*cols] = 1;
                }
                break;
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym) {
                    case SDLK_SPACE:
                        pause = pause?0:1;
                        break;
                    default:
                        break;
                }break;
        }

        // display each cell
        for (int i = 0; i < cols; i++) {
            for (int j = 0; j < rows; j++) {
                SDL_Rect rect = {
                    i*res, 
                    j*res, 
                    .w=res-1, 
                    .h=res-1,
                };

                if (grid[i + j*cols]) {
                    SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255);
                } else {
                    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
                }
                SDL_RenderFillRect(renderer, &rect);
            }
        }

        // update each cell
        if (!pause) { 
            for (int x = 0; x < cols; x++) {
                for (int y = 0; y < rows; y++) {

                    int neighbors = 0;
                    for (int i = -1; i < 2; i++) {
                        for (int j = -1; j < 2; j++) {
                            neighbors += grid[((x+i+cols)%cols) + ((y+j+rows)%rows)*cols];
                        }
                    }
                    neighbors -= grid[x+y*cols];

                    if (grid[x+y*cols]) {
                        next_grid[x+y*cols] = (neighbors == 2 || neighbors == 3);
                    } else {
                        next_grid[x+y*cols] = neighbors == 3;
                    }
                } 
            } 
            
            for (int i = 0; i < cols*rows; i++) {
                grid[i] = next_grid[i];
            }

            SDL_Delay(25);
        }



        SDL_RenderPresent(renderer);
    }

    free(grid);
    free(next_grid);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    return 0;
}
