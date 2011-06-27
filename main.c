#include <stdio.h>
#include <SDL.h>

#include "mandelbrot.h"

int main(void){
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE) != 0){
        printf("Failed to initialize SDL: %s\n", SDL_GetError());
        return 1;
    }
    SDL_SetVideoMode(1024, 768, 24, SDL_SWSURFACE);
    SDL_Surface *main_surface = SDL_GetVideoSurface();

    run_rendering(main_surface);

    SDL_Quit();
    return 0;
}
