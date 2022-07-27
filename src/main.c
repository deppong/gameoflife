/*
    John Conway's Game of Life 
    programmed in C/SDL2 by Isaiah Deppong

*/
#include "SDL.h"
#include <stdio.h>
#include <stdlib.h>

const int WIDTH  = 800;
const int HEIGHT = 800;
const int res    =  15;

void to_cell_from_mouse(uint8_t *grid, int x, int y, int cols, int val) {
    int cell_x = x>res?(x-res)/res+1:0;
    int cell_y = y>res?(y-res)/res+1:0;
    
    grid[cell_x + cell_y*cols] = val;
}

int main(int argc, char**argv) {
    // Initialization -------------------- 
    int quit = 1;
    int pause = 1;
    float dt = 0.0f;
    float sim_speed = 30.0f;
    Uint32 last_time = SDL_GetTicks();

    struct mouse {
        uint8_t drawing, erasing;
    } mouse = {0, 0};
    
    SDL_Event e;

    const int cols = WIDTH/res;
    const int rows = HEIGHT/res;

    uint8_t *grid = malloc(sizeof(uint8_t) * cols*rows);
    uint8_t *next_grid = malloc(sizeof(uint8_t) * cols*rows);
    for (int i = 0; i < cols*rows; i++) {
        grid[i] = 0;
        next_grid[i] = 0;
    }

    srand(time(0));
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);


    while(quit) {
        SDL_PollEvent(&e);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        switch (e.type) {
            int x = 0, y = 0;
            case SDL_QUIT: quit=0; break;
            case SDL_MOUSEBUTTONDOWN: 
                x = e.button.x;
                y = e.button.y;
                if (e.button.button == SDL_BUTTON_LEFT) {
                    mouse.drawing = 1;
                    to_cell_from_mouse(grid, x, y, cols, 1);
                } else {
                    mouse.erasing = 1;
                    to_cell_from_mouse(grid, x, y, cols, 0);
                }
                break;
            case SDL_MOUSEBUTTONUP:   mouse.drawing = 0; mouse.erasing = 0;break;
            case SDL_MOUSEMOTION:
                x = e.button.x;
                y = e.button.y;
                if (mouse.drawing) {
                    to_cell_from_mouse(grid, x, y, cols, 1);
                } else if (mouse.erasing) {
                    to_cell_from_mouse(grid, x, y, cols, 0);
                }
                break;

            case SDL_KEYDOWN:
                switch (e.key.keysym.sym) {
                    case SDLK_SPACE:  pause=pause?0:1;  break;
                    case SDLK_ESCAPE: quit=0;           break;
                    case SDLK_UP:     sim_speed+=5.0f;  break;
                    case SDLK_DOWN:   sim_speed = sim_speed<0.0f?1.0f:sim_speed-5.0f;  break;
                    case SDLK_r:
                        for (int i = 0; i < cols*rows; i++) {
                            grid[i] = 0;
                        }
                        break;
                    default:
                        break;
                }break;
        }

        Uint32 current_time = SDL_GetTicks32();

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
        dt = ((float)current_time - (float)last_time) / 1000.0f;

        if (!pause && floor(dt / (1.0f / sim_speed)) > 0) { 
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

            last_time = current_time;
        }



        SDL_RenderPresent(renderer);
    }

    free(grid);
    free(next_grid);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    return 0;
}
